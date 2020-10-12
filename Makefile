
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
	./main


main : main.o submain.o subasmmain.o
	$(kompilatorCPP)  $(nopie)  $(standard) $(debug) $(optymalizacja) $(errors)  -o $@ $^   $(grafika)

main.o : main.cpp
	$(kompilatorCPP)   $(standard) $(debug) $(optymalizacja) $(errors)  -c -o $@ $^

submain.o : submain.c
	$(kompilatorC)   $(debug) $(optymalizacja) $(errors)  -c -o $@ $^

subasmmain.o : subasmmain.asm
	$(kompilatorAsm) -f elf64 $(optymalizacja) -o $@ $^



clean :
	for f in `ls *.o` ; do  if [ -f $$f ] ; then rm $$f  ; fi;   done;
	if [ -f main ] ; then rm main ; fi ;
	if [ -d html ] ; then rm -r html; fi ;
	



