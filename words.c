#include <stdio.h>

#define CHAR_a              97
#define CHAR_z              122
#define CHAR_A              65
#define CHAR_Z              90
#define CHAR_NEWLINE        10
#define CHAR_SPACE          32

#define MENU_TEXT_INSERT    49      //ASCII: 1
#define MENU_TEXT_DISPLAY   56      //ASCII: 8
#define MENU_EXIT           57      //ASCII: 9

#define INPUT_MAXSIZE       1000

void word_count();
void menu_display();
int menu_handler(int c);
void text_insert();
void text_display();

//  > display a menu with several options:
//      + display text in memory
//      + dispaly stats (nr. lines, nr. words, nr. chars, histogram of workds, tf/idf) about the text in memory
//      + clear the text in memory and raplace it with another

int main() {

    menu_display();







    int c, i = 0;
    while(i != MENU_EXIT){
        c = getchar();
        if(c == CHAR_NEWLINE);
        else
            i = menu_handler(c);
    }
    return 0;
}

int menu_handler(int c){

    if(c == MENU_TEXT_INSERT)
        text_insert();
    else if(c == MENU_TEXT_DISPLAY)
        text_display();
    else if (c == MENU_EXIT)
        printf(" It will exit the program\n");
    else
        printf(" %c is an invalid option\n", c);
    return c;
}

void text_insert(){
    printf(" It will save a new input\n");
    printf("%d", '0');
    printf("\n");
}

void text_display(){
    printf(" It will display the input\n");
}

void menu_display(){
    printf("Select one of the options:\n");
    printf("  %c:\tInsert text\n", MENU_TEXT_INSERT);
    printf("  %c:\tDisplay text\n", MENU_TEXT_DISPLAY);
    printf("  %c:\tExit the program\n", MENU_EXIT);
}

void word_count(){
 
    printf("\nWord counting game, say something:\n");
    int char_count = 0, row_count = 0, word_count = 0, c = EOF;
    int prev_char = EOF;

    for(char_count = 0; ((c = getchar()) != EOF); char_count++){
        if(char_count == 0 || c == CHAR_NEWLINE){
            row_count++;
        }
        if((prev_char >= CHAR_a && prev_char <= CHAR_z) || (prev_char >= CHAR_A && prev_char <= CHAR_Z)){
            if((c < CHAR_a || c > CHAR_z) || (c < CHAR_A && c > CHAR_Z))
                word_count++;
        }
        prev_char = c;
    }
    printf("\nChars: %d\nRows: %d\nWords: %d\n", char_count, row_count, word_count);
}
