---

title: 课上测试：gdb 调试
subtitle:
date: 2024-10-08T10:11:56+08:00
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

## 编译运⾏ "bestidiocs2024/ch02/c/testgdb.c"，记录编译运⾏结果

~~~ shell
➜  c git:(master) ✗gcc -g testgdb.c -o testgdb
➜  c git:(master) ✗ ls
car.c  hello.c  lib  make  project  test.c  testgdb  testgdb.c
➜  c git:(master) ✗ ./testgdb
The sum of 1-50 is 1275
The sum of 1-50 is 1275
~~~

## 调试代码

### 设置函数断点和行断点

~~~ shell
pwndbg> b main
Breakpoint 1 at 0x1141: file testgdb.c, line 8.
pwndbg> b 10
Breakpoint 2 at 0x1150: file testgdb.c, line 10.
~~~

### 设置临时断点

~~~ shell
pwndbg> tb 12
Temporary breakpoint 3 at 0x55555555516d: file testgdb.c, line 12.
~~~

### 设置条件断点

~~~ shell
pwndbg> b 24 if i == 25
Breakpoint 4 at 0x5555555551d2: file testgdb.c, line 24.
pwndbg> c
Continuing.

Breakpoint 4, sum (m=50) at testgdb.c:24
24              n += i;
~~~



### 使⽤单步运⾏等其他命令

#### r

~~~ shell
pwndbg> r
Starting program: /home/zhanhe/bestidiocs2024/ch02/c/testgdb
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at testgdb.c:8
8           int i, n = 0;
~~~

#### n

~~~ shell
pwndbg> n
9           pi = &i;
pwndbg> n

Breakpoint 2, main () at testgdb.c:10
10          int arr[3] = { 10, 20, 30 };
~~~

#### c

~~~ shell
pwndbg> c
Continuing.

Temporary breakpoint 3, main () at testgdb.c:12
12          sum(50);
~~~

#### s

~~~ shell
pwndbg> s
sum (m=50) at testgdb.c:22
22          int i, n = 0;
~~~

#### p

~~~ shell
pwndbg> p i
$1 = 25
pwndbg> c
Continuing.
The sum of 1-50 is 1275
The sum of 1-50 is 1275
[Inferior 1 (process 1118) exited normally]
~~~

#### info b

~~~ shell
pwndbg> info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000555555555141 in main at testgdb.c:8
        breakpoint already hit 1 time
2       breakpoint     keep y   0x0000555555555150 in main at testgdb.c:10
        breakpoint already hit 1 time
4       breakpoint     keep y   0x00005555555551d2 in sum at testgdb.c:24
        stop only if i == 25
        breakpoint already hit 1 time
~~~

#### display

~~~ shell
display i
1: i = 0
~~~

#### set var

~~~ shell
pwndbg> set var i = 51
pwndbg> p i
$2 = 51
~~~

#### watch

~~~ shell
watch i
Hardware watchpoint 5: i
n
Hardware watchpoint 5: i

Old value = 51
New value = 52
~~~
#### delete watch
~~~ shell
delete watch 5
~~~

