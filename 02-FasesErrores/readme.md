En el siguiente trabajo se va a estar probando cada fase de la traducción que realiza un compilador sobre un programa, viendo que problema genera cada etapa.
1. Preprocesador
a. Se escribió el archivo hello2.c, una variante de hello.c, con el siguiente código:

#include <stdio.h>
int/*medio*/main(void){
 int i=42;
 prontf("La respuesta es %d\n");

b.  Preprocesar hello2.c, no compilar, y generar hello2.i. Analizar su contenido. ¿Qué conclusiones saca?

Este programa tiene estos errores: 
- ESTÁ MAL ESCRITO PRINTF
- FALTA LA LLAVE QUE CIERRA EL MAIN
- SE DECLARA LA VARIABLE I PERO NO SE USA
- A PRONTF SE LE ESTÁ INDICANDO QUE LE VA A PASAR UN ENTERO PARA IMPRIMIR, PERO NO SE LE ESTÁ PASANDO LA REFERENCIA

A este programa se le ejecuta el comando: gcc -E Hello2.c -o Hello2.i
Lo que indica este comando es decirle al compilador que solamente preprocese el archivo Hello2.c, sin compilarlo, ensamblarlo ni linkearlo.
Al preprocesar este archivo, lo que hace es interpretar el encabezado, en este caso, el #include, y "copia y pega" el prototipo de cada una de las funciones definidas en la biblioteca stdio.h para que puedan ser utilizadas en el programa que desarrollamos, y tambien cambia todos los comentarios por un espacio. Luego, genera el archivo llamado Hello2.i, que se puede visualizar todo lo generado por el preprocesador.
En líneas generales, la mayoria de las funciones tienen el atributto (__dllimport__) y el atributo (__cdecl__). El primero indica que la función se esta trayendo de la biblioteca stdio.h mientras que el segundo indica la forma en que se pasan los argumentos a la función (en este caso es la convención de C). Estos atributos son agregados por el compilador y no modifican la declaración de la función.

c.  Escribir hello3.c, una nueva variante:

int printf(const char * restrict s, ...);
int main(void){
int i=42;
 prontf("La respuesta es %d\n");

d. Investigar e indicar la semántica de la primera línea.

SEMÁNTICA DE LA PRIMERA LÍNEA (QUÉ SIGNIFICADO TRANSMITE)
QUÉ ESPERA LA FUNCIÓN:
-EL PRIMER ARGUMENTO ES UN PUNTERO A UN CHAR
-EL CONST SIGNIFICA QUE PUEDE APUNTAR A LA VARIABLE S, PERO 
QUE NO LA VA A MODIFICAR. ES DECIR, S ES UN PUNTERO DE SOLO LECTURA
-S ES EL NOMBRE DE LA VARIABLE
-S PUEDE CAMBIAR DE AL OBJETO AL CUAL APUNTA, PERO COMO ES UN CONST,
NO PUEDE MODIFICAR LO QUE HAY DENTRO.
-RESTRICT INDICA QUE S ESTA APUNTANDO A UN OBJETO y que es al unico,
que apunta, LO QUE PERMITE QUE EL COMPILADOR SE PUEDA OPTIMIZAR


LAS DIFERENCIAS CONTRA EL HELLO2.C ES QUE NO TRAJO 
TODAS LAS LIBRERIAS DEL INCLUDE, DECLARA PRINTF Y 
ELIMINÓ EL COMENTARIO QUE ESTABA EN LA FUNCIÓN MAIN

e. Preprocesar hello3.c, no compilar, y generar hello3.i. Buscar
diferencias entre hello3.c y hello3.i.

Para generar Hello3.i, vuelvo a ejecutar el comando gcc -E Hello3.c -o Hello3.i. Las diferencias entre son que añade un encabezado con #.
Si se ejecuta el comando gcc -E Hello3.c -o Hello3.i -P, el agregado hace que los # desaparezcan, dejando el programa exactamente igual al que escribimos.

2. Compilación.

a. Compilar el resultado y generar hello3.s, no ensamblar.

Para poder compilar el programa sin ensamblar, se debe usar el comando: gcc -S Hello3.i -o Hello3.s. Al ejecutar el comando, en la terminal aparecen 2 mensajes, una advertencia y un error:
ello3.i: In function 'main':
Hello3.i:4:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    4 |  prontf("La respuesta es %d\n");
      |  ^~~~~~
      |  printf
Hello3.i:4:2: error: expected declaration or statement at end of input

El primer error, la advertencia, indica una declaración implicita de la funcion "prontf", y pregunta si se quiere referir a la función "printf". El segundo error indica que esta faltando la llave de cierre del programa.

b. Corregir solo los errores, no los warnings, en el nuevo archivo hello4.c y empezar de nuevo, generar hello4.s, no ensamblar.

Se corrige el error de la llave de main y se compila el programa Hello4.c con el comando: gcc -S Hello4.c -o Hello4.s. El comando se ejecuta y se genera el archivo, por lo que se puede decir que el programa se compiló, por más de que exista un warning y no este declarada la función prontf. 

c. Leer hello4.s, investigar sobre lenguaje ensamblador, e indicar de formar sintética cual es el objetivo de ese código.

En el archivo Hello4.s, las primeras 4 lineas hacen referencia a definiciones, no es codigo ejecutable. LC0 es una constante de metacomandos que facilita la codificacion.
En la linea 10 arranca la funcion main en la que le asigna una etiqueta en la linea 11. En la linea 13 (pushl %ebp) esta empujando a la pila el registro que esta en el base point. a cada funcion que invoquemos se le va a sumar a la pila. En la linea 16 (movl %esp, ebp) indica que la cima de la pila es la nueva base. En la linea 18 y 19 está generando espacio para la declaracion de la variable i. En las lineas 21 y 22 vuelve a hacer movimientos para poder llamar a la funcion prontf, que se encuentra en la linea 23. Luego, en la linea 24, el comando que se ejecuta (movl $0 %eax) indica que se esta devolviendo un 0, que es lo que retorna la funcion main por convencion. El signo $0 indica que es un literal, es decir, que es un valor definido, no una direccion de memoria, mientras que el % indica que es un registro. Sin embargo, el programa nunca se terminaria de ejecutar ya que no esta definida la función prontf, aunque eso no impida que el programa se compile.

d. Ensamblar hello4.s en hello4.o, no vincular.

Para poder ensamblar se ejecuta el comando: gcc -c Hello4.s -o Hello4.o. Se logra generar el archivo Hello.o sin inconvenientes, y para poder visualizarlo se uso una extension de visual studio que permite editar archivos hexadecimales. dentro de este archivo .o, se encuentra todo el codigo assembler pero pasado en bytes.

3. Vinculación

a. Vincular hello4.o con la biblioteca estándar y generar el ejecutable.

Para vincular el archivo Hello4.o, se ejecuta el comando: gcc Hello4.o -o Hello4.exe. En este caso no se especifica el paso de la vinculación, como si pasaba en otras fases, ya que al entregar un archivo .o, no queda otra fase mas que la vinculación para generar el ejecutable. Al ejecutar el comando, en la terminal aparece el error:
e:/sintaxis/bin/../lib/gcc/mingw32/9.2.0/../../../../mingw32/bin/ld.exe: Hello4.o:Hello4.c:(.text+0x1e): undefined reference to `prontf'
collect2.exe: error: ld returned 1 exit status
Este error hace referencia a que no se encuentra definida la función prontf, lo que impide que se obtenga el ejecutable del programa. También, se interpreta que el programa que "expresa" el error es el ld.exe, que no es mas que el propio vinculador del compilador mingw.

b. Corregir en hello5.c y generar el ejecutable. Solo corregir lo necesario para que vincule.

Como el error en la vinculacion en el archivo Hello4.c era que no encontraba la funcion prontf (ya que estaba mal escrita), se cambio a printf para que el programa pueda vincular correctamente. Para ello, se ejecuta el comand: gcc Hello5.c -o Hello5.exe. En este caso, se saltea toda la fase de los archivos .i, .s y .o, y directamente se compila y entrega el ejecutable.

c. Ejecutar y analizar el resultado.

Para ejecutar el archivo Hello5.exe, unicamente se escribe el nombre del archivo en la consola y automaticamente lo ejecuta. la salida del programa es "La respuesta es 4200880". La parte del string "La respuesta es" proviene de la cadena de caracteres que le pasamos a la funcion printf, y el numero 4200880 proviene de la referencia que le pasamos a la funcion printf. Al no aclarar el numero referenciado, toma cualquier locacion de memoria, y el hecho de que los primeros 2 numeros coincidan con la variable i es pura coincidencia.

4. Corrección de Bug

a. Corregir en hello6.c y empezar de nuevo; verificar que funciona como se espera.

El unico bug para corregir es el mencionado anteriormente, que es la salida del numero que no es referenciado en la funcion printf. para ello, a la funcion le agregamos la variable i. Nuevamente compilamos el programa totalmente para obtener el ejecutable con el comando: gcc Hello6.c -o Hello6.exe. Ahora, la salida del programa es "La respuesta es 42" 

5. Remoción de prototipo

a. Escribir hello7.c, una nueva variante:
int main(void){
 int i=42;
 printf("La respuesta es %d\n", i);
}

b. Explicar porqué funciona.

Cuando se compila y se genera el ejecutable con el comando: gcc Hello7.c -o Hello7.exe, en la terminal aparece una advertencia:
Hello7.c: In function 'main':
Hello7.c:3:2: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    3 |  printf("La respuesta es %d\n", i);
      |  ^~~~~~
Hello7.c:3:2: warning: incompatible implicit declaration of built-in function 'printf'
Hello7.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
  +++ |+#include <stdio.h>
    1 | int main(void){

Esta advertencia de aca está indicando que se esta declarando, de forma implicita, la funcion printf. Sin embargo, el ejecutable se genera ya que una característica del lenguaje C es que se desclara, como dice el error, de forma implicita, la funcion printf, lo que evita que en el linker se produzca un error y encuentre la funcion en la biblioteca standar.
Tambien, advierte sobre que la declaracion de printf es incompatible con la "built-in". Esta declaracion built-in es una declaracion propia del preprocesador sobre la funcion printf, ya que es tan comun que tambien esta definida dentro del compilador.
Ademas, la advertencia tambien incluye una nota, recomendando incluir la biblioteca <stdio.h>, que ya contiene definida la funcion printf

