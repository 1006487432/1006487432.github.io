#define _CRT_SECURE_NO_WARNINGS

#include "openssl/evp.h"
#include <string.h>
#include <stdio.h>

#define FAILURE -1
#define SUCCESS 0
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
// Function to print hexadecimal data  
void print_hex(const char *title, const unsigned char *data, int len) {
    printf("%s:", title);
    for (int i = 0; i < len; i++) {
        if (i % 16 == 0)
            printf("\n%04X: ", i);
        printf("%02X ", data[i]);
    }
    printf("\n");
}
int do_encrypt(const unsigned char * input_key, const unsigned char * input_iv, const unsigned char * input_message,const EVP_CIPHER *type, const char *ctype)
{
    unsigned char outbuf[1024];
    int outlen, tmplen;
    // SM4 uses a 16-byte (128-bit) key  
    unsigned char *key, *iv, *message;
    size_t key_len, iv_len, message_len;
    if(read_file(input_key, &key, &key_len) || read_file(input_iv, &iv, &iv_len)) {
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    if(key_len != 16 || iv_len != 16) {
        fprintf(stderr, "Error Key or Iv.\n");
        return 0;
    }
    if(read_file(input_message, &message, &message_len)) {
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    // SM4 block size is 16 bytes, so IV should also be 16 bytes
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        printf("Failed to create EVP_CIPHER_CTX\n");
        return FAILURE;
    }

    // Initialize encryption operation  
    if (EVP_EncryptInit_ex(ctx, type, NULL, key, iv) != 1) {
        printf("EVP_EncryptInit_ex failed for %s\n", ctype);
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    // Provide plaintext and get ciphertext  
    if (EVP_EncryptUpdate(ctx, outbuf, &outlen, (unsigned char*)message, message_len) != 1) {
        printf("EVP_EncryptUpdate failed for %s\n", ctype);
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    // Finalize encryption  
    if (EVP_EncryptFinal_ex(ctx, outbuf + outlen, &tmplen) != 1) {
        printf("EVP_EncryptFinal_ex failed for %s\n", ctype);
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }
    outlen += tmplen;
    // Clean up context  
    EVP_CIPHER_CTX_free(ctx);

    // Write ciphertext to file  
    char filename[64];
    sprintf(filename, "./cipher_%s.dat", ctype);
    FILE *out = fopen(filename, "wb+");
    if (!out) {
        printf("Cannot open file: %s\n", filename);
        return FAILURE;
    }
    fwrite(outbuf, 1, outlen, out);
    fflush(out);
    fclose(out);
    printf("%s encryption successful. Ciphertext length: %d bytes\n", ctype, outlen);
    print_hex("Ciphertext", outbuf, outlen);
    return SUCCESS;
}
int do_decrypt(const unsigned char * input_key, const unsigned char * input_iv, const unsigned char * input_message,const EVP_CIPHER *type, const char *ctype)
{
    unsigned char inbuf[1024] = { 0 };
    unsigned char outbuf[1024] = { 0 };
    int outlen, inlen, tmplen;
    // SM4 uses a 16-byte (128-bit) key  
    unsigned char *key, *iv, *message;
    size_t key_len, iv_len, message_len;
    if(read_file(input_key, &key, &key_len) || read_file(input_iv, &iv, &iv_len)) {
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    if(key_len != 16 || iv_len != 16) {
        fprintf(stderr, "Error Key or Iv.\n");
        return 0;
    }
    if(read_file(input_message, &message, &message_len)) {
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        printf("Failed to create EVP_CIPHER_CTX\n");
        return FAILURE;
    }

    // Initialize decryption operation  
    if (EVP_DecryptInit_ex(ctx, type, NULL, key, iv) != 1) {
        printf("EVP_DecryptInit_ex failed for %s\n", ctype);
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    // Provide ciphertext and get plaintext  
    if (EVP_DecryptUpdate(ctx, outbuf, &outlen, message, message_len) != 1) {
        printf("EVP_DecryptUpdate failed for %s\n", ctype);
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }
    // Finalize decryption  
    if (EVP_DecryptFinal_ex(ctx, outbuf + outlen, &tmplen) != 1) {
        printf("EVP_DecryptFinal_ex failed for %s\n", ctype);
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }
    outlen += tmplen;
    // Clean up context  
    EVP_CIPHER_CTX_free(ctx);
    printf("%s decryption result: \n%.*s\n", ctype, outlen, outbuf);
    print_hex("Decrypted plaintext (hex)", outbuf, outlen);
    return SUCCESS;
}

int main(int argc, char *argv[])
{
    // Initialize OpenSSL algorithms
    OpenSSL_add_all_algorithms();
    // Use SM4-CBC for encryption and decryption
    const EVP_CIPHER *sm4_cbc = EVP_sm4_cbc();
    if (!sm4_cbc) {
        printf("Cannot get SM4-CBC cipher\n");
        return FAILURE;
    }

    if(argc < 8){
        printf("usage: -e/-d -kfile -iv -file");
        return 0;
    }
    if(strcmp(argv[1], "-e") == 0){
        if(strcmp(argv[2], "-kfile") == 0 && strcmp(argv[4], "-iv") == 0 && strcmp(argv[6], "-file") == 0)
            if (do_encrypt((unsigned char*)argv[3], (unsigned char*)argv[5],(unsigned char*)argv[7],sm4_cbc, "sm4-cbc") != SUCCESS) {
                printf("SM4-CBC encryption failed\n");
                EVP_cleanup();
                return FAILURE;
            }
    }else if(strcmp(argv[1], "-d") == 0){
        if(strcmp(argv[2], "-kfile") == 0 && strcmp(argv[4], "-iv") == 0 && strcmp(argv[6], "-file") == 0){
            if (do_decrypt((unsigned char*)argv[3], (unsigned char*)argv[5],(unsigned char*)argv[7],sm4_cbc, "sm4-cbc") != SUCCESS) {
                printf("SM4-CBC decryption failed\n");
                EVP_cleanup();
                return FAILURE;
            }
        }
    }else{
        printf("usage: -e/-d -kfile -iv -file");
        return 0;
    }
    // Clean up OpenSSL algorithms  
    EVP_cleanup();

    return 0;
}