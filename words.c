#include <stdio.h>

#define _a          97
#define _z          122
#define _A          65
#define _Z          90
#define _NEWLINE    10
#define _SPACE      32

#define _INSERT     49      //ASCII: 1
#define _DISPLAY    50      //ASCII: 2
#define _STATS      51      //ASCII: 3
#define _EXIT       57      //ASCII: 9

#define _MAXSIZE    10000

char menu();
void show();
void stats();
void save();
void clear();

char choice;
char input[_MAXSIZE];

int main() {
 
    clear();

    while((choice = menu()) != _EXIT){
        if(choice == _NEWLINE)      ;
        else if(choice == _INSERT){ clear(); save(); }
        else if(choice == _DISPLAY) show();
        else if(choice == _STATS)   stats();
        else                        printf("%c, is an invalid choice\n", choice);
    } 
    return 0;
}

void clear(){
    for(int i = 0; i < _MAXSIZE; i++) input[i] = EOF;
}

void save(){    
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
    printf("  %c.\tInsert text\n",      _INSERT);
    printf("  %c.\tDisplay text\n",     _DISPLAY);
    printf("  %c.\tCalculate text\n",   _STATS);
    printf("  %c.\tExit\n\n",           _EXIT);

    char t, c;
    while((t = getchar()) != '\n')
        c = t;
    
    return c;     
}

void stats(){

    int c_cnt = 0, r_cnt = 0, w_cnt = 0;
    int c = EOF, prev_c;

    for(c_cnt = 0; (c = input[c_cnt]) != EOF; c_cnt++){
        if(c_cnt == 0 || c == _NEWLINE){
            r_cnt++;
        }
        if((prev_c >= _a && prev_c <= _z) || (prev_c >= _A && prev_c <= _Z)){
            if((c < _a || c > _z) || (c < _A && c > _Z))
                w_cnt++;
        }
        prev_c = c;
    }
    printf("\nChars: %d\nRows: %d\nWords: %d\n", c_cnt, r_cnt, w_cnt);
}
