CC = gcc
CFLAGS = -Wall -Wextra -Wuninitialized -O0 -g -fsanitize=address,undefined -mcmodel=medium

TARGETS = words

all: $(TARGETS)

words: words.c
	$(CC) $(CFLAGS) words.c -o words

clean:
	@rm -f $(TARGETS)

