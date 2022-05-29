#include <stdio.h>
#include "Conversion.h"
double deFahrenheitACelcius(double fahr)
{
    return (5.0*(fahr-32))/9.0;
}

double deCelciusAFahrenheit(double cels)
{
    return ((cels*9.0)/5.0)+32;
}

void printFila(int temperatura,double funcionDeTranformacion(double))
{
    printf("%3d %6.1f\n", temperatura, funcionDeTranformacion(temperatura));
}

void printFilas (int tempMinima, int tempMaxima, int paso, double funcionDeTransformacion(double))
{   
    for(int temp = tempMinima; temp <= tempMaxima; temp = temp + paso)
        printFila(temp, funcionDeTransformacion);
}

void Fahrenheit()
{
    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP = 20;

    printFilas(LOWER, UPPER, STEP, deFahrenheitACelcius);
}

void Celcius()
{
    const int TEMPBAJA = -20;
    const int TEMPALTA = 150;
    const int PASO = 10;
    printFilas(TEMPBAJA, TEMPALTA, PASO, deCelciusAFahrenheit);
}
