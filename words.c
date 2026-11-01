#include <stdio.h>
#include <limits.h>

#define MAXSIZE     UINT_MAX

void write(char method);
void show();
void stats();

enum choices { INSERT = '1', APPEND = '2', STATS = '3', DISPLAY = '4', EXIT = '9' };
static char choice;
static const char TERMINATOR = '\0';
static char input[MAXSIZE] = { TERMINATOR };

void menu(){
    printf("%s", " |----------------------------|" "\n");
    printf(" | Select one of the options: |\n");
    printf(" |  %c.\tNew text              |\n",    INSERT  );
    printf(" |  %c.\tAppend to text        |\n",    APPEND  );
    printf(" |  %c.\tStats                 |\n",    STATS   );
    printf(" |  %c.\tDisplay               |\n",    DISPLAY );
    printf(" |  %c.\tExit                  |\n",    EXIT    );
    printf(" |----------------------------|\n "             );

    char t;
    extern char choice;
    while((t = getchar()) != '\n') choice = t;
}

int main() {
    extern char choice;
    while(1){
        menu();
        if      (choice              == EXIT)       return 0;
        else if (choice              == INSERT)     write(choice);
        else if (choice              == APPEND)     write(choice);
        else if (choice              == DISPLAY)    show();
        else if (choice              == STATS)      stats();
        else                                        printf(" \"%c\", is an invalid choice\n", choice);
    } 
}

void write(char method){
    char c;
    unsigned int i;
   
    if      (method == INSERT)  i = 0;
    else if (method == APPEND)  for(unsigned int b = 0; b < MAXSIZE && input[b] != TERMINATOR; b++) i = b + 1;
    else                        { printf(" \"%d\", is an invalid write method\n", method); return; }

    while((c = getchar()) != EOF){
        input[i] = c;
        i++;
    }
    input[i] = TERMINATOR;
    clearerr(stdin);
}

void show(){
    unsigned int i = 0;
    while(input[i] != TERMINATOR && i < 100){
        printf("[%d]:\t%c\n", i, input[i]);
        i++;
    }
}

void stats(){
    unsigned int rows = 1, words = 0, chars;
    char chr = TERMINATOR, prev;

    for(chars = 0; (chr = input[chars]) != TERMINATOR; chars++){
        if(chr == TERMINATOR) rows++;
        if((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
            if((chr < 'a' || chr > 'z') || (chr < 'A' && chr > 'Z')) words++;
        prev = chr;
    }
    printf("\nChars: %d\nRows: %d\nWords: %d\n", chars, rows, words);
}
