#include <stdio.h>
#include <limits.h>

#define MAXSIZE     UINT_MAX
#define PAGESIZE    40 

void write(char method);
void show();
void stats();

enum choices { INSERT = '1', APPEND = '2', STATS = '3', DISPLAY = '4', EXIT = '9' };
static char choice;
static const char TERMINATOR = '\0', NEWLINE = '\n';
static char input[MAXSIZE] = { TERMINATOR };

void menu(){
    char t;
    extern char choice;
    printf("%s", " \033[44m\033[37m+---------------------------------------------+\033[0m" "\n"     );
    printf(" \033[44m\033[37m| Select one of the options                   |\033[0m\n"              );
    printf(" \033[44m\033[37m+---------------------------------------------+\033[0m\n"              );
    printf(" \033[44m\033[37m|  %c. New text                                |\033[0m\n",    INSERT  );
    printf(" \033[44m\033[37m|  %c. Append to text                          |\033[0m\n",    APPEND  );
    printf(" \033[44m\033[37m|  %c. Stats                                   |\033[0m\n",    STATS   );
    printf(" \033[44m\033[37m|  %c. Display                                 |\033[0m\n",    DISPLAY );
    printf(" \033[44m\033[37m|  %c  Exit                                    |\033[0m\n",    EXIT    );
    printf(" \033[44m\033[37m+---------------------------------------------+\033[0m\n\n"            );
    while((t = getchar()) != NEWLINE) { choice = t; printf("\033[1A\r\033[K"); }
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
    else if (method == APPEND)  for(unsigned int b = 0; b < MAXSIZE && input[b] != TERMINATOR; b++) i = b++;
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
    printf(" +-------------+----------------+------+-------+\n");
    printf(" | array[n]    | address        | char | value |\n");
    printf(" +-------------+----------------+------+-------+\n");    
    for(i = 0; i < (page * PAGESIZE) && input[i] != TERMINATOR; i++){      
        printf(" |[%10d] | %-10p | %-4d | %-6s|"
            , i
            , (void*)&input[i]
            , input[i]
            , (input[i] == NEWLINE ? "\xE2\x86\xB5     " : (char[]){ input[i], TERMINATOR })
        );
        if(i == (page * PAGESIZE) - 1){ 
            printf(" + for more.. ");
            unsigned char t;
            while((t = getchar()) != NEWLINE) if(t == '+'){ page++; printf("\r\033[1A\033[49G\033[K\033[1B\r");} else break;
        }else printf("\n");
    }    
    printf(" +-------------+----------------+------+-------+\n\n");
}

void stats(){
    unsigned int rows = 1, words = 0, chars;
    char chr = TERMINATOR, prev;
    printf(" +---------------------------------------------+\n");
    printf(" | Stats                                       |\n");
    printf(" +---------------------------------------------+\n");    
    for(chars = 0; (chr = input[chars]) != TERMINATOR; chars++){
        if(chr == NEWLINE) rows++;
        if((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
            if((chr < 'a' || chr > 'z') || (chr < 'A' && chr > 'Z')) words++;
        prev = chr;
    }
    printf(" | Chars: %-36d |\n"
       " | Rows:  %-36d |\n" " | Words: %-36d |\n", chars, rows, words);
    printf(" +---------------------------------------------+\n\n");
}
