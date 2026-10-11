CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = fahr_to_celsius

all: $(TARGET)

$(TARGET): fahr_to_celsius.c
	$(CC) $(CFLAGS) fahr_to_celsius.c -o $(TARGET)

clean:
	rm -f $(TARGET)

