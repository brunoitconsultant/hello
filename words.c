#include <stdio.h>
#include <limits.h>

#define MAXSIZE         UINT_MAX
#define PAGESIZE        40
//TERMINAL STYLING STUFF
#define T_CYAN          "\033[44m\033[37m"
#define T_DARK          "\033[38;5;51;48;5;234m"
#define T_END           "\033[0m"
#define T_CHAR_CR       "\xE2\x86\xB5"
#define T_BACKSPACE     "\033[1A\r\033[K"
#define T_CR            "\r"
#define T_UP            "\033[1A"
#define T_HORIZ_ABS     "\033[49G"
#define T_ERASE_LINE    "\033[K"
#define T_DOWN          "\033[1B"

void write(char method);
void show();
void stats();

enum choices { INSERT = '1', APPEND = '2', DISPLAY = '3', STATS = '4', EXIT = '9' };
static char choice;
static const char TERMINATOR = '\0', NEWLINE = '\n';
static char input[MAXSIZE] = { TERMINATOR };

void menu(){
    char t;
    extern char choice;
    printf(" %s+---------------------------------------------+%s" "\n", T_CYAN,            T_END  );
    printf(" %s| Select one of the following TEXT options    |%s\n",    T_CYAN,            T_END  );
    printf(" %s+---------------------------------------------+%s\n",    T_CYAN,            T_END  );
    printf(" %s|  %c. Write new                               |%s\n",   T_CYAN, INSERT,    T_END  );
    printf(" %s|  %c. Append to existing                      |%s\n",   T_CYAN, APPEND,    T_END  );
    printf(" %s|  %c. Show                                    |%s\n",   T_CYAN, DISPLAY,   T_END  );
    printf(" %s|  %c. Calculate stats                         |%s\n",   T_CYAN, STATS,     T_END  );
    printf(" %s|  %c  Exit                                    |%s\n",   T_CYAN, EXIT,      T_END  );
    printf(" %s+---------------------------------------------+%s\n\n",  T_CYAN,            T_END  );
    while((t = getchar()) != NEWLINE) { choice = t; printf("%s",        T_BACKSPACE); }
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
        else                                        printf(" \"%c\" is an invalid option\n", choice);
    } 
}

void write(char method){
    char c;
    unsigned int i = 0;

    if      (method == INSERT);
    else if (method == APPEND) while(input[i] != TERMINATOR) i++;
    else                        { printf(" \"%d\", is an invalid write method\n", method); return; }

    while((c = getchar()) != EOF){
        input[i] = c;
        i++;
    }
    input[i] = TERMINATOR;
    clearerr(stdin);
}

void show(){
    unsigned int i, page = 1;
    printf(" %s+-------------+----------------+------+-------+%s\n", T_DARK, T_END);
    printf(" %s| array[n]    | address        | char | value |%s\n", T_DARK, T_END);
    printf(" %s+-------------+----------------+------+-------+%s\n", T_DARK, T_END);
    if(input[0] == TERMINATOR) printf(" %s| %-43s |%s\n", T_DARK, "no data is available", T_END);
    else{
        for(i = 0; i < (page * PAGESIZE) && input[i] != TERMINATOR; i++){
            printf(" %s|[%10d] | %-10p | %-4d | %-6s|%s"
                , T_DARK
                , i
                , (void*)&input[i]
                , input[i]
                , (input[i] == NEWLINE ? T_CHAR_CR "     ": (char[]){ input[i], TERMINATOR })
                , T_END
            );
            if(i == (page * PAGESIZE) - 1){ 
                printf(" press '+' & ENTER for more.. ");
                unsigned char t;
                while((t = getchar()) != NEWLINE) 
                    if(t == '+'){ page++; printf("%s%s%s%s%s%s", T_CR, T_UP, T_HORIZ_ABS, T_ERASE_LINE, T_DOWN, T_CR);} else break;
            }else printf("\n");
        }
    }
    printf(" %s+-------------+----------------+------+-------+%s\n\n", T_DARK, T_END);
}

void stats(){
    unsigned int rows = 0, words = 0, chars = 0;
    char chr = TERMINATOR, prev;
    printf(" %s+---------------------------------------------+%s\n", T_DARK, T_END);
    printf(" %s| Stats                                       |%s\n", T_DARK, T_END);
    printf(" %s+---------------------------------------------+%s\n", T_DARK, T_END);
    for(chars = 0; (chr = input[chars]) != TERMINATOR; chars++){
        if(chr == NEWLINE) rows++;
        if(((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) && (prev < 'A' || ((prev > 'Z' && prev < 'a') && prev > 'z'))) ++words;
        prev = chr;
    }
    printf(" %s| Chars: %-36d |%s\n" " %s| Rows:  %-36d |%s\n" " %s| Words: %-36d |%s\n", T_DARK, chars, T_END, T_DARK, rows, T_END, T_DARK, words, T_END);
    printf(" %s+---------------------------------------------+%s\n\n", T_DARK, T_END);
}
