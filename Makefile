CC = gcc
CFLAGS = -Wall -Wextra -g

TARGETS = words

all: $(TARGETS)

words: words.c
	$(CC) $(CFLAGS) words.c -o words

clean:
	rm -f $(TARGETS)

