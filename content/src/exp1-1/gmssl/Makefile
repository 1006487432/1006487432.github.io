# Makefile for sm4gmssl.c

# 编译器
CC = gcc

# 手动指定 GmSSL 的包含路径和库路径
GMSSL_INCLUDE = ~/GmSSL-3.1.1-Linux/include
GMSSL_LIB = ~/GmSSL-3.1.1-Linux/lib

# 编译选项
CFLAGS = -Wall -O2 -I $(GMSSL_INCLUDE)
LDFLAGS = -L $(GMSSL_LIB) -lgmssl

# 可执行文件名称  ·
TARGET = sm2gmssl sm3gmssl sm3-hmac sm4
# 默认目标
all: $(TARGET)
sm2gmssl: sm2gmssl.c
	$(CC) -o $@ $^ $(LDFLAGS)  $(CLAGS)

sm3gmssl: sm3.c
	$(CC) -o $@ $^ $(LDFLAGS)  $(CLAGS)
sm3-hmac: sm3-hmac.c
	$(CC) -o $@ $^ $(LDFLAGS)  $(CLAGS)
sm4: sm4.c
	$(CC) -o $@ $^ $(LDFLAGS)  $(CLAGS)
# 清理生成的文件
clean:
	rm -f $(TARGET) $(OBJS)

# 伪目标
.PHONY: all clean
