#include <stdio.h>
#include <limits.h>

#define MAXSIZE     UINT_MAX    //4,294,967,295

void save();
void show();
void stats();

enum choices { INSERT, STATS, DISPLAY, EXIT = 9 };
char choice;
char input[MAXSIZE] = {'\0'};

char menu(){
    printf(" |----------------------------|\n");
    printf(" | Select one of the options: |\n");
    printf(" |  %d.\tInsert                |\n",    INSERT);
    printf(" |  %d.\tStats                 |\n",    STATS);
    printf(" |  %d.\tDisplay               |\n",    DISPLAY);
    printf(" |  %d.\tExit                  |\n",    EXIT);
    printf(" |----------------------------|\n ");

    char t, c;
    while((t = getchar()) != '\n') c = t;
    return c; 
}

int main() {
    while      ((choice = menu() - '0')   != EXIT){
        if     (choice              == '\n')    ;
        else if(choice              == INSERT)  save();
        else if(choice              == DISPLAY) show();
        else if(choice              == STATS)   stats();
        else                                    printf(" \"%d\", is an invalid choice\n", choice);
    } 
    return 0;
}

void save(){    
    char c;
    int i = 0;
    while((c = getchar()) != EOF){
        input[i] = c;
        i++;
    }
    input[i] = '\0';
    clearerr(stdin);
}

void show(){
    int i = 0;
    while(input[i] != '\0'){
        printf("[%d]:\t%c\n", i, input[i]);
        i++;
    }
}

void stats(){
    int rows = 1, words = 0, chars;
    int chr = '\0', prev;

    for(chars = 0; (chr = input[chars]) != '\0'; chars++){
        if(chr == '\n') rows++;
        if((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
            if((chr < 'a' || chr > 'z') || (chr < 'A' && chr > 'Z')) words++;
        prev = chr;
    }
    printf("\nChars: %d\nRows: %d\nWords: %d\n", chars, rows, words);
}
