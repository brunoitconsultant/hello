CC = gcc
CFLAGS = -Wall -Wextra -g

TARGETS = fahr_to_celsius words

all: $(TARGETS)

fahr_to_celsius: fahr_to_celsius.c
	$(CC) $(CFLAGS) fahr_to_celsius.c -o fahr_to_celsius

words: words.c
	$(CC) $(CFLAGS) words.c -o words

clean:
	rm -f $(TARGETS)

