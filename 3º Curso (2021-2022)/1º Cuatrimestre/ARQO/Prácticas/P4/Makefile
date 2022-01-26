CC = gcc
LIBS = -lgomp -lm
LIB_DIR = 
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp -std=c99
C = ./src/
H = ./include/
O = ./obj/
E = ./exe/
.PHONY: clean all

all: omp1 omp2 pescalar_serie pescalar_par1 pi_serie pi_par1 pi_par2 pi_par3 pi_par4 pi_par5 pi_par6 pi_par7 edgeDetector $(H)stb_image.h $(H)stb_image_write.h fast slow multi_matrices multi_matrices_transpuesta serie par_b1 par_b2 par_b3 edgeDetector_omp edgeDetector-O3 edgeDetector_omp-O3 Thresholds Thresholds_G

omp1: $(C)omp1.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

omp2: $(C)omp2.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pescalar_serie: $(C)pescalar_serie.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pescalar_par1: $(C)pescalar_par1.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

Thresholds: $(C)calculate_Threshols.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

Thresholds_G: $(C)calculate_Threshols_graphic.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pi_serie: $(C)pi_serie.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pi_par1: $(C)pi_par1.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pi_par2: $(C)pi_par2.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)
	
pi_par3: $(C)pi_par3.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)
	
pi_par4: $(C)pi_par4.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pi_par5: $(C)pi_par5.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pi_par6: $(C)pi_par6.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

pi_par7: $(C)pi_par7.c $(C)arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

edgeDetector: $(C)edgeDetector.c $(H)stb_image_write.h $(H)stb_image.h
	gcc $(FLAGS) -std=gnu99 $(LIB_DIR) -o $(E)$@ $(C)edgeDetector.c $(LIBS)

edgeDetector_omp: $(C)edgeDetector_omp.c $(H)stb_image_write.h $(H)stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $(E)$@ $(C)edgeDetector_omp.c $(LIBS)


edgeDetector-O3: $(C)edgeDetector.c $(H)stb_image_write.h $(H)stb_image.h
	gcc $(FLAGS) -std=gnu99 $(LIB_DIR) -O3 -o $(E)$@ $(C)edgeDetector.c $(LIBS)

edgeDetector_omp-O3: $(C)edgeDetector_omp.c $(H)stb_image_write.h $(H)stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -O3 -o $(E)$@ $(C)edgeDetector_omp.c $(LIBS)


$(H)stb_image.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
	mv stb_image.h ./include/

$(H)stb_image_write.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
	mv stb_image_write.h ./include/
fast:	$(C)fast.c	$(C)arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

slow:	$(C)slow.c	$(C)arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

multi_matrices:	$(C)multi_matrices.c	$(C)arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

multi_matrices_transpuesta:	$(C)multi_matrices_transpuesta.c	$(C)arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $(E)$@ $^ $(LIBS)

serie: $(C)mult_matrix_serie.c $(C)arqo3.c
	gcc $(FLAGS) -o $(E)$@ $^

par_b1: $(C)mult_matrix_par_b1.c $(C)arqo3.c
	gcc $(FLAGS) -o $(E)$@ $^

par_b2: $(C)mult_matrix_par_b2.c $(C)arqo3.c
	gcc $(FLAGS) -o $(E)$@ $^

par_b3: $(C)mult_matrix_par_b3.c $(C)arqo3.c
	gcc $(FLAGS) -o $(E)$@ $^

clean:
	rm -f *.o *~ $(E)omp1 $(E)omp2 $(E)pescalar_serie $(E)pescalar_par1 $(E)pi_serie $(E)pi_par1 $(E)pi_par2 $(E)pi_par3 $(E)pi_par4 $(E)pi_par5 $(E)pi_par6 $(E)pi_par7 $(E)edgeDetector $(E)fast $(E)slow $(E)multi_matrices $(E)multi_matrices_transpuesta $(E)serie $(E)edgeDetector_omp $(H)stb_image.h $(H)stb_image_write.h $(E)edgeDetector-O3 $(E)edgeDetector_omp-O3 $(E)Thresholds $(E)Thresholds_G
clear:
	rm -f *.o *~
