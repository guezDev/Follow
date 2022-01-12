CC=gcc
EXEC=prog
CFLAGS=-Wall -Wextra -Werror
LDLIBS=-lm
DEPS=list.o hachage.o testListHelpers.o charge_analyse.o alignement.o

$(EXEC): $(DEPS) main.o
	$(CC) $(CFLAGS) $^ `pkg-config --cflags --libs gtk+-3.0` -o $@ $(LDLIBS)

list.o: liste_chainee/list.c liste_chainee/list.h
	$(CC) -c $^

hachage.o: table_de_hachage/hachage.c table_de_hachage/hachage.h
	$(CC) -c $^

charge_analyse.o: chargement_et_analyse_des_textes/charge_analyse.c chargement_et_analyse_des_textes/charge_analyse.h
	$(CC) -c $^

alignement.o: alignement_des_textes/alignement.c alignement_des_textes/alignement.h
	$(CC) -c $^

testListHelpers.o: test/testListHelpers.c test/testListHelpers.h
	$(CC) -c $^

main.o: main.c $(DEPS)
	$(CC) -c main.c `pkg-config --cflags --libs gtk+-3.0` 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

