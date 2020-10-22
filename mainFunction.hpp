/** @file */
#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>

unsigned int ** returnTabVal(const unsigned int _w,const unsigned int _h);
unsigned char * readBmp(const char * filname, unsigned int & _w,unsigned int &  _h);
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h);
char returnChar (const unsigned int _v);
void test();


#endif