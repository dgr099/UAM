.PHONY: all clean

###################################################

CFLAGS = -Wall -pedantic -fno-stack-protector -g
CC = g++
C = ./src/
C_elems = ./src/elementos/
C_pruebas = ./src/pruebas/
C_redes = ./src/redes/
C_utils = ./src/utils/
H = ./include/
O = ./obj/
E = ./exe/

O_elems = $(O)RedNeuronal.o $(O)Capa.o $(O)Conexion.o $(O)Neurona.o
O_utils = $(O)utils.o $(O)lecturaPatrones.o

COMPILE_OBJ = $(CC) $(CFLAGS) -c $< -o $@
COMPILE_EX = $(CC) $(CFLAGS) $^ -o $(E)$@

###################################################

all: pruebas mp adaline perceptron #lecturaPatrones

compilar: compila_adaline compila_perceptron

ayuda:
	@echo "\t-m: Modo de lectura de los ficheros [1-3]\n\t-f: Acompañado por un nombre de fichero"
	@echo "\t-p: En modo 1, porcentaje de patrones para entrenamiento [0.0-1.0]\n\t-e: Numero de epocas"
	@echo "\t-t: Tolerancia al cambio de pesos para el entrenamiento (>0.0)"
	@echo "\t-a: Constante de aprendizaje \"alpha\" (>0.0)\n\t-u: Umbral de la funcion de activacion (>0.0)"
	@echo "\t-h: Ayuda"

###################################################	Perceptron

perceptron: compila_perceptron ejecuta_perceptron

ayuda_perceptron:
	@echo "Compilar: make compila_perceptron\nEjecutar version de prueba: make ejecuta_perceptron\n"
	@echo "Sintaxis: $(E)perceptron -[hf:m:p:e:t:]"
	@make ayuda

compila_perceptron: $(C_redes)Perceptron.cpp $(O_elems) $(O_utils)
	@echo "Compiling Perceptron.cpp..."
	@if ! [ -d $(E) ] ; then mkdir $(E) ; fi
	@$(CC) $(CFLAGS) $^ -o $(E)perceptron

ejecuta_perceptron:
	@echo "Executing Perceptron.cpp..."
	@$(E)perceptron -m 1 -f ./data/and.txt -p 0.75 -e 20 -a 0.1 -u 0.5

###################################################	Adaline

adaline: compila_adaline ejecuta_adaline

ayuda_adaline:
	@echo "Compilar: make compila_adaline\nEjecutar version de prueba: make ejecuta_adaline\n"
	@echo "Sintaxis: $(E)adaline -[hf:m:p:e:t:]"
	@make ayuda

compila_adaline: $(C_redes)Adaline.cpp $(O_elems) $(O_utils)
	@echo "Compiling Adaline.cpp..."
	@if ! [ -d $(E) ] ; then mkdir $(E) ; fi
	@$(CC) $(CFLAGS) $^ -o $(E)adaline

ejecuta_adaline:
	@echo "Executing Adaline.cpp..."
	@$(E)adaline -m 1 -f ./data/and.txt -p 0.75 -e 20 -t 0.1 -a 0.1

###################################################	McCulloch-Pitts

mp: compila_mp ejecuta_mp

ayuda_mp:
	@echo "Compilar: make compila_mp\nEjecutar version de prueba: make ejecuta_mp\n"
	@echo "Sintaxis: $(E)mp -[peh]"
	@echo "\t-p: Version de prueba\n\t-e: Version de ejecucion\n\t-h: Ayuda\n"

compila_mp: $(C_redes)McCulloch-Pitts.cpp $(O_elems)
	@echo "Compiling McCulloch-Pitts.cpp..."
	@if ! [ -d $(E) ] ; then mkdir $(E) ; fi
	@$(CC) $(CFLAGS) $^ -o $(E)mp

ejecuta_mp:
	@echo "Executing McCulloch-Pitts.cpp..."
	@$(E)mp -p

###################################################	Pruebas

pruebas: pruebasNeuronaConexion pruebasCapa pruebasRedNeuronal

pruebasNeuronaConexion: $(C_pruebas)pruebasNeuronaConexion.cpp $(O_elems)
	@if ! [ -d $(E) ] ; then mkdir $(E) ; fi
	@$(COMPILE_EX) ; echo ; $(E)$@

pruebasCapa: $(C_pruebas)pruebasCapa.cpp $(O_elems)
	@echo "Compiling and executing pruebasCapa.cpp..."
	@if ! [ -d $(E) ] ; then mkdir $(E) ; fi
	@$(COMPILE_EX) ; echo ; $(E)$@

pruebasRedNeuronal: $(C_pruebas)pruebasRedNeuronal.cpp $(O_elems)
	@echo "Compiling and executing pruebasRedNeuronal.cpp..."
	@if ! [ -d $(E) ] ; then mkdir $(E) ; fi
	@$(COMPILE_EX) ; echo ; $(E)$@

###################################################

$(O)%.o: $(C_elems)%.cpp
	@if ! [ -d $(O) ] ; then mkdir $(O) ; fi
	@$(COMPILE_OBJ)

$(O)%.o: $(C_utils)%.cpp
	@if ! [ -d $(O) ] ; then mkdir $(O) ; fi
	@$(COMPILE_OBJ)
			
clean:
	@echo "Cleaning objects and executables..."
	@rm -rf $(O)*.o $(E)*