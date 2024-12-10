---
title: 课上测试：SM2算法测试
subtitle:
date: 2024-12-10T11:02:56+08:00
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

# 完成下面任务（24分）



## 1 在 Ubuntu 或 openEuler 中完成任务（推荐openEuler）

## 2 生成一个文档 sn.txt,内容为全班同学的 8 位学号，把你的学号排到第一个

使用AI生成：

~~~
我：生成纯文本，20221401到20221428只有最后两位不同
~~~
~~~
AI:好的，以下是从20221401到20221428的日期序列，每个日期只有最后两位数字不同：

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
20221413
20221414
20221415
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

在ubuntu中存储，并把20221415调到第一位

~~~
$ cat 1.txt
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
20221413
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

## 3 使用 GmSSL 命令产生一对公私钥对。（4 分）

使用命令生成公私钥对：

~~~
$ gmssl sm2keygen -pass 1415 -out sm2.pem -pubout sm2pub.pem
$ ls
sm2.pem  sm2gmssl  sm2pub.pem  sn.txt
~~~

本次使用代码生成的密钥对进行实验

~~~ shell
$ ./sm2gmssl -key
生成 SM2 密钥对...
SM2 密钥生成成功。
    SM2
        publicKey: 47AE2801D522EB748E30A12934B2CD2040E23E87906F1235E66524ED9DEFAD525800F49788E431CF0CA2BA9F95473B41C4B6BC926FCAA14675F73AE7DC9A13DC
        privateKey: b8d417427dd1c4290a7f825e7abcc38570b959a89fae9cc499514eac0f506540
$ ls
private_key.bin  public_key.bin  sm2gmssl  sm2gmssl.c  sn.txt
~~~

## 4 使用 GmSSL 编程对sn.txt进行加密解密，提交代码或代码链接，以及编译运行过程（文本或截图）（10 分）

第4问和第5问使用同一代码，在文末统一展示

~~~
$ ./sm2gmssl
usage: -key
       -e -kfile -file
       -d -kfile -file
       -s -pri -pub -file
       -v -kfile -file -signature
~~~

加密

~~~ shell
$ ./sm2gmssl -e -kfile public_key.bin -file 1.txt
加密成功。
密文: 30820168022001435F69E8C368CAF8A5B640C5201A5740FF9B017C6ABA29E00B25DECFD629DF022100973BFBFE6B5F35E218C3145D647C3F038AE666BEEA35669CDB89986FA4E5570C0420E6F2E64727905F9BFB10928250AE447C3390CF11EB3B2DA28AD46227E92D53D80481FEB8EBBC7CBFE9A0B226E2ABB5F2D940EB020FB26C5D7A940D6E036B04BD9E1170E2C833B83EDBCD06D985EBA9549C6D7E2FACA97389E17A3A07E7A2FCB2FCBEAEEE1C4FB375D98AE9B7F665AA4F63BB9CEDDE4ECDDF0B5AF48C7C9672536D4253F10F4EC560878A9F415744AEE4EC7CD551A929C83FBA2756100FFBC5C2B488E44951AD0784D990573EB3D7D3A9F1520A6AAB0C8B987730352A3CE2FA803C0EAFF7BB72D4863CC17995A5C60667393BC3DD062E29992FD8ECBE719E704A7D1340FD79B70EBEB4B29C66188FB7BA3952AE847D781D585A53EB9052323879F40DA3575F13B3DAA28FFA73599203E94B015969DE3E84B38FC4A41AB57B3F0E3B
Save ok
~~~

解密

~~~ shell
$ ./sm2gmssl -d -kfile private_key.bin -file encrypt.txt
解密密文...
解密成功。
解密后的明文: 20221415
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
20221413
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



Save ok
~~~

## 5 使用 GmSSL 编程对sn.txt进行签名验签，提交代码或代码链接，以及编译运行过程（文本或截图）（10 分）

签名

~~~ shell
$ ./sm2gmssl -s -pri private_key.bin -pub public_key.bin -file 1.txt
签名成功。
签名: 3045022051BB2DCB5B43472F76EFECEE447A8DE8A102EBB95EF78B655277FD05BCCB2CD1022100CDE9FD326DE6698DCFE92B8C0D81C9C4F5244A669019C4D5F2EAC532AA4FEF4E
Save ok
~~~

验签

~~~shell
$ ./sm2gmssl -v -kfile public_key.bin -file 1.txt -signature signature.sig
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
20221413
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



签名: 3045022051BB2DCB5B43472F76EFECEE447A8DE8A102EBB95EF78B655277FD05BCCB2CD1022100CDE9FD326DE6698DCFE92B8C0D81C9C4F5244A669019C4D5F2EAC532AA4FEF4E
签名验证成功。
~~~

## 代码

~~~ c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmssl/sm2.h>
#include <gmssl/sm3.h>
#include <gmssl/error.h>
int read_file(const unsigned char *input_file, unsigned char ** text, size_t* len){
    FILE* fp_in = fopen(input_file, "rb");
    if (!fp_in) {
        perror("Error opening input file");
        return 1;
    }
    // 获取文件大小并分配内存
    fseek(fp_in, 0, SEEK_END);
    *len = ftell(fp_in);
    fseek(fp_in, 0, SEEK_SET);
    *text = malloc(*len);
    if (!*text) {
        perror("Memory allocation failed");
        return 0;
    }
    fread(*text, 1, *len, fp_in);
    fclose(fp_in);
    return 0;
}
// 辅助函数：以十六进制格式打印字节数组
void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s: ", label);
    for(size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int gmssl_sm2_encrypt(const unsigned char * input_file, SM2_KEY* key){
    unsigned char *plaintext = NULL;
    size_t plaintext_len = 0;
    if(read_file(input_file,&plaintext, &plaintext_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    };
    uint8_t ciphertext[SM2_MAX_CIPHERTEXT_SIZE];
    size_t ciphertext_len = sizeof(ciphertext);
    int ret = sm2_encrypt(key, (const uint8_t *)plaintext, plaintext_len, ciphertext, &ciphertext_len);
    if (ret != 1) {
        fprintf(stderr, "SM2 加密失败\n");
        return EXIT_FAILURE;
    }
    printf("加密成功。\n");
    // 打印密文
    print_hex("密文", ciphertext, ciphertext_len);
    const char *output_file = "encrypt.txt";
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        perror("Error opening output file\n");
        fclose(fp_out);
        return 1;
    }
    fwrite(ciphertext, 1, ciphertext_len, fp_out);
    printf("Save ok\n");
    fclose(fp_out);
}
int gmssl_sm2_decrypt(const unsigned char * input_file, SM2_KEY* key){
    unsigned char *ciphertext = NULL;
    size_t ciphertext_len = 0;
    if(read_file(input_file,&ciphertext, &ciphertext_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    };
    uint8_t decrypted[SM2_MAX_PLAINTEXT_SIZE];
    size_t decrypted_len = sizeof(decrypted);
    printf("解密密文...\n");
    int ret = sm2_decrypt(key, (const uint8_t *)ciphertext, ciphertext_len, decrypted, &decrypted_len);
    if (ret != 1) {
        fprintf(stderr, "SM2 解密失败\n");
        return EXIT_FAILURE;
    }
    printf("解密成功。\n");
    // 确认解密后的明文与原始明文一致
    decrypted[decrypted_len] = '\0'; // 添加字符串终止符
    printf("解密后的明文: %s\n", decrypted);
    const char *output_file = "decrypt.txt";
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        perror("Error opening output file\n");
        fclose(fp_out);
        return 1;
    }
    fwrite(decrypted, 1, decrypted_len, fp_out);
    printf("Save ok\n");
    fclose(fp_out);
}
int gmssl_sm2_sign(const unsigned char * input_file, SM2_KEY* key){
    char *message = NULL;
    size_t message_len = 0;
    if(read_file(input_file,&message, &message_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    };
    SM2_SIGN_CTX sign_ctx;
    sm2_sign_init(&sign_ctx, key, SM2_DEFAULT_ID, SM2_DEFAULT_ID_LENGTH);
    // 更新签名上下文
    int ret = sm2_sign_update(&sign_ctx, (const uint8_t *)message, message_len);
    if (ret != 1) {
        fprintf(stderr, "SM2 签名更新失败\n");
        return EXIT_FAILURE;
    }
    // 完成签名
    uint8_t signature[SM2_MAX_SIGNATURE_SIZE];
    size_t signature_len = sizeof(signature);
    ret = sm2_sign_finish(&sign_ctx, signature, &signature_len);
    if (ret != 1) {
        fprintf(stderr, "SM2 签名失败\n");
        return EXIT_FAILURE;
    }
    printf("签名成功。\n");
    print_hex("签名", signature, signature_len);
    const char *output_file = "signature.sig";
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        perror("Error opening output file\n");
        fclose(fp_out);
        return 1;
    }
    fwrite(signature, 1, signature_len, fp_out);
    printf("Save ok\n");
    fclose(fp_out);
}
int gmssl_sm2_verify(const unsigned char * input_file, const unsigned char * input_sign, SM2_KEY* key){
    unsigned char *message = NULL;
    size_t message_len = 0;
    if(read_file(input_file,&message, &message_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    uint8_t *signature = NULL;
    size_t signature_len = 0;
    if(read_file(input_sign,&signature, &signature_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    printf("%s\n", message);
    print_hex("签名",signature,signature_len);
    SM2_SIGN_CTX verify_ctx;
    sm2_verify_init(&verify_ctx, key, SM2_DEFAULT_ID, SM2_DEFAULT_ID_LENGTH);
    int ret = sm2_verify_update(&verify_ctx, (const uint8_t *)message, message_len);
    if (ret != 1) {
        fprintf(stderr, "SM2 签名验证更新失败\n");
        return EXIT_FAILURE;
    }

    ret = sm2_verify_finish(&verify_ctx, signature, signature_len);
    if (ret == 1) {
        printf("签名验证成功。\n");
    } else {
        printf("签名验证失败。\n");
        return EXIT_FAILURE;
    }
}
int generate_sm2_key(){
    int ret;
    SM2_KEY key;
    // 生成 SM2 密钥对
    printf("生成 SM2 密钥对...\n");
    ret = sm2_key_generate(&key);
    if (ret != 1) {
        fprintf(stderr, "SM2 密钥生成失败\n");
        return 1;
    }
    printf("SM2 密钥生成成功。\n");
    FILE *priv_fp = fopen("private_key.bin", "wb");
    if (priv_fp == NULL) {
        fprintf(stderr, "打开私钥文件失败\n");
        return EXIT_FAILURE;
    }
    FILE *pub_fp = fopen("public_key.bin", "wb");
    if (pub_fp == NULL) {
        fprintf(stderr, "打开公钥文件失败\n");
        return EXIT_FAILURE;
    }
    uint8_t prikey[32];
    sm2_z256_to_bytes(key.private_key, prikey);
    uint8_t octets[65];
    octets[0] = SM2_point_uncompressed;
    (void)sm2_z256_point_to_bytes(&key.public_key, octets + 1);
    fwrite(prikey, 1, sizeof(prikey), priv_fp);
    fclose(priv_fp); // 关闭私钥文件
    // 写入公钥
    fwrite(octets, 1, sizeof(octets), pub_fp);
    fclose(pub_fp); // 关闭公钥文件
    sm2_key_print(stdout, 0, 4, "SM2", &key);
    return 0;
}
int load_pri_key(const unsigned char* pri, SM2_KEY* mykey){
    if (mykey == NULL) {
        fprintf(stderr, "提供的SM2_KEY结构指针无效\n");
        return 1;
    }
    FILE *priv_fp = fopen(pri, "rb");
    if (priv_fp == NULL) {
        fprintf(stderr, "打开私钥文件失败\n");
        return 1;
    }
    uint8_t prikey[32];
    size_t len;
    len = fread(prikey, 1, sizeof(prikey), priv_fp);
    if (len != sizeof(prikey)) {
        fprintf(stderr, "读取私钥数据失败\n");
        fclose(priv_fp);
        return 1;
    }
    fclose(priv_fp);
    sm2_z256_from_bytes(mykey->private_key, prikey);
    return 0;
}
int load_pub_key(const unsigned char* pub, SM2_KEY* mykey){
    if (mykey == NULL) {
        fprintf(stderr, "提供的SM2_KEY结构指针无效\n");
        return 1;
    }
    FILE *pub_fp = fopen(pub, "rb");
    if (pub_fp == NULL) {
        fprintf(stderr, "打开公钥文件失败\n");
        return 1;
    }
    uint8_t octets[65];
    size_t len;
    len = fread(octets, 1, sizeof(octets), pub_fp);
    if (len != sizeof(octets)) {
        fprintf(stderr, "读取公钥数据失败\n");
        fclose(pub_fp);
        return 1;
    }
    fclose(pub_fp);
    if (sm2_z256_point_from_bytes(&mykey->public_key, octets + 1) != 1) {
        fprintf(stderr, "密钥数据加载失败\n");
        return 1;
    }
    return 0;
}
int load_key(const char* pri_file, const char* pub_file, SM2_KEY* mykey) {
    load_pub_key(pub_file, mykey);
    load_pri_key(pri_file, mykey);
    return 0;
}

void usage(){
    printf("usage: -key\n");
    printf("       -e -kfile -file\n");
    printf("       -d -kfile -file\n");
    printf("       -s -pri -pub -file\n");
    printf("       -v -kfile -file -signature\n");
}
int check(char * argv[]){
    if(strcmp(argv[4], "-file") != 0){
        usage();
        return 1;
    }
    if (argv[5] == NULL || argv[5][0] == '\0') {
        fprintf(stderr, "No file provided\n");
        return 1;
    }
    return 0;
}
int main(int argc, char* argv[]) {
    SM2_KEY mykey;
    if(argc == 1){
        usage();
        return 0;
    }
    if(strcmp(argv[1], "-key") == 0){
        generate_sm2_key();
    }else if(argc <= 5){
        usage();
    }else if(strcmp(argv[1], "-e") == 0 && strcmp(argv[2], "-kfile") == 0){
        if(load_pub_key((const unsigned char*)argv[3], &mykey)){
            fprintf(stderr, "密钥数据加载失败\n");
            return 1;
        }
        if(check(argv)){
            usage();
            return 1;
        }
        gmssl_sm2_encrypt((const unsigned char*)argv[5], &mykey);
    }else if(strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-kfile") == 0){
        if(load_pri_key((const unsigned char*)argv[3], &mykey)){
            fprintf(stderr, "密钥数据加载失败\n");
            return 1;
        }
        if(check(argv)){
            usage();
            return 1;
        }
        gmssl_sm2_decrypt((const unsigned char*)argv[5], &mykey);
    }else if(strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-pri") == 0 && strcmp(argv[4], "-pub") == 0){
        if(load_pri_key((const unsigned char*)argv[3], &mykey) || load_pub_key((const unsigned char*)argv[5], &mykey)){
            fprintf(stderr, "密钥数据加载失败\n");
            return 1;
        }
        if(strcmp(argv[6], "-file") != 0 || argv[7] == NULL){
            usage();
            return 1;
        }
        gmssl_sm2_sign((const unsigned char*)argv[7], &mykey);
    }
    else if(strcmp(argv[1], "-v") == 0 && strcmp(argv[2], "-kfile") == 0){
        //load_pri_key("private_key.bin", &mykey);
        if(load_pub_key((const unsigned char*)argv[3], &mykey)){
            fprintf(stderr, "密钥数据加载失败\n");
            return 1;
        }
        if(check(argv) || strcmp(argv[6], "-signature") != 0 || argv[7] == NULL){
            usage();
            return 1;
        }
        gmssl_sm2_verify((const unsigned char*)argv[5], (const unsigned char*) argv[7],&mykey);
    }else {
        usage();
    }
}
~~~

## 提交要求 (1')

1 记录实践过程和 AI 问答过程，尽量不要截图，给出文本内容
2 (选做)推荐所有作业托管到 gitee或 github 上
3 (必做)提交作业 markdown文档，命名为“学号-姓名-作业题目.md”
4 (必做)提交作业 markdown文档转成的 PDF 文件，命名为“学号-姓名-作业题目.pdf”