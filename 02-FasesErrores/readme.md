En el siguiente trabajo se va a estar probando cada fase de la traducción que realiza un compilador sobre un programa, viendo que problema genera cada etapa.
Para realizar dicho trabajo, se va a estar usando el lenguaje C, con el compilador gcc versión 9.2.0 y el standard c18

1. Preprocesador

a. Se escribió el archivo hello2.c, una variante de hello.c, con el siguiente código:

#include <stdio.h>
int/*medio*/main(void){
 int i=42;
 prontf("La respuesta es %d\n");

b.  Preprocesar hello2.c, no compilar, y generar hello2.i. Analizar su contenido. ¿Qué conclusiones saca?

Este programa tiene estos errores: 
-Está mal escrito printf
-Falta la llave que cierra el main
-Se declara la variable i pero no se la usa
-a prontf se le está indicando que le va a pasar un entero para imprimir, pero no se le está pasando la referencia

A este programa se le ejecuta el comando: gcc -E Hello2.c -o Hello2.i
Lo que indica este comando es decirle al compilador que solamente preprocese el archivo Hello2.c, sin compilarlo, ensamblarlo ni linkearlo.
Al preprocesar este archivo, lo que hace es interpretar el encabezado, en este caso, el #include, y "copia y pega" el prototipo de cada una de las funciones definidas en la biblioteca stdio.h para que puedan ser utilizadas en el programa que desarrollamos, y también cambia todos los comentarios por un espacio. Luego, genera el archivo llamado Hello2.i, que se puede visualizar todo lo generado por el preprocesador.
En líneas generales, la mayoría de las funciones tienen el atributo (__dllimport__) y el atributo (__cdecl__). El primero indica que la función se está trayendo de la biblioteca stdio.h mientras que el segundo indica la forma en que se pasan los argumentos a la función (en este caso es la convención de C). Estos atributos son agregados por el compilador y no modifican la declaración de la función.

c.  Escribir hello3.c, una nueva variante:

int printf(const char * restrict s, ...);
int main(void){
int i=42;
 prontf("La respuesta es %d\n");

d. Investigar e indicar la semántica de la primera línea.

Semántica de la primera línea: (QUÉ SIGNIFICADO TRANSMITE)
Es una declaración de una función que está esperando:
-El primer argumento es un puntero a un char
-El const significa que puede apuntar a la variable s, pero  que no la va a modificar.
Es decir, s es un puntero de solo lectura
-s es el nombre de la variable
-s puede cambiar de objeto al cual apunta, pero como es un const, no puede modificar lo que hay dentro
-Restrict indica que s está apuntando a un objeto y que es al único al que se le va a apuntar, lo que permite optimizar al procesador

e. Preprocesar hello3.c, no compilar, y generar hello3.i. Buscar diferencias entre hello3.c y hello3.i.

Para generar Hello3.i, vuelvo a ejecutar el comando gcc -E Hello3.c -o Hello3.i. Las diferencias son que añade un encabezado con #:
# 1 "Hello3.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Hello3.c"
Este encabezado es información para el compilador.
Si se ejecuta el comando gcc -E Hello3.c -o Hello3.i -P, el agregado hace que los # desaparezcan, dejando el programa exactamente igual al que escribimos.

2. Compilación.

a. Compilar el resultado y generar hello3.s, no ensamblar.

Para poder compilar el programa sin ensamblar, se debe usar el comando: gcc -S Hello3.i -o Hello3.s. Al ejecutar el comando, en la terminal aparecen 2 mensajes, una advertencia y un error:
Hello3.i: In function 'main':
Hello3.i:4:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    4 |  prontf("La respuesta es %d\n");
      |  ^~~~~~
      |  printf
Hello3.i:4:2: error: expected declaration or statement at end of input 

El primer error, la advertencia, indica una declaración implícita de la función "prontf", y pregunta si se quiere referir a la función "printf". El segundo error indica que está faltando la llave de cierre del programa.

b. Corregir solo los errores, no los warnings, en el nuevo archivo hello4.c y empezar de nuevo, generar hello4.s, no ensamblar.

Se corrige el error de la llave de main y se compila el programa Hello4.c con el comando: gcc -S Hello4.c -o Hello4.s. El comando se ejecuta y se genera el archivo, por lo que se puede decir que el programa se compiló, por más de que exista un warning y no este declarada la función prontf. 

c. Leer hello4.s, investigar sobre lenguaje ensamblador, e indicar de formar sintética cual es el objetivo de ese código.

En el archivo Hello4.s, las primeras 4 líneas hacen referencia a definiciones, no es código ejecutable. LC0 es una constante de metacomandos que facilita la codificación.
En la línea 10 arranca la función main en la que le asigna una etiqueta en la línea 11. En la línea 13 (pushl %ebp) está empujando a la pila el registro que está en el base point. A cada función que invoquemos se le va a sumar a la pila. En la línea 16 (movl %esp, ebp) indica que la cima de la pila es la nueva base. En la línea 18 y 19 está generando espacio para la declaración de la variable i. En la línea 21 está guardando en la dirección que indica el registro de stack pointer (% esp) el valor 42 (en el programa representa a int i = 42), y en la línea 22 vuelve a hacer movimientos para poder llamar a la función prontf, que se encuentra en la línea 23. Luego, en la línea 24, el comando que se ejecuta (movl $0 %eax) indica que se está devolviendo un 0, que es lo que retorna la función main por convención. El signo $0 indica que es un literal, es decir, que es un valor definido, no una dirección de memoria, mientras que el % indica que es un registro. Sin embargo, el programa nunca se terminaría de ejecutar ya que no está definida la función prontf, aunque eso no impida que el programa se compile.

d. Ensamblar hello4.s en hello4.o, no vincular.

Para poder ensamblar se ejecuta el comando: gcc -c Hello4.s -o Hello4.o. Se logra generar el archivo Hello.o sin inconvenientes, y para poder visualizarlo se usó una extensión de visual studio que permite editar archivos hexadecimales. Dentro de este archivo .o, se encuentra todo el código assembler pero pasado en bytes, para que pueda ser interpretado por el microprocesador.

3. Vinculación

a. Vincular hello4.o con la biblioteca estándar y generar el ejecutable.

Para vincular el archivo Hello4.o, se ejecuta el comando: gcc Hello4.o -o Hello4.exe. En este caso no se especifica el paso de la vinculación, como si pasaba en otras fases, ya que al entregar un archivo .o, no queda otra fase más que la vinculación para generar el ejecutable. Al ejecutar el comando, en la terminal aparece el error:
e:/sintaxis/bin/../lib/gcc/mingw32/9.2.0/../../../../mingw32/bin/ld.exe: Hello4.o:Hello4.c:(.text+0x1e): undefined reference to `prontf'
collect2.exe: error: ld returned 1 exit status
Este error hace referencia a que no se encuentra definida la función prontf, lo que impide que se obtenga el ejecutable del programa. También, se interpreta que el programa que "expresa" el error es el ld.exe, que no es más que el propio vinculador del compilador mingw.

b. Corregir en hello5.c y generar el ejecutable. Solo corregir lo necesario para que vincule.

Como el error en la vinculación en el archivo Hello4.c era que no encontraba la función prontf (ya que estaba mal escrita), se cambió a printf para que el programa pueda vincular correctamente. Para ello, se ejecuta el comando: gcc Hello5.c -o Hello5.exe. En este caso, como no se especifica que fase de la ejecución es (preprocesar, compilar o vincular), el compilador entiende que deben ejecutarse todas y entrega el ejecutable.

c. Ejecutar y analizar el resultado.

Para ejecutar el archivo Hello5.exe, únicamente se escribe el nombre del archivo en la consola y automáticamente lo ejecuta. La salida del programa es "La respuesta es 4200880". La parte del string "La respuesta es" proviene de la cadena de caracteres que le pasamos a la función printf, y el numero 4200880 proviene de la referencia que le pasamos a la función printf. Al no aclarar el numero referenciado, toma cualquier locación de memoria, y el hecho de que los primeros 2 números coincidan con la variable i es pura coincidencia. Esto pasa ya que se está "rompiendo el contrato" establecido para printf con respecto a los argumentos que se le tiene que pasar con respecto a la cantidad de %d que tienen.

4. Corrección de Bug

a. Corregir en hello6.c y empezar de nuevo; verificar que funciona como se espera.

El único bug para corregir es el mencionado anteriormente, que es la salida del número que no es referenciado en la función printf. Para ello, a la función le agregamos la variable i. Nuevamente compilamos el programa totalmente para obtener el ejecutable con el comando: gcc Hello6.c -o Hello6.exe. Ahora, la salida del programa es "La respuesta es 42" 

5. Remoción de prototipo

a. Escribir hello7.c, una nueva variante:
int main(void){
 int i=42;
 printf("La respuesta es %d\n", i);
}

b. Explicar por qué funciona.

Cuando se compila y se genera el ejecutable con el comando: gcc Hello7.c -o Hello7.exe, en la terminal aparece una advertencia:
Hello7.c: In function 'main':
Hello7.c:3:2: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    3 |  printf("La respuesta es %d\n", i);
      |  ^~~~~~
Hello7.c:3:2: warning: incompatible implicit declaration of built-in function 'printf'
Hello7.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
  +++ |+#include <stdio.h>
    1 | int main(void){

Esta advertencia de acá está indicando que se está declarando, de forma implícita, la función printf. En este caso, gcc decide tomar esto como una advertencia ya que en versiones anteriores del compilador, estaban admitidas las declaraciones implícitas de funciones, pero fueron removidas.
También, advierte sobre que la declaración de printf es incompatible con la "built-in". Esta declaración built-in es una declaración propia del compilador sobre la función printf, ya que es tan común que decide darle un tratamiento especial. Y es principalmente por este motivo que el programa logra compilar y generar el ejecutable.
Además, la advertencia también incluye una nota, recomendando incluir la biblioteca <stdio.h>, que ya contiene definida la función printf.
Cabe destacar que cada compilador puede variar en la forma de tomar los inconvenientes. Es decir, otro compilador, como clang, lo puede tomar como un error y decidir no compilar el programa.

6. Compilación Separada: Contratos y Módulos

a. Escribir studio1.c (sí, studio1, no stdio) y hello8.c. La unidad de traducción studio1.c tiene una implementación de la función prontf, que es solo un wrappwer de la función estándar printf:
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}
La unidad de traducción hello8.c, muy similar a hello4.c, invoca a prontf, pero no incluye ningún header.
int main(void){
int i=42;
 prontf("La respuesta es %d\n", i);
}

b. Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de traducción (i.e., archivos fuente, archivos con extensión .c). Luego generar ese ejecutable y probarlo.

Con Hello8.c generado y studio1.c con la declaración de la función prontf, se ejecuta el comando: gcc Hello8.c -o Hello8.exe. Al ejecutar el comando, primero aparece una advertencia de que existe una declaración implícita de la función pronft, y luego aparece un error de vinculación, diciendo que no hay una referencia definida hacia la función prontf.
Sin embargo, si ejecutamos el siguiente comando: gcc Hello8.c studio1.c -o Hello8.exe, si genera el ejecutable, además de también generar una advertencias sobre declaraciones implícitas. Si ejecutamos Hello8.exe, la salida es la esperada: La respuesta es 42.
Lo que hace este último comando es indicarle al compilador que, valga la redundancia, compile ambos programas para generar sus respectivos archivos.o, y luego busque en cada uno con el linker las funciones que necesite. Es por esto que desaparece el problema del primer comando y, en este caso, logra generar el ejecutable.

c. Responder ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf? Justifique.

Si agregamos o eliminamos argumentos a la invocación, igualmente logra generar el ejecutable, además de también advertir sobre ciertas declaraciones implícitas. Esto pasa ya que, para empezar, el compilador toma de a un archivo a la vez para poder generar el archivo .o, eso explica por qué genera el error de las declaraciones implícitas. Por otro lado, una vez que tiene los archivos .o, el linker únicamente se encarga de vincular las funciones con su respectiva declaración, es decir, no le interesa si cumple con la cantidad de argumentos, sino que se abstrae de ese dato.
Agregando a lo anterior, esta es una situación de comportamiento indefinido, ya que, en lenguaje assembler, en la pila se le estarían pasando más o menos argumentos de los que toma la función, lo que provocaría un desbalanceo, y podría afectar tanto a la función actual, como al resto del programa. En este caso, como gcc con respecto a las funciones, logra generar el ejecutable, sin embargo, esto depende de cada compilador.
Con respecto a si le agregamos o sacamos argumentos, en este caso en particular, imprime un resultado. Si se le agregan argumentos, el resultado no se modifica. Sin embargo, si le sacamos argumentos (por ejemplo, el parámetro i), el resultado se va a ver afectado (por ejemplo, imprimir un numero cualquiera).

d. Revisitar el punto anterior, esta vez utilizando un contrato de interfaz en un archivo header.
  i. Escribir el contrato en studio.h.
  #ifndef _STUDIO_H_INCLUDED_
  #define _STUDIO_H_INCLUDED_
  void prontf(const char*, int);
  #endif

  ii. Escribir hello9.c, un cliente que sí incluye el contrato.
  #include "studio.h" // Interfaz que importa
  int main(void){
  int i=42;
  prontf("La respuesta es %d\n", i);
  }

  iii. Escribir studio2.c, el proveedor que sí incluye el contrato.
  #include "studio.h" // Interfaz que exporta
  #include <stdio.h> // Interfaz que importa
  void prontf(const char* s, int i){
  printf("La respuesta es %d\n", i);
  }

  iv. Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor?

  La ventaja que da incluir contratos en el programa es que permite tener el prototipo de la función, detectando errores en el programa durante la compilación, y así evitar un comportamiento indefinido de las funciones.
  Para compilar correctamente este nuevo programa Hello9.c, se debe ejecutar el comando: gcc Hello9.c studio.c -o Hello9.exe. Con este comando, compilamos ambos archivos y el linker vincula la función prontf de la interfaz studio2.c