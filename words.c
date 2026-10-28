#include <stdio.h>

#define a               97
#define z               122
#define A               65
#define Z               90
#define NEWLINE         10
#define SPACE           32

#define TEXT_INSERT     49      //ASCII: 1
#define TEXT_DISPLAY    50      //ASCII: 2
#define TEXT_STATS      51      //ASCII: 3
#define EXIT            57      //ASCII: 9

#define MAXSIZE         10000

void init();
char menu();
void input_show();
void input_stats();
void input_save(char bytes[], int max_lenght, int terminator);

char choice;
char input[MAXSIZE];

int main() {

    init();
   
    while(choice != EXIT){

        if(choice == NEWLINE);
        else if(choice == TEXT_INSERT)
            input_save(input, MAXSIZE, EOF);
        else if(choice == TEXT_DISPLAY)
            input_show();
        else if(choice == TEXT_STATS)
            input_stats();
        else
            printf("%c, is an invalid choice\n", choice);

        choice = menu();
    } 
    return 0;
}

void init(){
    for(int i = 0; i < MAXSIZE; i++) input[i] = EOF;
    choice = menu();
}

void input_save(char bytes[], int max_lenght, int terminator){
    
    for(int i = 0; i < max_lenght; i++) bytes[i] = EOF;
    
    char c;
    int i = 0;
    while((c = getchar()) != terminator){
        bytes[i] = c;
        i++;
    }
    clearerr(stdin);
}

void input_show(){
    int i = 0;
    while(input[i] != EOF){
        printf("[%d]:\t%c\n", i, input[i]);
        i++;
    }
}

char menu(){
    printf("__________________________\nSelect one of the options:\n");
    printf("  %c.\tInsert text\n", TEXT_INSERT);
    printf("  %c.\tDisplay text\n", TEXT_DISPLAY);
    printf("  %c.\tCalculate text\n", TEXT_STATS);
    printf("  %c.\tExit\n\n\n", EXIT);

    char c, b;
    while((c = getchar()) != '\n')
        b = c;
    
    return b;     
}

void input_stats(){
 
    int c_cnt = 0, r_cnt = 0, w_cnt = 0;
    int c = EOF, prev_c;

    for(c_cnt = 0; (c = input[c_cnt]) != EOF; c_cnt++){
        if(c_cnt == 0 || c == NEWLINE){
            r_cnt++;
        }
        if((prev_c >= a && prev_c <= z) || (prev_c >= A && prev_c <= Z)){
            if((c < a || c > z) || (c < A && c > Z))
                w_cnt++;
        }
        prev_c = c;
    }
    printf("\nChars: %d\nRows: %d\nWords: %d\n", c_cnt, r_cnt, w_cnt);
}
