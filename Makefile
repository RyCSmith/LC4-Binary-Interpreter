# Ryan Smith
# Makefile for CIT 593 LC4 project
#

# this rule invokes the lc4: rule below
#
all: lc4

# this rule partially compiles lc4_memory.c, to the target: lc4_memory.o
#

#make object file for memory (no main)
lc4_memory.o: lc4_memory.c lc4_memory.h
	clang -g -c lc4_memory.c

#make object file for loader (no main)
lc4_loader.o: lc4_loader.c lc4_loader.h
	clang -g -c lc4_loader.c

lc4_disassembler.o: lc4_disassembler.c lc4_disassembler.h
	clang -c lc4_disassembler.c

#this takes the 2 object files generated above and puts them in the file with main, give title lc4
lc4: lc4.c lc4_memory.o lc4_loader.o lc4_disassembler.o
	clang -g lc4.c lc4_memory.o lc4_loader.o lc4_disassembler.o -o lc4


clean:
	rm -rf *.o

clobber: clean
	rm -rf lc4
	
