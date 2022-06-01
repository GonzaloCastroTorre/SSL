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
	
runTest: ConversionTest.exe
	./ConversionTest.exe

ConversionTest.exe: ConversionTest.o Conversion.o
	gcc ConversionTest.o Conversion.o -o ConversionTest.exe

ConversionTest.o: ConversionTest.c
	gcc -c ConversionTest.c -std=c18 -o ConversionTest.o

borrarTest:
	del ConversionTest.o
	del ConversionTest.exe
	del Conversion.o