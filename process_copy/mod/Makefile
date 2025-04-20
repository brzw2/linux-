
LIBRARY_PATH=../library
INCLUDE_PATH=../include
CC=gcc
TARGET=copy
CFLAGS=-I$(INCLUDE_PATH) -c -g -Wall
SRCFILE=$(wildcard *.c)#获取当前目录下所有.c 后缀的文件名存储到SRCFILE中
DESTFILE=$(patsubst %.c,%.o,$(SRCFILE)) #字符串替换 将SRCFILE中所有.c后缀
#变为.c后缀

#主目标 将-o 链接链接编译成 process_copy
$(TARGET):$(DESTFILE)
	$(CC) $^ -o $@

#从目标，根据.c生成二进制.o文件

%.o:%.c
	$(CC) $(CFLAGS) $<


clean:
	rm $(DESTFILE) -rf
	rm $(TARGET) -rf

