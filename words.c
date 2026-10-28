#include <stdio.h>

#define a           97
#define z           122
#define A           65
#define Z           90
#define NEWLINE     10
#define SPACE       32

#define INSERT      49      //ASCII: 1
#define DISPLAY     50      //ASCII: 2
#define STATS       51      //ASCII: 3
#define EXIT        57      //ASCII: 9

#define MAXSIZE     10000

char menu();
void show();
void stats();
void save();

char choice;
char input[MAXSIZE];

int main() {

    for(int i = 0; i < MAXSIZE; i++) input[i] = EOF;
   
    while((choice = menu()) != EXIT){
        if(choice == NEWLINE)           ;
        else if(choice == INSERT)  save();
        else if(choice == DISPLAY) show();
        else if(choice == STATS)   stats();
        else                       printf("%c, is an invalid choice\n", choice);
    } 
    return 0;
}

void save(){
    
    for(int i = 0; i < MAXSIZE; i++) input[i] = EOF;
    
    char c;
    int i = 0;
    while((c = getchar()) != EOF){
        input[i] = c;
        i++;
    }
    clearerr(stdin);
}

void show(){
    int i = 0;
    while(input[i] != EOF){
        printf("[%d]:\t%c\n", i, input[i]);
        i++;
    }
}

char menu(){
    printf("__________________________\nSelect one of the options:\n");
    printf("  %c.\tInsert text\n",      INSERT);
    printf("  %c.\tDisplay text\n",     DISPLAY);
    printf("  %c.\tCalculate text\n",   STATS);
    printf("  %c.\tExit\n\n",           EXIT);

    char t, c;
    while((t = getchar()) != '\n')
        c = t;
    
    return c;     
}

void stats(){

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
