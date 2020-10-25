/** @file */
#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>
/**przchowuje którą bibliotekę ma używać program */
 enum class libMode {libC,libAsm};

 void helpParams();
/**zwraca nazwę biblioteki asm lub C 
 * @param _argc  
 * @param _argv
 * @param _inFileName
 * @param	_outFileName
 * @param _lM
 * @param _scale
 * @return true jeśli wszystkie parametry są poprawne 
 * @return false jeśli parametry są nie poprawne   
 */
bool readParams(const int _argc, char ** _argv,std::string &  _inFileName,std::string &_outFileName,libMode & _lM,int &_scale );
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
unsigned char * readBmp(const char * filename, unsigned int & _w,unsigned int &  _h);
/** zapisuje skonwertowany obraz w txt
 * @param [in,out] _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param [in,out] _h wysokośc bitmapy 
 * @return Nic. 
 */
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h,const char * _filename);
/** zwraca znak, któremu jest przypisana wartość liczbowa  
 * @param  _v Wartość, która decyduje jaki znak zostanie zwrócony 
 * @return Znak, który symbolizuje obszar pikseli (obszar może się składać z jednego piksela)
 */
char returnChar (const unsigned int _v);



#endif