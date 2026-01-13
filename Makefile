

CC = gcc
CLFAGS = -g -Wall
TARGET = lab9_mmahtab_208

all:  $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)
clean:
	rm $(TARGET)
