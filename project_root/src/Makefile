# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra

# 目标文件和可执行文件
OBJ = main.o list_pid.o operate_pid.o communicate_pid.o
EXECUTABLE = project_root

# 默认目标
all: $(EXECUTABLE)

# 生成可执行文件
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

# 依赖关系
main.o: main.c list_pid.h operate_pid.h communicate_pid.h
	$(CC) $(CFLAGS) -c main.c

list_pid.o: list_pid.c list_pid.h
	$(CC) $(CFLAGS) -c list_pid.c

operate_pid.o: operate_pid.c operate_pid.h
	$(CC) $(CFLAGS) -c operate_pid.c

communicate_pid.o: communicate_pid.c communicate_pid.h
	$(CC) $(CFLAGS) -c communicate_pid.c

# 清理生成的文件
clean:
	rm -f $(OBJ) $(EXECUTABLE)