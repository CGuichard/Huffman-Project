#====================== PARAMETRES ======================#

# Nom du fichier principal (sans le .c)
MAIN=huffman

#====================== NE PAS TOUCHER ======================#

# Compilateur
CC=gcc

# FLAGS : paramètres de compilation
CFLAGS=-I include -O3 -march=native -Wall -Wextra -pedantic -ggdb

# FLAGS : Librairies + Version utilisée
LIBS=-std=c99 -lm

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)

bin/$(MAIN): $(OBJS)
	@mkdir -p bin
	$(CC) -o $@ $^ $(LIBS)

obj/$(MAIN).o: src/$(MAIN).c
	@mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj/%.o: src/%.c include/%.h
	@mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean cleanO clean+ cleandir run memory_run archive sort init

clean:
ifneq ("$(wildcard bin/$(MAIN))","")
	@rm bin/$(MAIN)
	@echo "Exécutable supprimé"
else
	@echo "Exécutable déjà supprimé"
endif

cleanO:
ifneq ("$(wildcard obj/*.o)","")
	@rm $(wildcard obj/*.o)
	@echo "Fichiers .o supprimés"
else
	@echo "Aucun fichier .o à supprimer"
endif

clean+: clean cleanO

cleandir:
	@rm -rf bin obj
	@echo "Dossiers bin/ et obj/ supprimés"

run: bin/$(MAIN)
	@./bin/$(MAIN)

memory_run: bin/$(MAIN)
	@valgrind ./bin/$(MAIN)

archive: $(wildcard src/*) $(wildcard include/*) $(wildcard doc/*) Makefile
	@tar jcvf $@-$(MAIN).tar.bz2 $^ > /dev/null
ifneq ("$@-$(MAIN).tar.bz2","")
	@echo "Une archive \"$@-$(MAIN).tar.bz2\" a était généré"
else
	@echo "L'archive n'a pas pu être généré"
endif

sort:
	@mkdir -p src include doc
ifneq ("$(wildcard *.c)","")
	@mv $(wildcard *.c) src/
endif
ifneq ("$(wildcard *.h)","")
	@mv $(wildcard *.h) include/
endif
ifneq ("$(wildcard *.pdf)","")
	@mv $(wildcard *.pdf) doc/
endif
ifneq ("$(wildcard *.o)","")
	@rm $(wildcard *.o)
endif
ifneq ("$(wildcard $(MAIN))","")
	@rm $(MAIN)
endif
	@echo "Répartition faite"

init:
	@mkdir -p src include doc
ifneq ("$(wildcard include/$(MAIN).h)","")
	@echo "Attention! Le fichier include/$(MAIN).h est déjà présent"
else
	@echo "#ifndef $$( echo $(MAIN) | tr [a-z] [A-Z] )_H\n#define $$( echo $(MAIN) | tr [a-z] [A-Z] )_H\n\n  #ifndef STD_LIBS_H\n  #define STD_LIBS_H\n\n  #include <stdlib.h>\n  #include <stdio.h>\n\n  #endif\n\n// Prototypes ici\n\n#endif\n" > include/$(MAIN).h;
endif
ifneq ("$(wildcard src/$(MAIN).c)","")
	@echo "Attention! Le fichier src/$(MAIN).c est déjà présent"
else
	@echo "#include \"$(MAIN).h\"\n\nint main(int argc, char *argv[]){\n\n  // A modifier\n  puts(\"Hello World!\");\n\n  return EXIT_SUCCESS;\n}\n" > src/$(MAIN).c;
endif
	@echo "Répertoire initialisé";

#====================== FIN NE PAS TOUCHER ======================#
