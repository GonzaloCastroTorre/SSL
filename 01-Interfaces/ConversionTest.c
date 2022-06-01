#include <stdio.h>
#include <assert.h>
#include "Conversion.h"


int main ()
{
    assert(Fahrenheit(14) == -10 );
    puts("14 Farenheite son -10 Celcius");

    assert(Fahrenheit(23) == -5 );
    puts("23 Farenheite son -5 Celcius");

    assert(Fahrenheit(32) == 0 );
    puts("32 Farenheite son 0 Celcius");

    assert(Fahrenheit(41) == 5 );
    puts("41 Farenheite son 5 Celcius");

    assert(Celcius(-10) == 14);
    puts("-10 Celcius son 14 Farenheite");

    assert(Celcius(-5) == 23);
    puts("-5 Celcius son 23 Farenheite");

    assert(Celcius(0) == 32);
    puts("0 Celcius son 32 Farenheite");

    assert(Celcius(5) == 41);
    puts("5 Celcius son 41 Farenheite");
    
    printf("todo OK");
    return 0;
}
