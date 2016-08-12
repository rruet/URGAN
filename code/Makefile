export CC = gcc
export LD = gcc
export CLIB = -lm
export CFLAG = -Wall

#
# Cible pour l'algo de test
#

test: main_svg_test.c urgan.c
	$(CC) $(CFLAG) main_svg_test.c urgan.c -o urgan_test $(CLIB) 

#
# Cible pour l'algo avec moyennage des coordonnées
#

coor: main_avg_coor.c urgan.c
	$(CC) $(CFLAG) main_avg_coor.c urgan.c -o urgan_coor $(CLIB)


#
# Cible pour l'algo avec moyennage des distances
#

dist: main_avg_dist.c urgan.c
	$(CC) $(CFLAG) main_avg_dist.c urgan.c -o urgan_dist $(CLIB)


#
# Nettoyage global
#

clean:
	rm -f urgan_test urgan_dist urgan_coor


