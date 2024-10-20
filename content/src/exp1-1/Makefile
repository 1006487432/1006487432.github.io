# 定义 C 编译器
CC=gcc

# 定义 C++ 编译器
CXX=g++

# 定义链接的库
LIBS=-lcrypto -lssl

# 定义目标文件
TARGETS=sm2-1 sm3 sm3-hmac sm4

# 默认目标
all: $(TARGETS)

# 规则来构建 sm2-1 程序
sm2-1: sm2-1.c
	$(CC) -o $@ $< $(LIBS)

# 规则来构建 sm3 程序
sm3: sm3.c
	$(CC) -o $@ $< $(LIBS)
sm3-hmac: sm3-hmac.c
	$(CC) -o $@ $< $(LIBS)
sm4: sm4.c
	$(CC) -o $@ $< $(LIBS)
# 清理编译生成的文件
clean:
	rm -f $(TARGETS) *.o

# 伪目标，以便在没有第一个参数时运行默认目标
.PHONY: all clean