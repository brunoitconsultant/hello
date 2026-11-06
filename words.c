#include <stdio.h>
#include <limits.h>

#define MAXSIZE             UINT_MAX
#define PAGESIZE            40
#define TERM_COLOUR_CYAN    "\033[44m\033[37m"
#define TERM_COLOUR_DARK    "\033[38;5;51;48;5;234m"
#define TERM_COLOUR_END     "\033[0m"
#define TERM_CHAR_CR        "\xE2\x86\xB5"
#define TERM_BACKSPACE      "\033[1A\r\033[K"
#define TERM_CR             "\r"
#define TERM_CUR_UP         "\033[1A"
#define TERM_CUR_HORIZ_ABS  "\033[49G"
#define TERM_ERASE_LINE     "\033[K"
#define TERM_CUR_DOWN       "\033[1B"

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
    printf(" %s+---------------------------------------------+%s" "\n", TERM_COLOUR_CYAN,            TERM_COLOUR_END  );
    printf(" %s| Select one of the following TEXT options    |%s\n",    TERM_COLOUR_CYAN,            TERM_COLOUR_END  );
    printf(" %s+---------------------------------------------+%s\n",    TERM_COLOUR_CYAN,            TERM_COLOUR_END  );
    printf(" %s|  %c. Write new                               |%s\n",   TERM_COLOUR_CYAN, INSERT,    TERM_COLOUR_END  );
    printf(" %s|  %c. Append to existing                      |%s\n",   TERM_COLOUR_CYAN, APPEND,    TERM_COLOUR_END  );
    printf(" %s|  %c. Show                                    |%s\n",   TERM_COLOUR_CYAN, DISPLAY,   TERM_COLOUR_END  );
    printf(" %s|  %c. Calculate stats                         |%s\n",   TERM_COLOUR_CYAN, STATS,     TERM_COLOUR_END  );
    printf(" %s|  %c  Exit                                    |%s\n",   TERM_COLOUR_CYAN, EXIT,      TERM_COLOUR_END  );
    printf(" %s+---------------------------------------------+%s\n\n",  TERM_COLOUR_CYAN,            TERM_COLOUR_END  );
    while((t = getchar()) != NEWLINE) { choice = t; printf("%s",        TERM_BACKSPACE); }
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
    unsigned int i;
   
    if      (method == INSERT)  i = 0;
    else if (method == APPEND)  for(unsigned int b = 0 + 1; b < MAXSIZE && input[b] != TERMINATOR; b++) i = ++b;
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
    printf(" %s+-------------+----------------+------+-------+%s\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
    printf(" %s| array[n]    | address        | char | value |%s\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
    printf(" %s+-------------+----------------+------+-------+%s\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
    if(input[0] == TERMINATOR) printf(" %s| %-43s |%s\n", TERM_COLOUR_DARK, "no data is available", TERM_COLOUR_END);
    else{
        for(i = 0; i < (page * PAGESIZE) && input[i] != TERMINATOR; i++){
            printf(" %s|[%10d] | %-10p | %-4d | %-6s|%s"
                , TERM_COLOUR_DARK
                , i
                , (void*)&input[i]
                , input[i]
                , (input[i] == NEWLINE ? TERM_CHAR_CR "     ": (char[]){ input[i], TERMINATOR })
                , TERM_COLOUR_END
            );
            if(i == (page * PAGESIZE) - 1){ 
                printf(" press '+' & ENTER for more.. ");
                unsigned char t;
                while((t = getchar()) != NEWLINE) 
                    if(t == '+'){ page++; printf("%s%s%s%s%s%s", TERM_CR, TERM_CUR_UP, TERM_CUR_HORIZ_ABS, TERM_ERASE_LINE, TERM_CUR_DOWN, TERM_CR);} else break;
            }else printf("\n");
        }
    }
    printf(" %s+-------------+----------------+------+-------+%s\n\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
}

void stats(){
    unsigned int rows = 1, words = 0, chars;
    char chr = TERMINATOR, prev;
    printf(" %s+---------------------------------------------+%s\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
    printf(" %s| Stats                                       |%s\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
    printf(" %s+---------------------------------------------+%s\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
    for(chars = 0; (chr = input[chars]) != TERMINATOR; chars++){
        if(chr == NEWLINE) rows++;
        if((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
            if((chr < 'a' || chr > 'z') || (chr < 'A' && chr > 'Z')) words++;
        prev = chr;
    }
    printf(" %s| Chars: %-36d |%s\n" " %s| Rows:  %-36d |%s\n" " %s| Words: %-36d |%s\n", TERM_COLOUR_DARK, chars, TERM_COLOUR_END, TERM_COLOUR_DARK, rows, TERM_COLOUR_END, TERM_COLOUR_DARK, words, TERM_COLOUR_END);
    printf(" %s+---------------------------------------------+%s\n\n", TERM_COLOUR_DARK, TERM_COLOUR_END);
}
