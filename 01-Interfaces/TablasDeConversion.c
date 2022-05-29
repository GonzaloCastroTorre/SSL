#include <stdio.h>
#include "Conversion.h"

void printTablas()
{
    printf("------------------------\n\n");

    printf("TABLA DE CONVERSION DE FAHRENHEIT A CELCIUS\n\n");

    Fahrenheit();

    printf("\n------------------------\n\n");

    printf("TABLA DE CONVERSION DE CELCIUS A FAHRENHEIT\n\n");

    Celcius();

    printf("\n------------------------");
}

int main ()
{
    /*printTablas imprime las tablas que pasan la temperatura de Fahrenheit
    a Celcius y de Celcius a Fahrenheit*/
    printTablas();
    
    return 0;
}