#include <stdio.h>

#define CHAR_a          97
#define CHAR_z          122
#define CHAR_A          65
#define CHAR_Z          90
#define CHAR_NEWLINE    10
#define CHAR_SPACE      32

void count_words(){
    
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

// 1. RECEIVE AN INPUT OF TEXT AND COPY EACH WORK TO ARRAYS
// 2. PRINT THE LONGEST LINE
// 3. PRINT HISTOGRAM OF LENGH OF WORDS
// 4. PRINT HISTOGRAM OF FREEQUENCY OF APPEARING CHARS

int main() {
    count_words();
    return 0;
}
