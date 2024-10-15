---

title: 课上测试：SM3算法测试
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

## 代码

~~~ makefile
# Compiler and flags
CC = gcc
CFLAGS = -I ~/GmSSL-3.1.1-Linux/include
LDFLAGS = -L ~/GmSSL-3.1.1-Linux/lib -lgmssl

# Targets
TARGETS = gsm3

# Source files
SRCS = sm3.c

# Object files
OBJS = $(SRCS:.c=.o)

# Make targets
all: $(TARGETS)


gsm3: sm3.c
	$(CC) $(CFLAGS) sm3.c $(LDFLAGS) -o gsm3

clean:
	rm -f $(TARGETS) $(OBJS)

~~~



~~~ c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmssl/sm3.h>

int main() {
    FILE *file = NULL;
    unsigned char buffer[1024];
    size_t bytesRead;
    SM3_CTX ctx;
    unsigned char hash[SM3_DIGEST_SIZE];

    // 打开文件
    file = fopen("sn.txt", "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // 初始化SM3上下文
    sm3_init(&ctx);

    // 读取文件并更新哈希状态
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        sm3_update(&ctx, buffer, bytesRead);
    }

    // 最终化哈希并输出结果
    sm3_finish(&ctx, hash);
    for (int i = 0; i < SM3_DIGEST_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // 清理工作
    fclose(file);

    return EXIT_SUCCESS;
}
~~~

## 结果

~~~ shel
[root@localhost roc-exp]# make
gcc -I ~/GmSSL-3.1.1-Linux/include sm3.c -L ~/GmSSL-3.1.1-Linux/lib -lgmssl -o gsm3
[root@localhost roc-exp]# ./gsm3 
2476052a1213e11aa81f31920528336963fb2bd5d8f247bc4c40c7112e24ae4f
[root@localhost roc-exp]# cat sn.txt | openssl sm3
SM3(stdin)= 2476052a1213e11aa81f31920528336963fb2bd5d8f247bc4c40c7112e24ae4f
~~~

结果一致
