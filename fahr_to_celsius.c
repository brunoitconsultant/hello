#include <stdio.h>

void fahr_to_celsius(int min, int max, int interval){

    printf("\nFahrenheit\t>\tCelsius\n________________________________\n");

    for(int fahr = min; fahr <= max ; fahr += interval){
        int celsius = (5 * (fahr - 32) / 9);
        printf("%d\t\t>\t%d\n", fahr, celsius);
    }
    
    printf("________________________________\n\n");
}


int main() {
    fahr_to_celsius(0, 300, 20);   
    return 0;
}
