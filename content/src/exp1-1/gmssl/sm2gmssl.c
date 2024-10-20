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
