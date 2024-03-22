CSOURCE = $(shell find . -name "*.c")
OBJ  = $(CSOURCE:.c=.o)
CC     = gcc
TARGET = server

CFLAGS =  -Wall -std=c99 
CFLAGS += -I./Login_solv  -I./protocol  -I./down_up  -I./chatroom

#链接库参数
LDFLAGS = -lpthread

#最终目标是demo 依赖所有工程内的.o文件
$(TARGET):$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "链接完成"

#自定义make自动推导出来的执行规则
%.o:%.c
	@$(CC) $^ -o $@ -c $(CFLAGS)
	@echo $^

#我们希望clean是一个非文件的目标 
#解决：声明clean是一个伪目标
.PHONY:clean

clean:
	-@rm $(TARGET) $(OBJ)


