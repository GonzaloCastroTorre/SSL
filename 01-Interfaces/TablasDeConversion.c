#include <stdio.h>
#include "Conversion.h"

void printFila(int temperatura,double funcionDeTranformacion(double))
{
    printf("%3d %6.1f\n", temperatura, funcionDeTranformacion(temperatura));
}

void printFilas (int tempMinima, int tempMaxima, int paso, double funcionDeTransformacion(double))
{   
    for(int temp = tempMinima; temp <= tempMaxima; temp = temp + paso)
        printFila(temp, funcionDeTransformacion);
}

void TablaFahrenheit()
{
    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP = 20;

    printFilas(LOWER, UPPER, STEP, Fahrenheit);
}

void TablaCelcius()
{
    const int TEMPBAJA = -20;
    const int TEMPALTA = 150;
    const int PASO = 10;
    printFilas(TEMPBAJA, TEMPALTA, PASO, Celcius);
}


void printTablas()
{
    printf("------------------------\n\n");

    printf("TABLA DE CONVERSION DE FAHRENHEIT A CELCIUS\n\n");

    TablaFahrenheit();

    printf("\n------------------------\n\n");

    printf("TABLA DE CONVERSION DE CELCIUS A FAHRENHEIT\n\n");

    TablaCelcius();

    printf("\n------------------------");
}

int main ()
{
    /*printTablas imprime las tablas que pasan la temperatura de Fahrenheit
    a Celcius y de Celcius a Fahrenheit*/
    printTablas();
  
    return 0;
}