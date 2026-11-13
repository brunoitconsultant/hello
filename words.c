#include <stdio.h>
#include <limits.h>

#define MAX_CHARS       INT_MAX
#define MAX_WORDS       320'000'000 
#define MAX_PAGESIZE    50 
#define T_CYAN          "\033[44m\033[37m"
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
void atoi();
void display(char choice);

static char choice;
static unsigned char input[MAX_CHARS]   = { '\0' };
unsigned short token[MAX_WORDS][3]      = { { '\0' } };

enum choices { 
    INSERT              = '1'
    ,APPEND             = '2'
    ,TOKENIZE           = '3'
    ,ATOI               = '4'
    ,DISPLAY_STATS      = '5'
    ,DISPLAY_INPUT      = '6'
    ,DISPLAY_TOKENS     = '7'
    ,EXIT               = '9' 
};

void menu(){
    char t;
    extern char choice;
    printf(" %s+---------------------------------------------+%s" "\n", T_CYAN,                 T_END  );
    printf(" %s| Pick one of the following operations:       |%s\n",    T_CYAN,                 T_END  );
    printf(" %s+---------------------------------------------+%s\n",    T_CYAN,                 T_END  );
    printf(" %s|  %c. Write new                               |%s\n",   T_CYAN, INSERT,         T_END  );
    printf(" %s|  %c. Append                                  |%s\n",   T_CYAN, APPEND,         T_END  );
    printf(" %s|  %c. Tokenize                                |%s\n",   T_CYAN, TOKENIZE,       T_END  );
    printf(" %s|  %c. ATOI (ASCII to Int)                     |%s\n",   T_CYAN, ATOI,           T_END  );
    printf(" %s|  -------------------------------------------|%s\n",    T_CYAN,                 T_END  );
    printf(" %s|  %c. Display Statistics                      |%s\n",   T_CYAN, DISPLAY_STATS,  T_END  );
    printf(" %s|  %c. Display Input                           |%s\n",   T_CYAN, DISPLAY_INPUT,  T_END  );
    printf(" %s|  %c. Display Tokens                          |%s\n",   T_CYAN, DISPLAY_TOKENS, T_END  );
    printf(" %s|  -------------------------------------------|%s\n",    T_CYAN,                 T_END  );
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
        else if (choice              == ATOI)               atoi();
        else if (choice              == DISPLAY_STATS)      display(choice);
        else if (choice              == DISPLAY_INPUT)      display(choice);
        else if (choice              == DISPLAY_TOKENS)     display(choice);
        else                                                printf(" \"%c\" is an invalid option\n", choice);
    } 
}

void write(char method){
    char c;
    unsigned int i = 0;
    if      (method == INSERT)  ;
    else if (method == APPEND)  while(input[i] != '\0') i++;
    else                        { printf(" \"%d\", is an invalid write method\n", method); return; }
    
    while((c = getchar()) != EOF) if((i + 1) < MAX_CHARS) input[i++] = c;
    input[i] = '\0';
    clearerr(stdin);
}

void tokenize(){
    unsigned char chr, prev = '\0';
    unsigned int id = 0;
    for(unsigned int i = 0; ((chr = input[i]) != '\0'); i++){
        if(((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) && (prev < 'A' || ((prev > 'Z' && prev < 'a') && prev > 'z'))){
            if(id < (MAX_WORDS - 1)){
                token[id][0] = id;
                token[id][1] = i;
                token[id][2] = 1;
                id++;
            }else break;
        }else if ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) token[id-1][2]++;
        prev = chr;
    }
    token[id][2] = '\0';
}

void atoi(){ 
    unsigned atoi = 0;
    for(unsigned int i = 0; input[i] != '\0'; i++)
        if(input[i] >= '0' && input[i] <= '9') atoi = (10 * atoi) + (input[i] - '0');
    printf("_________atoi: %d\n", atoi);
}

void display(char choice){
    unsigned int pos, page = 1;
    if(input[0] == '\0') printf(" %s\n", "no data is available");
    else if(choice == DISPLAY_INPUT){
        printf(" %s+-------------+----------------+------+-------+%s\n", T_DARK, T_END);
        printf(" %s| array[n]    | address        | char | value |%s\n", T_DARK, T_END);
        printf(" %s+-------------+----------------+------+-------+%s\n", T_DARK, T_END);
        for(pos = 0; pos < (page * MAX_PAGESIZE) && input[pos] != '\0'; pos++){
            printf(" %s|[%10d] | %-10p | %-4d | %-6s|%s"
                , T_DARK
                , pos
                , (void*)&input[pos]
                , input[pos]
                , (input[pos] == '\n' ? T_CHAR_CR "     " : (char[]){ input[pos], '\0' })
                , T_END
            );
            if(pos == (page * MAX_PAGESIZE) - 1){ 
                printf(" press '+' & ENTER for more.. ");
                unsigned char t;
                while((t = getchar()) != '\n') 
                    if(t == '+'){ page++; printf("\r%s%s%s%s\r", T_UP, T_HORIZ_ABS, T_ERASE_LINE, T_DOWN);} else break;
            }else printf("\n");
        }
        printf(" %s+-------------+----------------+------+-------+%s\n\n", T_DARK, T_END);
    }else if(choice == DISPLAY_TOKENS){
        tokenize();
        printf(" %s+-------------+-------------------------------+%s\n", T_DARK, T_END);
        printf(" %s| token[n]    | data                          |%s\n", T_DARK, T_END);
        printf(" %s+-------------+-------------------------------+%s\n", T_DARK, T_END);
        for(pos = 0; pos < (page * MAX_PAGESIZE) && token[pos][2] != '\0'; pos++){
            printf(" %s|[%10d] | ", T_DARK, token[pos][0]);
            for(unsigned short i = token[pos][1]; i < (token[pos][1] + token[pos][2]); i++){ printf("%c", input[i]); }
            for(unsigned short i = 0; i < (30 - token[pos][2]); i++){ printf(" "); } printf("|%s", T_END);
            if(pos == (page * MAX_PAGESIZE) - 1){ 
                printf(" press '+' & ENTER for more.. ");
                unsigned char t;
                while((t = getchar()) != '\n') 
                    if(t == '+'){ page++; printf("\r%s%s%s%s\r", T_UP, T_HORIZ_ABS, T_ERASE_LINE, T_DOWN);} else break;
            }else printf("\n");
        }
        printf(" %s+-------------+-------------------------------+%s\n\n", T_DARK, T_END);
    }else if(choice == DISPLAY_STATS){
        unsigned int rows = 0, words = 0, chars;
        unsigned char chr, prev = '\0';
        printf(" %s+---------------------------------------------+%s\n", T_DARK, T_END);
        printf(" %s| Stats                                       |%s\n", T_DARK, T_END);
        printf(" %s+---------------------------------------------+%s\n", T_DARK, T_END);
        for(chars = 0; (chr = input[chars]) != '\0'; chars++){
            if(chr == '\n') rows++;
            if(((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) && (prev < 'A' || ((prev > 'Z' && prev < 'a') && prev > 'z'))) ++words;
            prev = chr;
        }
        printf(" %s| Chars: %-36d |%s\n %s| Rows:  %-36d |%s\n %s| Words: %-36d |%s\n", T_DARK, chars, T_END, T_DARK, rows, T_END, T_DARK, words, T_END);
        printf(" %s+---------------------------------------------+%s\n\n", T_DARK, T_END);
    }
}
