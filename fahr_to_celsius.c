#include <stdio.h>

#define LOWER           0
#define UPPER           360
#define INTERVAL        20

void fahr_to_celsius(int min, int max, int interval){

    printf("\nFahrenheit\t>\tCelsius\n________________________________\n");
    
    for(int fahr = min; fahr <= max ; fahr += interval){
        float celsius = (5.0 * (fahr - 32) / 9);
        printf("%4d\t\t>\t%6.2f\n", fahr, celsius);
    }

    printf("________________________________\n\n");
}

int main() {

    fahr_to_celsius(LOWER, UPPER, INTERVAL);
    return 0;
}
