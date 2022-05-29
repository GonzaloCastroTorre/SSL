# Hello.c
# Comentario

#all: Hello.exe

#run: Hello.exe
#	./Hello.exe

#Hello.exe: Hello.o
#	gcc Hello.o -o Hello.exe

#Hello.o: Hello.c
#	gcc -c Hello.c -std=c18 -o Hello.o

#clean:
#	del Hello.o
#	del Hello.exe

run: TablasDeConversion.exe
	./TablasDeConversion.exe

TablasDeConversion.exe: TablasDeConversion.o Conversion.o
	gcc TablasDeConversion.o Conversion.o -o TablasDeConversion.exe

TablasDeConversion.o: TablasDeConversion.c
	gcc -c TablasDeConversion.c -std=c18 -o TablasDeConversion.o

Conversion.o: Conversion.c
	gcc -c Conversion.c -std=c18 -o Conversion.o

borrar: 
	del TablasDeConversion.o
	del Conversion.o
	del TablasDeConversion.exe
	
run2: ConversionTest.exe
	./ConversionTest.exe

ConversionTest.exe: ConversionTest.o
	gcc ConversionTest.o -o ConversionTest.exe

ConversionTest.o: ConversionTest.c
	gcc -c ConversionTest.c -std=c18 -o ConversionTest.o

borrar2:
	del ConversionTest.o
	del ConversionTest.exe