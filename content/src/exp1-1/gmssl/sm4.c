#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "gmssl/sm4.h"
#include "gmssl/rand.h"

void usage() {
    printf("usage:    -key\n");
    printf("          -iv\n");
    printf("          -e/-d -key -iv -file\n");
    return;
}

int read_file(const unsigned char *input_file, unsigned char **text, size_t *len) {
    FILE *fp_in = fopen(input_file, "rb");
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

int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage();
        return;
    }
    if (strcmp(argv[1], "-key") == 0) {
        uint8_t key[SM4_KEY_SIZE];
        if (rand_bytes(key, SM4_KEY_SIZE) != 1) {
            fprintf(stderr, "随机密钥生成失败。\n");
            return EXIT_FAILURE;
        }
        printf("随机生成的密钥: ");
        for (size_t i = 0; i < SM4_KEY_SIZE; i++) {
            printf("%02X ", key[i]);
        }
        printf("\n");
        const char *output_file = "key.bin";
        FILE *fp_out = fopen(output_file, "wb");
        if (!fp_out) {
            printf("Save Error\n");
            perror("Error opening output file\n");
            fclose(fp_out);
            return 1;
        }
        fwrite(key, 1, SM4_KEY_SIZE, fp_out);
        printf("key Save ok\n");
        fclose(fp_out);
    } else if (strcmp(argv[1], "-iv") == 0) {
        uint8_t iv[SM4_BLOCK_SIZE];
        if (rand_bytes(iv, SM4_BLOCK_SIZE) != 1) {
            fprintf(stderr, "随机IV生成失败。\n");
            return EXIT_FAILURE;
        }
        // 打印生成的IV
        printf("随机生成的IV: ");
        for (size_t i = 0; i < SM4_BLOCK_SIZE; i++) {
            printf("%02X ", iv[i]);
        }
        printf("\n");
        const char *output_file = "iv.bin";
        FILE *fp_out = fopen(output_file, "wb");
        if (!fp_out) {
            printf("Save Error\n");
            perror("Error opening output file\n");
            fclose(fp_out);
            return 1;
        }
        fwrite(iv, 1, SM4_BLOCK_SIZE, fp_out);
        printf("iv Save ok\n");
        fclose(fp_out);
    } else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 8) {
            usage();
            return 0;
        }
        if (strcmp(argv[2], "-key") != 0 || strcmp(argv[4], "-iv") != 0 || strcmp(argv[6], "-file") != 0) {
            usage();
            return 0;
        }
        unsigned char *plaintext = NULL, *key = NULL, *iv = NULL;
        size_t plaintext_len = 0, key_len = 0, iv_len = 0;
        if (read_file((const unsigned char *) argv[3], &key, &key_len) ||
            read_file((const unsigned char *) argv[5], &iv, &iv_len) ||
            read_file((const unsigned char *) argv[7], &plaintext, &plaintext_len)) {
            fprintf(stderr, "Unable to read file.\n");
            return 0;
        }
        if(key_len != SM4_KEY_SIZE || iv_len != SM4_BLOCK_SIZE){
            printf("key or iv error\n");
            return 0;
        }
        SM4_KEY enc_key;
        sm4_set_encrypt_key(&enc_key, key);
        size_t max_ciphertext_len = plaintext_len + SM4_BLOCK_SIZE;
        uint8_t *ciphertext = malloc(max_ciphertext_len);
        if (ciphertext == NULL) {
            fprintf(stderr, "内存分配失败。\n");
            return EXIT_FAILURE;
        }
        size_t outlen;
        int ret;
        // 加密带填充的明文
        ret = sm4_cbc_padding_encrypt(&enc_key, (uint8_t *) iv, (uint8_t *)plaintext, plaintext_len, ciphertext, &outlen);
        if (ret != 1) {
            fprintf(stderr, "加密失败。\n");
            free(ciphertext);
            return EXIT_FAILURE;
        }
        // 输出密文（十六进制格式）
        printf("密文 (%zu 字节): ", outlen);
        for (size_t i = 0; i < outlen; i++) {
            printf("%02X ", ciphertext[i]);
        }
        printf("\n");
        const char *output_file = "ciphertext.txt";
        FILE *fp_out = fopen(output_file, "wb");
        if (!fp_out) {
            printf("Save Error\n");
            perror("Error opening output file\n");
            fclose(fp_out);
            return 1;
        }
        fwrite(ciphertext, 1, outlen, fp_out);
        printf("Save ok\n");
        fclose(fp_out);
        free(ciphertext);
    } else if (strcmp(argv[1], "-d") == 0) {
        unsigned char *ciphertext = NULL, *key = NULL, *iv = NULL;
        size_t ciphertext_len = 0, key_len = 0, iv_len = 0;
        if (argc < 8) {
            usage();
            return 0;
        }
        if (strcmp(argv[2], "-key") != 0 || strcmp(argv[4], "-iv") != 0 || strcmp(argv[6], "-file") != 0) {
            usage();
            return 0;
        }
        if (read_file((const unsigned char *) argv[3], &key, &key_len) ||
            read_file((const unsigned char *) argv[5], &iv, &iv_len) ||
            read_file((const unsigned char *) argv[7], &ciphertext, &ciphertext_len)) {
            fprintf(stderr, "Unable to read file.\n");
            return 0;
        }
        if(key_len != SM4_KEY_SIZE || iv_len != SM4_BLOCK_SIZE){
            printf("key or iv error\n");
            return 0;
        }
        SM4_KEY dec_key;
        sm4_set_decrypt_key(&dec_key, key);
        size_t max_ciphertext_len = ciphertext_len;
        uint8_t *decryptedtext = malloc(max_ciphertext_len + 1); // +1用于终止符
        if (decryptedtext == NULL) {
            fprintf(stderr, "内存分配失败。\n");
            free(ciphertext);
            free(key);
            free(iv);
            return EXIT_FAILURE;
        }
        size_t outlen;
        // 解密带填充的密文
        int ret = sm4_cbc_padding_decrypt(&dec_key, (uint8_t *) iv, (uint8_t *) ciphertext, max_ciphertext_len,
                                          decryptedtext, &outlen);
        if (ret != 1) {
            fprintf(stderr, "解密失败。\n");
            free(ciphertext);
            free(decryptedtext);
            return EXIT_FAILURE;
        }
        // 确保解密后的文本是以空字符结尾的字符串
        decryptedtext[outlen] = '\0';
        // 打印解密后的明文（以十六进制格式）
        printf("解密后的明文 (%zu 字节): ", outlen);
        for (size_t i = 0; i < outlen; i++) {
            printf("%02X ", decryptedtext[i]);
        }
        printf("\n");
        const char *output_file = "decryptedtext.txt";
        FILE *fp_out = fopen(output_file, "wb");
        if (!fp_out) {
            printf("Save Error\n");
            perror("Error opening output file\n");
            fclose(fp_out);
            return 1;
        }
        fwrite(decryptedtext, 1, outlen, fp_out);
        printf("Save ok\n");
        fclose(fp_out);
        free(decryptedtext);
    } else {
        usage();
        return EXIT_SUCCESS;
    }
}