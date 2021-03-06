#====================== PARAMETRES ======================#

# Nom du fichier principal (sans le .c)
MAIN=huffman_exec
LIB=libhuffman

#====================== NE PAS TOUCHER ======================#

# Compilateur
CC=gcc

# FLAGS : paramètres de compilation
CFLAGS=-I include -O2 -march=native -Wall -Wextra -pedantic -ggdb

# FLAGS : Librairies + Version utilisée
LIBS=-std=c99 -lm

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)
OBJSPIC=$(SRCS:src/%.c=obj/%.pic.o)

# bin/$(MAIN)

bin/$(MAIN): $(OBJS)
	@mkdir -p bin
	$(CC) -o $@ $^ $(LIBS)
	@cp bin/$(MAIN) app/.resources/huffman_exec
	@chmod +x app/.resources/huffman_exec

obj/$(MAIN).o: src/$(MAIN).c
	@mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj/%.o: src/%.c include/%.h
	@mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

#lib/$(LIB).a

lib/$(LIB).a: $(OBJS)
	@mkdir -p lib
	@rm -f obj/$(MAIN).o obj/*.pic.o
	$(AR) -cr $@ obj/*.o

#lib/$(LIB).so

lib/$(LIB).so: $(OBJSPIC)
	@mkdir -p lib
	@rm -f obj/$(MAIN).pic.o
	$(CC) --shared -o $@ obj/*.pic.o

obj/$(MAIN).pic.o: src/$(MAIN).c
	$(CC) -fPIC -c -o $@ $< -I include

obj/%.pic.o: src/%.c include/%.h
	$(CC) -fPIC -c -o $@ $< -I include

.PHONY: bin lib clean cleanO cleantests clean+ cleandir run memory_run run_interface memory_run_interface archive

bin: bin/$(MAIN)

lib: lib/$(LIB).a lib/$(LIB).so

clean:
ifneq ("$(wildcard bin/$(MAIN))","")
	@rm bin/$(MAIN)
	@echo "Executable removed"
else
	@echo "Executable already removed"
endif

cleanO:
ifneq ("$(wildcard obj/*.o)","")
	@rm $(wildcard obj/*.o)
	@echo "Files .o deleted"
else
	@echo "No file .o to delete"
endif

cleantests:
ifneq ("$(wildcard tests/*.hfm)","")
	@rm $(wildcard tests/*.hfm)
endif
ifneq ("$(wildcard tests/*.hfm.key)","")
	@rm $(wildcard tests/*.hfm.key)
endif
ifneq ("$(wildcard tests/*.hfm.txt)","")
	@rm $(wildcard tests/*.hfm.txt)
endif
	@echo "Tests repository cleaned"

clean+: clean cleanO cleantests

cleandir: cleantests
	@rm -rf bin obj lib
	@echo "'bin/', 'obj/' and 'lib/' folders have been deleted"

run: bin/$(MAIN)
	@./bin/$(MAIN)

memory_run: bin/$(MAIN)
	@valgrind ./bin/$(MAIN)

run_interface: bin/$(MAIN)
	@./bin/$(MAIN) interface

memory_run_interface: bin/$(MAIN)
	@valgrind ./bin/$(MAIN) interface

archive: $(wildcard src/*) $(wildcard include/*) $(wildcard doc/*) $(wildcard app/.resources/*) app/HuffmanCoding.jar $(wildcard tests/*) Makefile README.html commands.html
	@tar jcvf $@-$(MAIN).tar.bz2 $^ > /dev/null
ifneq ("$@-$(MAIN).tar.bz2","")
	@echo "The archive \"$@-$(MAIN).tar.bz2\" was successfully generated"
else
	@echo "The archive could not be generated"
endif

#====================== FIN NE PAS TOUCHER ======================#
