#include <openssl/evp.h>
#include <string.h>
void dumpbuf(const unsigned char *buf, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", buf[i]);
    }
    printf("\n");
}
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
int sm3_hash(const unsigned char *input_file, unsigned char *hash, unsigned int *hash_len)
{
    unsigned char *message = NULL;
    size_t len = 0;
    if(read_file(input_file,&message, &len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    EVP_MD_CTX *md_ctx = NULL;
    const EVP_MD *md = NULL;
    int ret = -1; // 默认返回值为失败
    md_ctx = EVP_MD_CTX_new();
    if (md_ctx == NULL) {
        return ret;
    }
    md = EVP_sm3();
    if (md == NULL) {
        EVP_MD_CTX_free(md_ctx);
        return ret;
    }
    if (EVP_DigestInit_ex(md_ctx, md, NULL) != 1) {
        goto cleanup;
    }
    if (EVP_DigestUpdate(md_ctx, message, len) != 1) {
        goto cleanup;
    }
    if (EVP_DigestFinal_ex(md_ctx, hash, hash_len) != 1) {
        goto cleanup;
    }
    ret = 0; // 成功
    cleanup:
    EVP_MD_CTX_free(md_ctx);
    return ret;
}
int main(int argc, char * argv[]){
    unsigned char hash_value[32]; // SM3 输出 32 字节
    unsigned int hash_len;
    if(argc < 3){
        printf("usage: -in filename\n");
        return 0;
    }
    if(strcmp(argv[1], "-in") != 0){
        printf("usage: -in filename\n");
        return 0;
    }
    int ret = sm3_hash((const unsigned char *)argv[2], hash_value, &hash_len);
    if (ret != 0) {
        fprintf(stderr, "SM3 Hash failed\n");
        return 1;
    }
    printf("SM3 Hash OK\n");
    const char *output_file = "hash.bin";
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        printf("SM3 Save Error\n");
        perror("Error opening output file\n");
        fclose(fp_out);
        return 1;
    }
    dumpbuf(hash_value, hash_len);
    fwrite(hash_value, 1, hash_len, fp_out);
    printf("SM3 Save ok\n");
    fclose(fp_out);
    return 0;
}