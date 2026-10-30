#include <stdio.h>
#include <limits.h>

#define MAXSIZE     UINT_MAX    //4,294,967,295
#define INSERT      49          //ASCII: 1
#define STATS       50          //ASCII: 2
#define DISPLAY     51          //ASCII: 3
#define EXIT        57          //ASCII: 9

void save();
void show();
void stats();
char choice;
char input[MAXSIZE] = {'\0'};

char menu(){
    printf(" |----------------------------|\n");
    printf(" | Select one of the options: |\n");
    printf(" |  %c.\tInsert                |\n",   INSERT);
    printf(" |  %c.\tStats                 |\n",    STATS);
    printf(" |  %c.\tDisplay               |\n",  DISPLAY);
    printf(" |  %c.\tExit                  |\n",     EXIT);
    printf(" |----------------------------|\n ");

    char t, c;
    while((t = getchar()) != '\n') c = t;
    return c; 
}

int main() {
    while      ((choice = menu())   != EXIT){
        if     (choice              == '\n')    ;
        else if(choice              == INSERT)  save();
        else if(choice              == DISPLAY) show();
        else if(choice              == STATS)   stats();
        else                                    printf(" \"%c\", is an invalid choice\n", choice);
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
