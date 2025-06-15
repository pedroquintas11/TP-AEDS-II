CC=gcc
CFLAGS=-g -Wall
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TARGET=app.exe

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(TARGET)