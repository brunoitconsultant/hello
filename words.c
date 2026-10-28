#include <stdio.h>

#define CHAR_a                  97
#define CHAR_z                  122
#define CHAR_A                  65
#define CHAR_Z                  90
#define CHAR_NEWLINE            10
#define CHAR_SPACE              32

#define MENU_TEXT_INSERT        49      //ASCII: 1
#define MENU_TEXT_DISPLAY       50      //ASCII: 2
#define MENU_TEXT_STATS         51      //ASCII: 3
#define MENU_EXIT               57      //ASCII: 9

#define INPUT_MAXSIZE          10000

void init();
void menu();
void input_show();
void input_stats();
void input_save(char bytes[], int max_lenght, int terminator);

char choice[1];
char input[INPUT_MAXSIZE];

int main() {

    init();
   
    while(choice[0] != MENU_EXIT){

        if(choice[0] == CHAR_NEWLINE);
        else if(choice[0] == MENU_TEXT_INSERT)
            input_save(input, INPUT_MAXSIZE, EOF);
        else if(choice[0] == MENU_TEXT_DISPLAY)
            input_show();
        else if(choice[0] == MENU_TEXT_STATS)
            input_stats();
        else
            printf("%c, is an invalid choice\n", choice[0]);

        menu();
    } 
    return 0;
}

void init(){
    for(int i = 0; i < INPUT_MAXSIZE; i++) input[i] = EOF;
    menu();
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
        printf("buffer[%d]:\t%c\n", i, input[i]);
        i++;
    }
}

void menu(){
    printf("__________________________\nSelect one of the options:\n");
    printf("  %c:\tInsert text\n", MENU_TEXT_INSERT);
    printf("  %c:\tDisplay text\n", MENU_TEXT_DISPLAY);
    printf("  %c:\tCalculate text\n", MENU_TEXT_STATS);
    printf("  %c:\tExit\n", MENU_EXIT);
    printf("__________________________\n\n");
    input_save(choice, 1, CHAR_NEWLINE);    
}

void input_stats(){
 
    int c_cnt = 0, r_cnt = 0, w_cnt = 0;
    int c = EOF, prev_c;

    for(c_cnt = 0; (c = input[c_cnt]) != EOF; c_cnt++){
        if(c_cnt == 0 || c == CHAR_NEWLINE){
            r_cnt++;
        }
        if((prev_c >= CHAR_a && prev_c <= CHAR_z) || (prev_c >= CHAR_A && prev_c <= CHAR_Z)){
            if((c < CHAR_a || c > CHAR_z) || (c < CHAR_A && c > CHAR_Z))
                w_cnt++;
        }
        prev_c = c;
    }
    printf("\nChars: %d\nRows: %d\nWords: %d\n", c_cnt, r_cnt, w_cnt);
}
