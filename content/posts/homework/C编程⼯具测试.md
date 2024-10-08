---
title: C编程⼯具测试
subtitle:
date: 2024-10-08T12:07:56+08:00
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

# C编程⼯具测试

## hello

### 过程

~~~ shell
➜  p2 git:(master) ✗ gcc -E hello.c -o hello.i
➜  p2 git:(master) ✗ gcc -S hello.i -o hello.s
➜  p2 git:(master) ✗ gcc -c hello.s -o hello.o
➜  p2 git:(master) ✗ gcc hello.o -o hello
➜  p2 git:(master) ✗ ls
a.out  hello  hello.c  hello.i  hello.o  hello.s
➜  p2 git:(master) ✗ ./hello
hello 20221415
~~~

## 大小端代码测试

### 编译运行

~~~ makefile
all:
        gcc cebitfields.c -o cebitfields
        gcc cebitwise.c -o cebitwise
        gcc celibrary.c -o celibrary
        gcc cepointer.c -o cepointer
        gcc ceunion.c -o ceunion
~~~

~~~ shell
➜  big-little-endian git:(master) ✗ make
gcc cebitfields.c -o cebitfields
gcc cebitwise.c -o cebitwise
gcc celibrary.c -o celibrary
gcc cepointer.c -o cepointer
gcc ceunion.c -o ceunion
➜  big-little-endian git:(master) ✗ ls
cebitfields    cebitwise    celibrary    cepointer    ceunion    Makefile
cebitfields.c  cebitwise.c  celibrary.c  cepointer.c  ceunion.c
➜  big-little-endian git:(master) ✗ ./cebitfields
Little Endian (Bit-field Method)
➜  big-little-endian git:(master) ✗ ./cebitwise
Little Endian (Bitwise Method)
➜  big-little-endian git:(master) ✗ ./celibrary
Little Endian (Standard Library Method)
➜  big-little-endian git:(master) ✗ ./cepointer
Little Endian (Pointer Method)
➜  big-little-endian git:(master) ✗ ./ceunion
Little Endian (Union Method)
~~~

## 命令行

### 编写main.c ble.h Makefile

#### main.c

~~~ c++
#include "ble.h"
#include<string.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if(argc == 1){
        printf("use -i to chose method\n");
        printf("1 -> fields\n2 -> wise\n3 -> library\n4 -> pointer\n5 -> union\n");
        return 0;
    }
    int choice = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-i") == 0){
            if(i + 1 >= argc){
                printf("Parameters are missing\n");
                return 0;
            }
            choice = atoi(argv[i + 1]);
            break;
        }
    }
    switch (choice) {
        case 1:
            check_endian_bit_field();
            break;
        case 2:
            check_endian_bitwise();
            break;
        case 3:
            check_endian_standard();
            break;
        case 4:
            check_endian_pointer();
            break;
        case 5:
            check_endian_union();
            break;
        default:
            printf("Wrong Parameters\n");
    }
    return 0;
}
~~~

#### ble.h

~~~ c++
#ifndef CC_BLE_H
#define CC_BLE_H
#include<stdio.h>
void check_endian_bit_field();
void check_endian_bitwise();
void check_endian_standard();
void check_endian_pointer();
void check_endian_union();
#endif //CC_BLE_H
~~~

#### Makefile

~~~ shell
main: cebitfields.o cebitwise.o celibrary.o cepointer.o ceunion.o main.o
	gcc -o main *.o

cebitfields.o: cebitfields.c ble.h
	gcc -c cebitfields.c

cebitwise.o: cebitwise.c ble.h
	gcc -c cebitwise.c

celibrary.o: celibrary.c ble.h
	gcc -c celibrary.c

cepointer.o: cepointer.c ble.h
	gcc -c cepointer.c

ceunion.o: ceunion.c ble.h
	gcc -c ceunion.c

main.: main.c ble.h
	gcc -c main.c

clean:
	rm -f *.o
~~~

### 编译运行

~~~ shell
➜  p3 git:(master) ✗ make && make clean
gcc -c cebitfields.c
gcc -c cebitwise.c
gcc -c celibrary.c
gcc -c cepointer.c
gcc -c ceunion.c
cc    -c -o main.o main.c
gcc -o main *.o
rm -f *.o
➜  p3 git:(master) ✗ ./main            
use -i to chose method
1 -> fields
2 -> wise
3 -> library
4 -> pointer
5 -> union
~~~

~~~ shell
➜  p3 git:(master) ✗ ./main -i 1  
Little Endian (Bit-field Method)
➜  p3 git:(master) ✗ ./main -i 2
Little Endian (Bitwise Method)
➜  p3 git:(master) ✗ ./main -i 3
Little Endian (Standard Library Method)
➜  p3 git:(master) ✗ ./main -i 4
Little Endian (Pointer Method)
➜  p3 git:(master) ✗ ./main -i 5
Little Endian (Union Method)
➜  p3 git:(master) ✗ ./main -i  
Parameters are missing
➜  p3 git:(master) ✗ ./main -i 10
Wrong Parameters
~~~

## 静态库

### 制作静态库

Makefile

~~~ shell
libble.a: cebitfields.o cebitwise.o celibrary.o cepointer.o ceunion.o
	ar rcs  libble.a *.o

cebitfields.o: cebitfields.c ble.h
	gcc -c cebitfields.c

cebitwise.o: cebitwise.c ble.h
	gcc -c cebitwise.c

celibrary.o: celibrary.c ble.h
	gcc -c celibrary.c

cepointer.o: cepointer.c ble.h
	gcc -c cepointer.c

ceunion.o: ceunion.c ble.h
	gcc -c ceunion.c

clean:
	rm -f *.o
~~~

~~~ shell
➜  p3-1 git:(master) ✗ make && make clean
gcc -c cebitfields.c
gcc -c cebitwise.c
gcc -c celibrary.c
gcc -c cepointer.c
gcc -c ceunion.c
ar rcs  libble.a *.o
rm -f *.o
➜  p3-1 git:(master) ✗ ls
ble.h  cebitfields.c  cebitwise.c  celibrary.c  cepointer.c  ceunion.c  libble.a  main  main.c  Makefile
~~~
### 链接静态库
~~~ shell
➜  p3-1 git:(master) ✗ rm main
➜  p3-1 git:(master) ✗ sudo cp libble.a /usr/lib/
➜  p3-1 git:(master) ✗ gcc -o main main.c -lble
~~~

### 测试运行

~~~ shell
➜  p3-1 git:(master) ✗ ls
ble.h  cebitfields.c  cebitwise.c  celibrary.c  cepointer.c  ceunion.c  libble.a  main  main.c  Makefile
➜  p3-1 git:(master) ✗ ./main -i 1 
Little Endian (Bit-field Method)
➜  p3-1 git:(master) ✗ ./main -i 2
Little Endian (Bitwise Method)
➜  p3-1 git:(master) ✗ ./main -i 3
Little Endian (Standard Library Method)
➜  p3-1 git:(master) ✗ ./main -i 4
Little Endian (Pointer Method)
➜  p3-1 git:(master) ✗ ./main -i 5
Little Endian (Union Method)
➜  p3-1 git:(master) ✗ ./main -i  
Parameters are missing
➜  p3-1 git:(master) ✗ ./main -i 10
Wrong Parameters
➜  p3-1 git:(master) ✗ ./main      
use -i to chose method
1 -> fields
2 -> wise
3 -> library
4 -> pointer
5 -> union
~~~

## 动态库

### 制作动态库

Makefile

~~~ shell
libble.so: cebitfields.o cebitwise.o celibrary.o cepointer.o ceunion.o
	gcc -shared *.o -o libble.so

cebitfields.o: cebitfields.c ble.h
	gcc -c cebitfields.c -fpic

cebitwise.o: cebitwise.c ble.h
	gcc -c cebitwise.c -fpic

celibrary.o: celibrary.c ble.h
	gcc -c celibrary.c -fpic

cepointer.o: cepointer.c ble.h
	gcc -c cepointer.c -fpic

ceunion.o: ceunion.c ble.h
	gcc -c ceunion.c -fpic

clean:
	rm -f *.o
~~~

~~~ shell
➜  p3-2 git:(master) ✗ make && make clean
gcc -c cebitfields.c -fpic
gcc -c cebitwise.c -fpic
gcc -c celibrary.c -fpic
gcc -c cepointer.c -fpic
gcc -c ceunion.c -fpic
gcc -shared *.o -o libble.so
rm -f *.o
~~~

### 链接动态库

~~~ shell
➜  p3-2 git:(master) ✗ gcc -o main main.c -L ./home/zhanhe/cc/2024-10-08/p3-2 -lble
~~~

### 编译运行

~~~ shell
➜  p3-2 git:(master) ✗ ./main
use -i to chose method
1 -> fields
2 -> wise
3 -> library
4 -> pointer
5 -> union
➜  p3-2 git:(master) ✗ ./main -i 10
Wrong Parameters
➜  p3-2 git:(master) ✗ ./main -i   
Parameters are missing
➜  p3-2 git:(master) ✗ ./main -i 1 
Little Endian (Bit-field Method)
➜  p3-2 git:(master) ✗ ./main -i 2
Little Endian (Bitwise Method)
➜  p3-2 git:(master) ✗ ./main -i 3
Little Endian (Standard Library Method)
➜  p3-2 git:(master) ✗ ./main -i 4
Little Endian (Pointer Method)
➜  p3-2 git:(master) ✗ ./main -i 5
Little Endian (Union Method)
~~~

## 项目结构

### 组织项目结构

~~~ shell
➜  p3-3 git:(master) ✗ tree
.
├── bin
├── docs
├── include
│   └── ble.h
├── lib
├── Makefile
└── src
    ├── cebitfields.c
    ├── cebitwise.c
    ├── celibrary.c
    ├── cepointer.c
    ├── ceunion.c
    └── main.c

6 directories, 8 files

~~~

### 编写Makefile

~~~ shell
target = ./bin/main
src = $(wildcard ./src/*.c)
obj = $(patsubst %.c,%.o, $(src))
include = ./include

$(target): $(obj)
	gcc $^ -o $@

%.o:%.c
	gcc $< -c -I $(include) -o $@

clean:
	rm -f $(obj)
~~~

### 编译运行

~~~ shell
➜  p3-3 git:(master) ✗ make && make clean
gcc src/cebitfields.c -c -I ./include -o src/cebitfields.o
gcc src/cebitwise.c -c -I ./include -o src/cebitwise.o
gcc src/celibrary.c -c -I ./include -o src/celibrary.o
gcc src/cepointer.c -c -I ./include -o src/cepointer.o
gcc src/ceunion.c -c -I ./include -o src/ceunion.o
gcc src/main.c -c -I ./include -o src/main.o
gcc src/cebitfields.o src/cebitwise.o src/celibrary.o src/cepointer.o src/ceunion.o src/main.o -o bin/main
rm -f ./src/cebitfields.o ./src/cebitwise.o ./src/celibrary.o ./src/cepointer.o ./src/ceunion.o ./src/main.o
➜  p3-3 git:(master) ✗ tree
.
├── bin
│   └── main
├── docs
├── include
│   └── ble.h
├── lib
├── Makefile
└── src
    ├── cebitfields.c
    ├── cebitwise.c
    ├── celibrary.c
    ├── cepointer.c
    ├── ceunion.c
    └── main.c

6 directories, 9 files
➜  p3-3 git:(master) ✗ ./bin/main 
use -i to chose method
1 -> fields
2 -> wise
3 -> library
4 -> pointer
5 -> union
➜  p3-3 git:(master) ✗ ./bin/main -i 1
Little Endian (Bit-field Method)
➜  p3-3 git:(master) ✗ ./bin/main -i 2
Little Endian (Bitwise Method)
➜  p3-3 git:(master) ✗ ./bin/main -i 3
Little Endian (Standard Library Method)
➜  p3-3 git:(master) ✗ ./bin/main -i 4
Little Endian (Pointer Method)
➜  p3-3 git:(master) ✗ ./bin/main -i 5
Little Endian (Union Method)
➜  p3-3 git:(master) ✗ ./bin/main -i  
Parameters are missing
➜  p3-3 git:(master) ✗ ./bin/main -i 10
Wrong Parameters
~~~

