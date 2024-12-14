# kompilator c
CCOMP = gcc 

# konsolidator
LOADER = gcc 

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3 -fopenmp -p
OPT = -O3  -fopenmp -march=core-avx2
#OPT = -g  -fopenmp 
#OPT = -O2 -parallel -opt-mem-bandwidth1

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
#LIB = -L/opt/intel//mkl/8.1/lib/em64t -lmkl_em64t
#LIB = -L/opt/intel//mkl/8.1/lib/32 -lmkl_ia32
#LIB = -L/opt/intel/mkl/10.1.0.015/lib/em64t/ -lmkl -lguide -lpthread
LIB = -lm

# zaleznosci i komendy
moj_program: moj_program.o mat_vec.o mat_vec_crs.o mat_vec_csc.o mat_vec_sell.o mat_vec_vector.o pomiar_czasu.o csrToSell.o cooToCsr.o readFile.o cooToCsc.o
	$(LOADER) $(OPT) moj_program.o mat_vec.o mat_vec_crs.o mat_vec_csc.o mat_vec_sell.o mat_vec_vector.o pomiar_czasu.o cooToCsr.o csrToSell.o readFile.o cooToCsc.o -o moj_program $(LIB)

moj_program.o: moj_program.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) moj_program.c $(INC)

mat_vec.o: mat_vec.c
	$(CCOMP) -c $(OPT) mat_vec.c

readFile.o: readFile.c
	$(CCOMP) -c $(OPT) readFile.c

csrToSell.o: csrToSell.c
	$(CCOMP) -c $(OPT) csrToSell.c

cooToCsr.o: cooToCsr.c
	$(CCOMP) -c $(OPT) cooToCsr.c

cooToCsc.o: cooToCsc.c
	$(CCOMP) -c $(OPT) cooToCsc.c

mat_vec_crs.o: mat_vec_crs.c
	$(CCOMP) -c $(OPT) mat_vec_crs.c

mat_vec_csc.o: mat_vec_csc.c
	$(CCOMP) -c $(OPT) mat_vec_csc.c

mat_vec_sell.o: mat_vec_sell.c
	$(CCOMP) -c $(OPT) mat_vec_sell.c

mat_vec_vector.o: mat_vec_vector.c
	$(CCOMP) -c $(OPT) mat_vec_vector.c

pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

clean:
	rm -f *.o
