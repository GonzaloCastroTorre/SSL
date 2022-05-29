#include <stdio.h>
#include <assert.h>

double pruebaFahrACel(double fahr)
{
    return (5.0*(fahr-32))/9.0;
}

double pruebaCelAFahr(double cels)
{
    return ((cels*9.0)/5.0)+32;
}


int main ()
{
    assert(pruebaFahrACel(14) == -10 );
    puts("14 Farenheite son -10 Celcius");

    assert(pruebaFahrACel(23) == -5 );
    puts("23 Farenheite son -5 Celcius");

    assert(pruebaFahrACel(32) == 0 );
    puts("32 Farenheite son 0 Celcius");

    assert(pruebaFahrACel(41) == 5 );
    puts("41 Farenheite son 5 Celcius");

    assert(pruebaCelAFahr(-10) == 14);
    puts("-10 Celcius son 14 Farenheite");

    assert(pruebaCelAFahr(-5) == 23);
    puts("-5 Celcius son 23 Farenheite");

    assert(pruebaCelAFahr(0) == 32);
    puts("0 Celcius son 32 Farenheite");

    assert(pruebaCelAFahr(5) == 41);
    puts("5 Celcius son 41 Farenheite");
    
    printf("todo OK");
    return 0;
}
