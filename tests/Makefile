CC = gcc
CFLAGS = -Wall -Wextra -g -I../include
LDFLAGS = -lcheck -lm -lpthread

TEST_SRC = test_matrix.c
PROJECT_SRCS = ../src/matrix.c ../src/matrix_info.c ../src/complex_num.c
TEST_TARGET = test_matrix.exe

all: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(PROJECT_SRCS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(PROJECT_SRCS) $(LDFLAGS)

run: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	-del /Q $(TEST_TARGET) *.o 2>nul || rm -f $(TEST_TARGET) *.o
