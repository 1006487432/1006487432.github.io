#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// 从PEM文件中读取私钥
EVP_PKEY *load_private_key(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Unable to open file");
        return NULL;
    }
    EVP_PKEY *private_key = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
    if (!private_key) {
        ERR_print_errors_fp(stderr);
    }
    fclose(fp);
    return private_key;
}

EVP_PKEY* load_public_key(const char* filename) {
    EVP_PKEY *key = NULL;
    BIO *bio = BIO_new(BIO_s_file());
    if (!bio) {
        fprintf(stderr, "Unable to create file BIO\n");
        return NULL;
    }

    BIO_read_filename(bio, filename);
    key = PEM_read_bio_PUBKEY(bio, NULL, 0, NULL);
    BIO_free(bio);

    if (!key) {
        fprintf(stderr, "Unable to load public key\n");
    }
    return key;
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
int sm2_encrypt(const unsigned char *input_file,EVP_PKEY *pub_key,unsigned char **ciphertext, size_t *ciphertext_len) {
    EVP_PKEY_CTX *pctx = NULL;
    int ret = 0;
    // Check for a valid public key
    if (!pub_key) {
        fprintf(stderr, "Invalid public key.\n");
        return 0;
    }
    // Create a public key context
    pctx = EVP_PKEY_CTX_new(pub_key, NULL);
    if (!pctx) {
        fprintf(stderr, "Unable to create EVP_PKEY_CTX.\n");
        ERR_print_errors_fp(stderr);
        return 0;
    }
    unsigned char* buf = NULL;
    size_t buf_len = 0;
    if(read_file(input_file, &buf, &buf_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    // Initialize the encryption operation
    if (EVP_PKEY_encrypt_init(pctx) <= 0) {
        fprintf(stderr, "Encryption initialization failed.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }
    // Determine the length of the ciphertext
    if (EVP_PKEY_encrypt(pctx, NULL, ciphertext_len, buf, buf_len) <= 0) {
        fprintf(stderr, "Failed to determine ciphertext length.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }
    // Allocate memory for the ciphertext
    *ciphertext = OPENSSL_malloc(*ciphertext_len);
    if (!*ciphertext) {
        fprintf(stderr, "Unable to allocate memory for ciphertext.\n");
        goto cleanup;
    }
    // Perform the encryption
    if (EVP_PKEY_encrypt(pctx, *ciphertext, ciphertext_len, buf, buf_len) <= 0) {
        fprintf(stderr, "Encryption failed.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }
    ret = 1; // Success
    free(buf);
    buf = NULL;
cleanup:
    if (!ret && *ciphertext) {
        OPENSSL_free(*ciphertext);
        *ciphertext = NULL;
        *ciphertext_len = 0;
    }
    if (pctx) {
        EVP_PKEY_CTX_free(pctx);
    }
    return ret;
}
int sm2_decrypt(const unsigned char *input_file,EVP_PKEY *priv_pkey,unsigned char **plaintext, size_t *plaintext_len) {
    EVP_PKEY_CTX *pctx = NULL;
    int ret = 0;

    if (!priv_pkey) {
        fprintf(stderr, "Invalid pri key. \n");
        return 0;
    }
    unsigned char* buf = NULL;
    size_t buf_len = 0;
    if(read_file(input_file, &buf, &buf_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    // Create a private key context
    pctx = EVP_PKEY_CTX_new(priv_pkey, NULL);
    if (!pctx) {
        fprintf(stderr, "Unable to create EVP_PKEY_CTX.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }

    // Initialize the decryption operation
    if (EVP_PKEY_decrypt_init(pctx) <= 0) {
        fprintf(stderr, "Decryption initialization failed.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }

    // Determine the length of the plaintext
    if (EVP_PKEY_decrypt(pctx, NULL, plaintext_len, buf, buf_len) <= 0) {
        fprintf(stderr, "Failed to determine plaintext length.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }

    // Allocate memory for the plaintext
    *plaintext = OPENSSL_malloc(*plaintext_len);
    if (!*plaintext) {
        fprintf(stderr, "Unable to allocate memory for plaintext.\n");
        goto cleanup;
    }

    // Perform the decryption
    if (EVP_PKEY_decrypt(pctx, *plaintext, plaintext_len, buf, buf_len) <= 0) {
        fprintf(stderr, "Decryption failed.\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }
    printf("plaintext:%s", *plaintext);
    ret = 1; // Success
cleanup:
    if (!ret && *plaintext) {
        OPENSSL_free(*plaintext);
        *plaintext = NULL;
        *plaintext_len = 0;
    }
    if (pctx) {
        EVP_PKEY_CTX_free(pctx);
    }
    return ret;
}
int generate_sm2_key(const char *priv_key_file, const char *pub_key_file) {
    EC_KEY *ec_key = NULL;
    EVP_PKEY *pkey = NULL;
    FILE *priv_fp = NULL;
    FILE *pub_fp = NULL;
    int ret = 1; // 1表示失败

    // 创建基于SM2的椭圆曲线密钥
    ec_key = EC_KEY_new_by_curve_name(NID_sm2);
    if (!ec_key) {
        ERR_print_errors_fp(stderr);
        return ret;
    }

    // 生成SM2密钥对
    if (!EC_KEY_generate_key(ec_key)) {
        fprintf(stderr, "Failed to generate SM2 key\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }

    // 将EC_KEY转换为EVP_PKEY
    pkey = EVP_PKEY_new();
    if (!pkey || !EVP_PKEY_assign_EC_KEY(pkey, ec_key)) {
        fprintf(stderr, "Failed to assign EC_KEY to EVP_PKEY\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }
    ec_key = NULL; // EVP_PKEY 已经接管了ec_key的内存管理

    // 保存私钥到文件
    priv_fp = fopen(priv_key_file, "wb");
    if (!priv_fp || !PEM_write_PrivateKey(priv_fp, pkey, NULL, NULL, 0, NULL, NULL)) {
        fprintf(stderr, "Failed to write private key\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }

    // 保存公钥到文件
    pub_fp = fopen(pub_key_file, "wb");
    if (!pub_fp || !PEM_write_PUBKEY(pub_fp, pkey)) {
        fprintf(stderr, "Failed to write public key\n");
        ERR_print_errors_fp(stderr);
        goto cleanup;
    }

    printf("SM2 key pair generated and saved successfully.\n");
    ret = 0; // 成功

cleanup:
    if (pkey) EVP_PKEY_free(pkey);
    if (ec_key) EC_KEY_free(ec_key);
    if (priv_fp) fclose(priv_fp);
    if (pub_fp) fclose(pub_fp);
    return ret;
}
int sm2_sign(const unsigned char *input_file, EVP_PKEY *priv_key, unsigned char **signature, size_t *sig_len) {
    unsigned char *sig = NULL;
    unsigned char *message = NULL;
    size_t len = 0;
    if(read_file(input_file,&message, &len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }
    int ret = 0;
    // Create a signing context
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create signing context\n");
        goto end;
    }
    // Initialize the signing operation
    if (EVP_DigestSignInit(ctx, NULL, EVP_sm3(), NULL, priv_key) <= 0) {
        fprintf(stderr, "Failed to init signing\n");
        goto end;
    }

    // Update the signing operation with the message
    if (EVP_DigestSignUpdate(ctx, message, len) <= 0) {
        fprintf(stderr, "Failed to update signing\n");
        goto end;
    }
    // Finalize the signing operation
    size_t tmp_sig_len = 0;
    if (EVP_DigestSignFinal(ctx, NULL, &tmp_sig_len) <= 0) {
        fprintf(stderr, "Failed to get signature length\n");
        goto end;
    }
    sig = OPENSSL_malloc(tmp_sig_len);
    if (EVP_DigestSignFinal(ctx, sig, &tmp_sig_len) <= 0) {
        fprintf(stderr, "Failed to sign\n");
        goto end;
    }
    // Assign the signature and length
    *signature = (char *)sig;
    *sig_len = tmp_sig_len;
    ret = 1;
    end:
    if (!ret) {
        ERR_print_errors_fp(stderr);
        OPENSSL_free(sig);
    }
    EVP_MD_CTX_free(ctx);
    return ret;
}
int sm2_verify(const unsigned char *input_file, EVP_PKEY *pub_key, const unsigned char *signature) {
    int ret = 0;
    // Load public key
    unsigned char *message = NULL, *sign = NULL;
    size_t len = 0, sig_len = 0;
    if(read_file(input_file,&message, &len) || read_file(signature, &sign, &sig_len)){
        fprintf(stderr, "Unable to read file.\n");
        return 0;
    }

    // Create a verification context
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create verification context\n");
        goto end;
    }

    // Initialize the verification operation
    if (EVP_DigestVerifyInit(ctx, NULL, EVP_sm3(), NULL, pub_key) <= 0) {
        fprintf(stderr, "Failed to init verification\n");
        goto end;
    }

    // Update the verification operation with the message
    if (EVP_DigestVerifyUpdate(ctx, message, len) <= 0) {
        fprintf(stderr, "Failed to update verification\n");
        goto end;
    }

    // Finalize the verification operation
    if (EVP_DigestVerifyFinal(ctx, (const unsigned char *)sign, sig_len) <= 0) {
        fprintf(stderr, "Failed to verify\n");
        goto end;
    }

    ret = 1;

    end:
    if (!ret) {
        ERR_print_errors_fp(stderr);
    }
    EVP_MD_CTX_free(ctx);
    return ret;
}
void usage(){
    printf("usage: -key\n");
    printf("       -e -kfile -file\n");
    printf("       -d -kfile -file\n");
    printf("       -s -kfile -file\n");
    printf("       -v -kfile -file -sig\n");
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
int main(int argc, char * argv[]){
    if(argc == 1){
        usage();
        return 0;
    }
    if(strcmp(argv[1], "-key") == 0){
        const char *priv_key_file = "sm2_private.pem";
        const char *pub_key_file = "sm2_public.pem";
        generate_sm2_key(priv_key_file,pub_key_file);
    }else if(argc <= 5){
        usage();
    }else if(strcmp(argv[1], "-e") == 0 && strcmp(argv[2], "-kfile") == 0){
        EVP_PKEY *pub_key = load_public_key(argv[3]);
        unsigned char * ciphertext = NULL;
        size_t ciphertextlen = 0;
        if(!pub_key){
            fprintf(stderr, "Failed to load keys\n");
            return 1;
        }
        if(check(argv)){
            EVP_PKEY_free(pub_key);
            return 1;
        }
        if (sm2_encrypt((const unsigned char *)argv[5], pub_key, &ciphertext, &ciphertextlen) == 1) {
            // Print the ciphertext
            printf("SM2 Encryption OK\n");
            const char *output_file = "encrypt.txt";
            FILE* fp_out = fopen(output_file, "wb");
            if (!fp_out) {
                printf("SM2 Save Error\n");
                perror("Error opening output file\n");
                fclose(fp_out);
                return 1;
            }
            fwrite(ciphertext, 1, ciphertextlen, fp_out);
            printf("SM2 Save ok\n");
            fclose(fp_out);
        } else {
            fprintf(stderr, "Encryption failed\n");
             if (ciphertext) {
                OPENSSL_free(ciphertext); // 确保在失败时释放内存
            }
        }
    }else if(strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-kfile") == 0){
        EVP_PKEY *priv_key = load_private_key(argv[3]);
        unsigned char * plaintext = NULL;
        size_t plaintextlen = 0;
        if(!priv_key){
            fprintf(stderr, "Failed to load keys\n");
            return 1;
        }
        if(check(argv)){
            EVP_PKEY_free(priv_key);
            return 1;
        }
        if (sm2_decrypt((const unsigned char *)argv[5], priv_key, &plaintext, &plaintextlen) == 1) {
            // Print the ciphertext
            printf("SM2 Decryption OK\n");
            const char *output_file = "decrypt.txt";
            FILE* fp_out = fopen(output_file, "wb");
            if (!fp_out) {
                printf("SM2 Save Error\n");
                perror("Error opening output file\n");
                fclose(fp_out);
                return 1;
            }
            fwrite(plaintext, 1, plaintextlen, fp_out);
            printf("SM2 Save ok\n");
            fclose(fp_out);
        } else {
            fprintf(stderr, "Decryption failed\n");
            if (plaintext) {
                OPENSSL_free(plaintext); // 确保在失败时释放内存
            }
        }
    }else if(strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-kfile") == 0){
        EVP_PKEY *priv_key = load_private_key(argv[3]);
        unsigned char * signtext = NULL;
        size_t signlen = 0;
        if(!priv_key){
            fprintf(stderr, "Failed to load keys\n");
            return 1;
        }
        if(check(argv)){
            EVP_PKEY_free(priv_key);
            return 1;
        }
        if(sm2_sign((const unsigned char *)argv[5], priv_key, &signtext, &signlen) == 1){
            // Print the ciphertext
            printf("SM2 signature OK\n");
            const char *output_file = "signature.sig";
            FILE* fp_out = fopen(output_file, "wb");
            if (!fp_out) {
                printf("SM2 Save Error\n");
                perror("Error opening output file\n");
                fclose(fp_out);
                return 1;
            }
            fwrite(signtext, 1, signlen, fp_out);
            printf("SM2 Save ok\n");
            fclose(fp_out);
        }else{
            fprintf(stderr, "Signature failed\n");
            if (signtext) {
                OPENSSL_free(signtext); // 确保在失败时释放内存
            }
        }
    }
    else if(strcmp(argv[1], "-v") == 0 && strcmp(argv[2], "-kfile") == 0){
        EVP_PKEY *pub_key = load_public_key(argv[3]);
        if(!pub_key){
            fprintf(stderr, "Failed to load keys\n");
            return 1;
        }
        if(check(argv)){
            EVP_PKEY_free(pub_key);
            return 1;
        }
        if(argc <= 6 || strcmp(argv[6], "-sig") != 0){
            usage();
            return 0;
        }
        if (argv[7] == NULL || argv[7][0] == '\0') {
            fprintf(stderr, "No signature provided\n");
            return 1;
        }
        if(sm2_verify((const unsigned char *)argv[5], pub_key, (const unsigned char *)argv[7])){
            printf("Signature verified successfully.\n");
        }else{
            printf("Signature verification failed.\n");
        }
        EVP_PKEY_free(pub_key);
    }else{
        usage();
    }
    return 0;
}
