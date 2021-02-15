
kompilatorCPP=g++
kompilatorC=gcc
kompilatorAsm=nasm 
nopie=-no-pie
standard=-std=c++14
optymalizacja=-O3
errors=-pedantic-errors -Wall
debug=-g
.PHONY: clean

all : convert2txt
	export LD_LIBRARY_PATH=$LC_LIBRARY_PATH:./
	./convert2txt

v : all  #leak test 
	valgrind ./convert2txt

convert2txt :   libasm.so libC.so mainFunction.o main.o 
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja)   $(errors) -pthread -m64  -L. -l:libasm.so -l:libC.so -I. -o $@ mainFunction.o  main.o -ldl #<- musi być na końcu tak jak SFML   
main.o : main.cpp
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja) $(errors) -pthread  -c -o $@ $^ 
mainFunction.o : mainFunction.cpp
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja) $(errors)  -c -o $@ $^

libC.so : submain.o
	$(kompilatorC) $(debug) $(optymalizacja) $(errors) -m64 -shared -fPIC -o $@ $^

submain.o : submain.c
	$(kompilatorC) $(debug) $(optymalizacja) $(errors)  -c -o $@ $^

libasm.so : subasmmain.o
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja) $(errors) -fPIC -m64 -shared  -o $@ $^

subasmmain.o : subasmmain.asm
	$(kompilatorAsm) -f elf64 $(optymalizacja) $(debug) -o $@ $^



clean :
	for f in `ls *.o` `ls *.so`; do  if [ -f $$f ] ; then rm $$f  ; fi;   done;
	if [ -f main ] ; then rm main ; fi ;
	if [ -d documentation ] ; then rm -r documentation; fi ; 
	rm convert2txt
d : doxy
	firefox documentation/html/index.html

doxy :
	doxygen Doxyfile




