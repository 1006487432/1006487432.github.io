// sm3.c
#include <string.h>
#include <stdint.h>
#include <stdio.h>
typedef struct {
    uint32_t total[2];     // 消息总长度（以位为单位）
    uint32_t state[8];     // 哈希状态
    unsigned char buffer[64]; // 数据缓冲区

    // 用于 HMAC
    unsigned char ipad[64];
    unsigned char opad[64];
} sm3_context;

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                             \
    {                                                       \
        (n) = ((uint32_t)(b)[(i)    ] << 24)             \
            | ((uint32_t)(b)[(i) + 1] << 16)             \
            | ((uint32_t)(b)[(i) + 2] <<  8)             \
            | ((uint32_t)(b)[(i) + 3]       );            \
    }
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                             \
    {                                                       \
        (b)[(i)    ] = (unsigned char) ( (n) >> 24 );     \
        (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );     \
        (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );     \
        (b)[(i) + 3] = (unsigned char) ( (n)       );     \
    }
#endif

/*
 * SM3 context setup
 */
void sm3_starts(sm3_context *ctx)
{
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = 0x7380166F;
    ctx->state[1] = 0x4914B2B9;
    ctx->state[2] = 0x172442D7;
    ctx->state[3] = 0xDA8A0600;
    ctx->state[4] = 0xA96F30BC;
    ctx->state[5] = 0x163138AA;
    ctx->state[6] = 0xE38DEE4D;
    ctx->state[7] = 0xB0FB0E4E;
}

static void sm3_process(sm3_context *ctx, const unsigned char data[64])
{
    uint32_t SS1, SS2, TT1, TT2, W[68], W1[64];
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t T[64];
    uint32_t Temp1, Temp2, Temp3, Temp4, Temp5;
    int j;
#ifdef _DEBUG
    int i;
#endif

    for (j = 0; j < 16; j++)
        T[j] = 0x79CC4519;
    for (j = 16; j < 64; j++)
        T[j] = 0x7A879D8A;

    for (j = 0; j < 16; j++)
    GET_UINT32_BE(W[j], data, j * 4);

#ifdef _DEBUG
    printf("Message with padding:\n");
    for (i = 0; i < 8; i++)
        printf("%08x ", W[i]);
    printf("\n");
    for (i = 8; i < 16; i++)
        printf("%08x ", W[i]);
    printf("\n");
#endif

#define FF0(x,y,z) ( (x) ^ (y) ^ (z))
#define FF1(x,y,z) (((x) & (y)) | ( (x) & (z)) | ( (y) & (z)))

#define GG0(x,y,z) ( (x) ^ (y) ^ (z))
#define GG1(x,y,z) (((x) & (y)) | ( (~(x)) & (z)) )

#define  SHL(x,n) (((x) & 0xFFFFFFFF) << (n))
#define ROTL(x,n) (SHL((x),n) | ((x) >> (32 - (n))))

#define P0(x) ((x) ^  ROTL((x),9) ^ ROTL((x),17))
#define P1(x) ((x) ^  ROTL((x),15) ^ ROTL((x),23))

    for (j = 16; j < 68; j++)
    {
        Temp1 = W[j - 16] ^ W[j - 9];
        Temp2 = ROTL(W[j - 3], 15);
        Temp3 = Temp1 ^ Temp2;
        Temp4 = P1(Temp3);
        Temp5 = ROTL(W[j - 13], 7) ^ W[j - 6];
        W[j] = Temp4 ^ Temp5;
    }

#ifdef _DEBUG
    printf("Expanding message W0-67:\n");
    for (i = 0; i < 68; i++)
    {
        printf("%08x ", W[i]);
        if (((i + 1) % 8) == 0) printf("\n");
    }
    printf("\n");
#endif

    for (j = 0; j < 64; j++)
    {
        W1[j] = W[j] ^ W[j + 4];
    }

#ifdef _DEBUG
    printf("Expanding message W'0-63:\n");
    for (i = 0; i < 64; i++)
    {
        printf("%08x ", W1[i]);
        if (((i + 1) % 8) == 0) printf("\n");
    }
    printf("\n");
#endif

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];
    E = ctx->state[4];
    F = ctx->state[5];
    G = ctx->state[6];
    H = ctx->state[7];
#ifdef _DEBUG
    printf("j     A       B        C         D         E        F        G       H\n");
    printf("   %08x %08x %08x %08x %08x %08x %08x %08x\n", A, B, C, D, E, F, G, H);
#endif

    for (j = 0; j < 16; j++)
    {
        SS1 = ROTL((ROTL(A, 12) + E + ROTL(T[j], j)), 7);
        SS2 = SS1 ^ ROTL(A, 12);
        TT1 = FF0(A, B, C) + D + SS2 + W1[j];
        TT2 = GG0(E, F, G) + H + SS1 + W[j];
        D = C;
        C = ROTL(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = ROTL(F, 19);
        F = E;
        E = P0(TT2);
#ifdef _DEBUG
        printf("%02d %08x %08x %08x %08x %08x %08x %08x %08x\n", j, A, B, C, D, E, F, G, H);
#endif
    }

    for (j = 16; j < 64; j++)
    {
        SS1 = ROTL((ROTL(A, 12) + E + ROTL(T[j], j)), 7);
        SS2 = SS1 ^ ROTL(A, 12);
        TT1 = FF1(A, B, C) + D + SS2 + W1[j];
        TT2 = GG1(E, F, G) + H + SS1 + W[j];
        D = C;
        C = ROTL(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = ROTL(F, 19);
        F = E;
        E = P0(TT2);
#ifdef _DEBUG
        printf("%02d %08x %08x %08x %08x %08x %08x %08x %08x\n", j, A, B, C, D, E, F, G, H);
#endif
    }

    ctx->state[0] ^= A;
    ctx->state[1] ^= B;
    ctx->state[2] ^= C;
    ctx->state[3] ^= D;
    ctx->state[4] ^= E;
    ctx->state[5] ^= F;
    ctx->state[6] ^= G;
    ctx->state[7] ^= H;
#ifdef _DEBUG
    printf("   %08x %08x %08x %08x %08x %08x %08x %08x\n", ctx->state[0], ctx->state[1], ctx->state[2],
        ctx->state[3], ctx->state[4], ctx->state[5], ctx->state[6], ctx->state[7]);
#endif
}

/*
 * SM3 process buffer
 */
void sm3_update(sm3_context *ctx, const unsigned char *input, int ilen)
{
    int fill;
    uint32_t left;

    if (ilen <= 0)
        return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < (uint32_t)ilen)
        ctx->total[1]++;

    if (left && ilen >= fill)
    {
        memcpy(ctx->buffer + left, input, fill);
        sm3_process(ctx, ctx->buffer);
        input += fill;
        ilen -= fill;
        left = 0;
    }

    while (ilen >= 64)
    {
        sm3_process(ctx, input);
        input += 64;
        ilen -= 64;
    }

    if (ilen > 0)
    {
        memcpy(ctx->buffer + left, input, ilen);
    }
}

static const unsigned char sm3_padding[64] =
        {
                0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

/*
 * SM3 final digest
 */
void sm3_finish(sm3_context *ctx, unsigned char output[32])
{
    uint32_t last, padn;
    uint32_t high, low;
    unsigned char msglen[8];

    high = (ctx->total[0] >> 29) | (ctx->total[1] << 3);
    low = (ctx->total[0] << 3);

    PUT_UINT32_BE(high, msglen, 0);
    PUT_UINT32_BE(low, msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    sm3_update(ctx, sm3_padding, padn);
    sm3_update(ctx, msglen, 8);

    PUT_UINT32_BE(ctx->state[0], output, 0);
    PUT_UINT32_BE(ctx->state[1], output, 4);
    PUT_UINT32_BE(ctx->state[2], output, 8);
    PUT_UINT32_BE(ctx->state[3], output, 12);
    PUT_UINT32_BE(ctx->state[4], output, 16);
    PUT_UINT32_BE(ctx->state[5], output, 20);
    PUT_UINT32_BE(ctx->state[6], output, 24);
    PUT_UINT32_BE(ctx->state[7], output, 28);
}

/*
 * output = SM3( input buffer )
 */
void sm3(const unsigned char *input, int ilen, unsigned char output[32])
{
    sm3_context ctx;

    sm3_starts(&ctx);
    sm3_update(&ctx, input, ilen);
    sm3_finish(&ctx, output);

    memset(&ctx, 0, sizeof(sm3_context));
}

/*
 * output = SM3( file contents )
 */
int sm3_file(const char *path, unsigned char output[32])
{
    FILE *f;
    size_t n;
    sm3_context ctx;
    unsigned char buf[1024];

    if ((f = fopen(path, "rb")) == NULL)
        return 1;

    sm3_starts(&ctx);

    while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
        sm3_update(&ctx, buf, n);

    sm3_finish(&ctx, output);

    memset(&ctx, 0, sizeof(sm3_context));

    if (ferror(f) != 0)
    {
        fclose(f);
        return 2;
    }

    fclose(f);
    return 0;
}

/*
 * SM3 HMAC context setup
 */
void sm3_hmac_starts(sm3_context *ctx, const unsigned char *key, int keylen)
{
    int i;
    unsigned char sum[32];

    if (keylen > 64)
    {
        sm3(key, keylen, sum);
        keylen = 32;
        //key = sum;
        key = (const unsigned char*)sum;
    }

    memset(ctx->ipad, 0x36, 64);
    memset(ctx->opad, 0x5C, 64);

    for (i = 0; i < keylen; i++)
    {
        ctx->ipad[i] ^= key[i];
        ctx->opad[i] ^= key[i];
    }

    sm3_starts(ctx);
    sm3_update(ctx, ctx->ipad, 64);

    memset(sum, 0, sizeof(sum));
}

/*
 * SM3 HMAC process buffer
 */
void sm3_hmac_update(sm3_context *ctx, const unsigned char *input, int ilen)
{
    sm3_update(ctx, input, ilen);
}

/*
 * SM3 HMAC final digest
 */
void sm3_hmac_finish(sm3_context *ctx, unsigned char output[32])
{
    int hlen = 32;
    unsigned char tmpbuf[32];

    sm3_finish(ctx, tmpbuf);
    sm3_starts(ctx);
    sm3_update(ctx, ctx->opad, 64);
    sm3_update(ctx, tmpbuf, hlen);
    sm3_finish(ctx, output);

    memset(tmpbuf, 0, sizeof(tmpbuf));
}

/*
 * output = HMAC-SM3( hmac key, input buffer )
 */
void sm3_hmac(const unsigned char *key, int keylen,
              const unsigned char *input, int ilen,
              unsigned char output[32])
{
    sm3_context ctx;

    sm3_hmac_starts(&ctx, key, keylen);
    sm3_hmac_update(&ctx, input, ilen);
    sm3_hmac_finish(&ctx, output);

    memset(&ctx, 0, sizeof(sm3_context));
}
// 打印缓冲区为十六进制格式
void dumpbuf(const unsigned char *buf, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", buf[i]);
        if (((i + 1) % 4) == 0) printf(" ");
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
int main(int argc, char *argv[])
{
    if(argc < 5){
        printf("usage: -kfile -file\n");
        return 0;
    }
    if(strcmp(argv[1], "-kfile") == 0 && strcmp(argv[3], "-file") == 0){
        const unsigned char *input = NULL;
        const unsigned char *key = NULL;
        size_t  keylen = 0, ilen = 0;
        if(read_file((const unsigned char*)argv[2], &key, &keylen) || read_file((const unsigned char *)argv[4], &input, &ilen)){
            fprintf(stderr, "Unable to read file.\n");
            return 0;
        }
        unsigned char output[32];
        printf("Message: %s\n", input);
        sm3_hmac(key, keylen, input, ilen, output);
        printf("HMAC:   ");
        dumpbuf(output, 32);

        const char *output_file = "SM3-HMAC.bin";
        FILE* fp_out = fopen(output_file, "wb");
        if (!fp_out) {
            printf("SM3 Save Error\n");
            perror("Error opening output file\n");
            fclose(fp_out);
            return 1;
        }
        fwrite(output, 1, 32, fp_out);
        printf("SM3-HMAC Save ok\n");
        fclose(fp_out);
    }
    return 0;
}
