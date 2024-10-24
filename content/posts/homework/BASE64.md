---


title: 课上测试：BASE64
subtitle:
date: 2024-10-24T17:07:56+08:00
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

# BASE64

## 手动对“你的姓名的首字母”进行 BASE64 编码，给出编码过程。（5 分）

cjs

ascii为:

63 6a 73

二进制为:

0110 0011 0110 1010 0111 0011

按六个分组为:

011000 为24 查表为Y

110110 为 54 查表为2

101001为 41 查表为p

110011 为 51 查表为z

编码为Y2pz

## 使用OpenSSL 命令或者 Linux base64 命令验证你的编码的正确性（4 分）

~~~ shell
$ echo -n "cjs" | openssl base64
Y2pz
$ echo -n "cjs" | base64
Y2pz
~~~

结果与手动编码一致

## 使用OpenSSL编程对sn.txt进行加密解密，提交代码或代码链接，以及编译运行过程（文本或截图）（5 分）

~~~ shell
$ cat sn.txt
20221415
20221401
20221402
20221403
20221404
20221405
20221406
20221407
20221408
20221409
20221410
20221411
20221412
20221414
20221414
20221416
20221417
20221418
20221419
20221420
20221421
20221422
20221423
20221424
20221425
20221426
20221427
20221428
~~~

### 加密代码
~~~ c
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>

int encode_file(const char *input_filename) {
    BIO *b64, *bio, *bio_err;
    FILE *input_file;
    int buffer_length = 1024;
    unsigned char buffer[buffer_length];
    int len;

    /* Open the file for reading */
    input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    /* Create a memory BIO for the base64 encoded output */
    b64 = BIO_new(BIO_f_base64());
    b64 = BIO_push(b64, BIO_new(BIO_s_mem())); // Push the base64 filter into the chain

    /* Read the file, encode to base64 and write to the memory BIO */
    while (!feof(input_file)) {
        len = fread(buffer, 1, buffer_length, input_file);
        if (len > 0) {
            BIO_write(b64, buffer, len);
        }
    }

    // Flush the base64 encoding
    BIO_flush(b64);

    // Get the memory BIO in the chain
    bio = BIO_pop(b64); // Get the memory BIO
    BIO_set_close(bio, BIO_NOCLOSE); // We will close it

    // Read from the memory BIO and write to stdout
    while ((len = BIO_read(bio, buffer, buffer_length)) > 0) {
        fwrite(buffer, 1, len, stdout);
    }

    // Cleanup
    BIO_free_all(b64);
    BIO_free(bio);
    fclose(input_file);

    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    return encode_file(argv[1]);
}
~~~
### 运行结果

~~~ shell
$ cat cjs.txt
cjs
$ ./mybase64 cjs.txt
Y2pz
~~~

