#all: pract3b.exe
pract3b.exe: pract3b.obj pract3bs.obj
	tcc -v -ml -Lc:\compila\tc\lib pract3b.obj pract3bs.obj

pract3b.obj: pract3b.c
	tcc -c -v -ml -Ic:\compila\tc\include pract3b.c

pract3bs.obj: pract3bs.asm
	tasm /zi /ml pract3bs,,pract3bs