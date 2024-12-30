CC = gcc
CFLAGS = -pthread -Wall -Wextra -g
TARGET = program

all: $(TARGET)

$(TARGET): main.o threads_utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o threads_utils.o

main.o: main.c threads_utils.h
	$(CC) $(CFLAGS) -c main.c

threads_utils.o: threads_utils.c threads_utils.h
	$(CC) $(CFLAGS) -c threads_utils.c

clean:
	rm -f *.o $(TARGET)
