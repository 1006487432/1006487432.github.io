#include <stdio.h>
#include <string.h>
#include <gmssl/sm3.h>
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
int main(int argc, char* argv[]) {
    if(argc < 3){
        printf("usage: -in filename\n");
        return 0;
    }
    if(strcmp(argv[1], "-in") != 0){
        printf("usage: -in filename\n");
        return 0;
    }
    unsigned char hash[SM3_DIGEST_SIZE];  // SM3_DIGEST_SIZE is the length of the hash
    SM3_CTX ctx;
    sm3_init(&ctx);  // Initialize the hash context
    sm3_update(&ctx, (const unsigned char*)argv[2], strlen(argv[2]));  // Hash the data
    sm3_finish(&ctx, hash);  // Finalize the hash
    printf("SM3 hash: ");
    for (int i = 0; i < SM3_DIGEST_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    const char *output_file = "hash.bin";
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        printf("SM3 Save Error\n");
        perror("Error opening output file\n");
        fclose(fp_out);
        return 1;
    }
    fwrite(hash, 1, SM3_DIGEST_SIZE, fp_out);
    printf("SM3 Save ok\n");
    fclose(fp_out);
    return 0;
}