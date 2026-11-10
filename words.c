#include <stdio.h>
#include <limits.h>

#define MAXSIZE         UINT_MAX
#define MAXWORDS        85
#define PAGESIZE        40 
#define T_CYAN          "\033[44m\033[37m"          //TERMINAL STYLING STUFF
#define T_DARK          "\033[38;5;51;48;5;234m"
#define T_END           "\033[0m"
#define T_CHAR_CR       "\xE2\x86\xB5"
#define T_BACKSPACE     "\033[1A\r\033[K"
#define T_UP            "\033[1A"
#define T_HORIZ_ABS     "\033[49G"
#define T_ERASE_LINE    "\033[K"
#define T_DOWN          "\033[1B"

void write(char method);
void tokenize();
void show(char object);
void stats();

static char choice;
static unsigned char input[MAXSIZE] = { '\0' };
unsigned short token[MAXWORDS][3] = { { '\0' } };
enum choices { 
    INSERT              = '1'
    ,APPEND             = '2'
    ,TOKENIZE           = '3'
    ,DISPLAY_INPUT      = '4'
    ,DISPLAY_TOKENS     = '5'
    ,STATS              = '6'
    ,EXIT               = '9' 
};

void menu(){
    char t;
    extern char choice;
    printf(" %s+---------------------------------------------+%s" "\n", T_CYAN,                 T_END  );
    printf(" %s| Select one of the following TEXT options    |%s\n",    T_CYAN,                 T_END  );
    printf(" %s+---------------------------------------------+%s\n",    T_CYAN,                 T_END  );
    printf(" %s|  %c. Write new                               |%s\n",   T_CYAN, INSERT,         T_END  );
    printf(" %s|  %c. Append                                  |%s\n",   T_CYAN, APPEND,         T_END  );
    printf(" %s|  %c. Tokenize                                |%s\n",   T_CYAN, TOKENIZE,       T_END  );
    printf(" %s|  %c. Show Input                              |%s\n",   T_CYAN, DISPLAY_INPUT,  T_END  );
    printf(" %s|  %c. Show Tokens                             |%s\n",   T_CYAN, DISPLAY_TOKENS, T_END  );
    printf(" %s|  %c. Show Stats                              |%s\n",   T_CYAN, STATS,          T_END  );
    printf(" %s|  %c  Exit                                    |%s\n",   T_CYAN, EXIT,           T_END  );
    printf(" %s+---------------------------------------------+%s\n\n",  T_CYAN,                 T_END  );
    while((t = getchar()) != '\n') { choice = t; printf("%s",           T_BACKSPACE); }
}

int main() {
    extern char choice;
    while(1){
        menu();
        if      (choice              == EXIT)               return 0;
        else if (choice              == INSERT)             write(choice);
        else if (choice              == APPEND)             write(choice);
        else if (choice              == TOKENIZE)           tokenize();
        else if (choice              == STATS)              stats();
        else if (choice              == DISPLAY_INPUT)      show(choice);
        else if (choice              == DISPLAY_TOKENS)     show(choice);
        else                                                printf(" \"%c\" is an invalid option\n", choice);
    } 
}

void write(char method){
    char c;
    unsigned int i = 0;
    if      (method == INSERT);
    else if (method == APPEND) while(input[i] != '\0') i++;
    else                        { printf(" \"%d\", is an invalid write method\n", method); return; }

    while((c = getchar()) != EOF){
        input[i] = c;
        i++;
    }
    input[i] = '\0';
    clearerr(stdin);
}

void tokenize(){
    unsigned char chr, prev;
    unsigned short id = 0, start, length;
    for(unsigned short i = 0; ((chr = input[i]) != '\0'); i++){
        if(((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) && (prev < 'A' || ((prev > 'Z' && prev < 'a') && prev > 'z'))){
            if(id < MAXWORDS-1){
                start = i;
                length = 1;
                token[id][0] = id;
                token[id][1] = start;
                token[id][2] = length;
                id++;
            }else{ break; }
        }else if ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) token[id-1][2]++;
        prev = chr;
    }
    token[id][2] = '\0';
}

void show(char object){
    if(input[0] == '\0') printf("%s\n", "no data is available");
    else if(object == DISPLAY_INPUT){
        unsigned int i, page = 1;
        printf(" %s+-------------+----------------+------+-------+%s\n", T_DARK, T_END);
        printf(" %s| array[n]    | address        | char | value |%s\n", T_DARK, T_END);
        printf(" %s+-------------+----------------+------+-------+%s\n", T_DARK, T_END);
        for(i = 0; i < (page * PAGESIZE) && input[i] != '\0'; i++){
            printf(" %s|[%10d] | %-10p | %-4d | %-6s|%s"
                , T_DARK
                , i
                , (void*)&input[i]
                , input[i]
                , (input[i] == '\n' ? T_CHAR_CR "     " : (char[]){ input[i], '\0' })
                , T_END
            );
            if(i == (page * PAGESIZE) - 1){ 
                printf(" press '+' & ENTER for more.. ");
                unsigned char t;
                while((t = getchar()) != '\n') 
                    if(t == '+'){ page++; printf("\r%s%s%s%s\r", T_UP, T_HORIZ_ABS, T_ERASE_LINE, T_DOWN);} else break;
            }else printf("\n");
        }
        printf(" %s+-------------+----------------+------+-------+%s\n\n", T_DARK, T_END);
    }else if(object == DISPLAY_TOKENS){
        tokenize();
        printf(" %s+-------------+-------------------------------+%s\n", T_DARK, T_END);
        printf(" %s| token[n]    | data                          |%s\n", T_DARK, T_END);
        printf(" %s+-------------+-------------------------------+%s\n", T_DARK, T_END);
        for(unsigned short r = 0; token[r][2] != '\0'; r++){
            printf(" %s|[%10d] | ", T_DARK, token[r][0]);
            for(unsigned short i = token[r][1]; i < (token[r][1] + token[r][2]); i++){ printf("%c", input[i]); }
            for(unsigned short i = 0; i < (30 - token[r][2]); i++){ printf(" "); } printf("|%s\n", T_END);
        }
        printf(" %s+-------------+-------------------------------+%s\n\n", T_DARK, T_END);
    }
}

void stats(){
    unsigned int rows = 0, words = 0, chars = 0;
    char chr = '\0', prev;
    printf(" %s+---------------------------------------------+%s\n", T_DARK, T_END);
    printf(" %s| Stats                                       |%s\n", T_DARK, T_END);
    printf(" %s+---------------------------------------------+%s\n", T_DARK, T_END);
    for(chars = 0; (chr = input[chars]) != '\0'; chars++){
        if(chr == '\n') rows++;
        if(((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) && (prev < 'A' || ((prev > 'Z' && prev < 'a') && prev > 'z'))) ++words;
        prev = chr;
    }
    printf(" %s| Chars: %-36d |%s\n" " %s| Rows:  %-36d |%s\n" " %s| Words: %-36d |%s\n", T_DARK, chars, T_END, T_DARK, rows, T_END, T_DARK, words, T_END);
    printf(" %s+---------------------------------------------+%s\n\n", T_DARK, T_END);
}
