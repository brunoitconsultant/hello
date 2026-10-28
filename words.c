#include <stdio.h>

#define CHAR_a                  97
#define CHAR_z                  122
#define CHAR_A                  65
#define CHAR_Z                  90
#define CHAR_NEWLINE            10
#define CHAR_SPACE              32

#define MENU_TEXT_INSERT        49      //ASCII: 1
#define MENU_TEXT_DISPLAY       56      //ASCII: 8
#define MENU_EXIT               57      //ASCII: 9

#define BUFFER_MAXSIZE          1000

void menu();
void buffer_show();
void buffer_stats(char buffer[]);
void buffer_save(char buffer[], int terminator);

char buffer[BUFFER_MAXSIZE];

int main() {

    menu();
   
    if(buffer[0] == CHAR_NEWLINE);
    else if(buffer[BUFFER_MAXSIZE-1] == 1 && buffer[0] == MENU_TEXT_INSERT){
        buffer_save(buffer, EOF);
    }else if(buffer[0] == MENU_TEXT_DISPLAY)
        buffer_show();
    }else if(buffer[0] == MENU_TEXT_DISPLAY)
        buffer_stats(buffer);
    else if (buffer[0] == MENU_EXIT)
        printf("Exiting the program\n");
    else
        printf("'%c' is an invalid option.\n", buffer[0]);
 
    return 0;
}

void buffer_save(char b[], int t){
    
    for(int i = 0; i < BUFFER_MAXSIZE; i++) b[i] = EOF;
    
    char c;
    int len = 0;
    while((c = getchar()) != t){
        if(len < BUFFER_MAXSIZE-2){
            b[len] = c;
            len++;
        }
        b[BUFFER_MAXSIZE-1] = len;
    }  
}

void buffer_show(){
    int i = 0;
    while(buffer[i] != EOF){
        printf("buffer[%d]:\t%c\n", i, buffer[i]);
        i++;
    }
}

void menu(){
    printf("Select one of the options:\n");
    printf("  %c:\tInsert text\n", MENU_TEXT_INSERT);
    printf("  %c:\tDisplay text\n", MENU_TEXT_DISPLAY);
    printf("  %c:\tExit the program\n", MENU_EXIT);

    buffer_save(buffer, CHAR_NEWLINE);
}

void buffer_stats(char b[]){
 
    int char_count = 0, row_count = 0, word_count = 0, c = EOF;
    int prev_char = EOF;

    for(char_count = 0; 1000; char_count++){
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
