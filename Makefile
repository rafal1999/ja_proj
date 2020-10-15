
kompilatorCPP=g++
kompilatorC=gcc
kompilatorAsm=nasm 
nopie=-no-pie
standard=-std=c++14
optymalizacja=-O0
errors=-pedantic-errors -Wall
debug=#-g
.PHONY: clean

all : main
	export LD_LIBRARY_PATH=$LC_LIBRARY_PATH:./
	./main


main :   libasm.so libC.so main.o 
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja) $(errors) -m64  -L. -l:libasm.so -l:libC.so -I. -o main  main.o -ldl #<- musi być na końcu tak jak SFML   
main.o : main.cpp
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja) $(errors)  -c -o $@ $^ 

libC.so : submain.o
	$(kompilatorC) $(debug) $(optymalizacja) $(errors) -m64 -shared -fPIC -o $@ $^

submain.o : submain.c
	$(kompilatorC) $(debug) $(optymalizacja) $(errors)  -c -o $@ $^

libasm.so : subasmmain.o
	$(kompilatorCPP) $(standard) $(debug) $(optymalizacja) $(errors) -fPIC -m64 -shared  -o $@ $^

subasmmain.o : subasmmain.asm
	$(kompilatorAsm) -f elf64 $(optymalizacja) -o $@ $^



clean :
	for f in `ls *.o` `ls *.so`; do  if [ -f $$f ] ; then rm $$f  ; fi;   done;
	if [ -f main ] ; then rm main ; fi ;
	if [ -d html ] ; then rm -r html; fi ;
	



