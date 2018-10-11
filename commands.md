<span style="display:block;text-align:center">![Logo](./doc/l3ing-project-huffman-coding.png)
# L3 ING Project - Huffman coding

## Make commands

### Make

	make

Compiles the **src/** files and generates the executable huffman_exec in **bin/**

### Make bin

	make bin

Same as **make**, compiles the executable in **bin/**

### Make lib

	make lib

Generates two versions of the library in **lib/**, a dynamic one _".so"_ and a static one ".a"

### Make clean

	make clean

Deletes the executable in **bin/**

### Make cleanO

	make cleanO

Deletes the files _".o"_ in **obj/**

### Make clean+

	make clean+

Executes **make clean** and **make cleanO**

### Make cleandir

	make cleandir

Deletes the folders **bin/**, **obj/** and **lib/**

### Make run

	make run

Updates the executable if needed, and after that executes **bin/huffman_exec** with no arguments

### Make run_interface

	make run_interface

Updates the executable if needed, and after that executes **bin/huffman_exec** with the argument "interface" to run the program with a console interface made for the tests

### Make memory_run

	make memory_run

Same as **make run**, but uses valgrind in addition

### Make memory\_run\_interface

	make memory_run_interface

Same as **make run_interface**, but uses valgrind in addition

### Make archive

	make archive

Puts the content of the directory in a compressed folder **.tar.bz2**. The folders **bin/**, **obj/** and **lib/** aren't put in it

## NOTE

You can use the _-j{x}_ option with the previous commands; You have to replace the _{x}_ by the number of threads your computer can handle as said in **README.md**