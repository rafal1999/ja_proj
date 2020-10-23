/** @file */
#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>
/** Tworzy tablice 2D  
 * @param _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param _h wysokośc bitmapy 
 * @return zaalokowana tablica 2D i wyzerowana 
 */
unsigned int ** returnTabVal(const unsigned int _w,const unsigned int _h);
/** zwraca wsk tablice 1D BGR 
 * @param [in,out] _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param [in,out] _h wysokośc bitmapy 
 * @return wskaźnik na zaalokowaną tablicę 1D BGR... 
 */
unsigned char * readBmp(const char * filname, unsigned int & _w,unsigned int &  _h);
/** zapisuje skonwertowany obraz w txt
 * @param [in,out] _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param [in,out] _h wysokośc bitmapy 
 * @todo zrobic zapisa do pliku a nie na terminal
 * @return Nic. 
 */
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h);
/** zwraca znak, któremu jest przypisana wartość liczbowa  
 * @param  _v Wartość, która decyduje jaki znak zostanie zwrócony 
 * @return Znak, który symbolizuje obszar pikseli (obszar może się składać z jednego piksela)
 */
char returnChar (const unsigned int _v);



#endif