#include <stdio.h>
#include <limits.h>

#define MAXSIZE     UINT_MAX

void save();
void show();
void stats();

enum choices { INSERT = '1', STATS = '2', DISPLAY = '3', EXIT = (9 + '0') };
static char choice;
static const char TERMINATOR = '\0', ENTER = '\n';
static char input[MAXSIZE] = { TERMINATOR };

void menu(){
    printf("%s", " |----------------------------|" "\n");
    printf(" | Select one of the options: |\n");
    printf(" |  %c.\tInsert                |\n",    INSERT);
    printf(" |  %c.\tStats                 |\n",    STATS);
    printf(" |  %c.\tDisplay               |\n",    DISPLAY);
    printf(" |  %c.\tExit                  |\n",    EXIT);
    printf(" |----------------------------|\n ");

    char t;
    extern char choice;
    while((t = getchar()) != '\n') choice = t;
}

int main() {
    extern char choice;
    while(1){
        menu();
        if      (choice              == EXIT)       break;
        //else if (choice              == ENTER)      ;
        else if (choice              == INSERT)     save();
        else if (choice              == DISPLAY)    show();
        else if (choice              == STATS)      stats();
        else                                        printf(" \"%c\", is an invalid choice\n", choice);
    } 
    return 0;
}

void save(){    
    char c;
    unsigned int i = 0;
    while((c = getchar()) != EOF){
        input[i] = c;
        i++;
    }
    input[i] = TERMINATOR;
    clearerr(stdin);
}

void show(){
    unsigned int i = 0;
    while(input[i] != TERMINATOR){
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
