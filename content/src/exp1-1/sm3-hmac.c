#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#define BLOCK_LENGTH 64
#define L 32 // SM3的输出长度为256位（32字节）
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
// 异或操作
void XOR(unsigned char *out, const unsigned char *in1, const unsigned char *in2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}

// SM3 HMAC 实现
unsigned char* SM3_HMAC(const unsigned char *key, size_t key_len, const unsigned char *data, size_t data_len, unsigned char *mac, size_t *mac_len) {
    unsigned char key_pad[BLOCK_LENGTH] = {0};
    unsigned char o_key_pad[BLOCK_LENGTH];
    unsigned char inner_hash[L];
    unsigned char final_hash[L];

    // 检查密钥长度并进行处理
    if (key_len > BLOCK_LENGTH) {
        // 如果密钥太长，则对其进行SM3哈希
        EVP_MD_CTX *ctx = EVP_MD_CTX_new();
        if (!ctx) {
            fprintf(stderr, "Unable to create MD context\n");
            return NULL;
        }
        EVP_DigestInit_ex(ctx, EVP_sm3(), NULL);
        EVP_DigestUpdate(ctx, key, key_len);
        unsigned char hashed_key[L];
        EVP_DigestFinal_ex(ctx, hashed_key, NULL);
        memcpy(key_pad, hashed_key, L);
        EVP_MD_CTX_free(ctx);
    } else {
        memcpy(key_pad, key, key_len);
    }

    // 初始化内层和外层哈希的密钥
    memset(o_key_pad, 0x5c, BLOCK_LENGTH);
    memset(key_pad, 0x36, BLOCK_LENGTH);
    XOR(o_key_pad, o_key_pad, key_pad, BLOCK_LENGTH);

    // 计算内层哈希
    EVP_MD_CTX *inner_ctx = EVP_MD_CTX_new();
    if (!inner_ctx) {
        fprintf(stderr, "Unable to create MD context\n");
        return NULL;
    }
    EVP_DigestInit_ex(inner_ctx, EVP_sm3(), NULL);
    EVP_DigestUpdate(inner_ctx, key_pad, BLOCK_LENGTH);
    EVP_DigestUpdate(inner_ctx, data, data_len);
    EVP_DigestFinal_ex(inner_ctx, inner_hash, NULL);
    EVP_MD_CTX_free(inner_ctx);

    // 计算外层哈希
    EVP_MD_CTX *outer_ctx = EVP_MD_CTX_new();
    if (!outer_ctx) {
        fprintf(stderr, "Unable to create MD context\n");
        return NULL;
    }
    EVP_DigestInit_ex(outer_ctx, EVP_sm3(), NULL);
    EVP_DigestUpdate(outer_ctx, o_key_pad, BLOCK_LENGTH);
    EVP_DigestUpdate(outer_ctx, inner_hash, L);
    EVP_DigestFinal_ex(outer_ctx, final_hash, NULL);
    EVP_MD_CTX_free(outer_ctx);
    // 设置最终的MAC值
    memcpy(mac, final_hash, L);
    *mac_len = L;
    return mac;
}

int main(int argc, char * argv[]) {
    if(argc < 5){
        printf("usage: -kfile -file");
        return 0;
    }
    if(strcmp(argv[1], "-kfile") == 0 && strcmp(argv[3], "-file") == 0){
        unsigned char *key, *data;
        unsigned char mac[L];
        size_t mac_len, key_len, data_len;
        if(read_file((const unsigned char*)argv[2], &key, &key_len) || read_file((const unsigned char *)argv[4], &data, &data_len)){
            fprintf(stderr, "Unable to read file.\n");
            return 0;
        }
        SM3_HMAC(key, key_len, data, data_len, mac, &mac_len);
        printf("HMAC-SM3: ");
        for (size_t i = 0; i < mac_len; i++) {
            printf("%02x", mac[i]);
        }
        printf("\n");

        const char *output_file = "SM3-HMAC.bin";
        FILE* fp_out = fopen(output_file, "wb");
        if (!fp_out) {
            printf("SM3 Save Error\n");
            perror("Error opening output file\n");
            fclose(fp_out);
            return 1;
        }
        fwrite(mac, 1, L, fp_out);
        printf("SM3-HMAC Save ok\n");
        fclose(fp_out);
    }
    return 0;
}