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
/**
 * @todo todo 
 */

 void helpParams();

/**czyta parametry
 * @param _argc  
 * @param _argv
 * @param [in,out] _inFileName
 * @param	[in,out] _outFileName
 * @param [in,out] _lM informuje, którą bibliotekę wykorzystuje program  
 * @param [in,out] _scale
 * @todo zrobić znacznik do watków 
 * @return true jeśli wszystkie parametry są poprawne 
 * @return false jeśli parametry są nie poprawne   
 */
bool readParams(const int _argc, char ** _argv,std::string &  _inFileName,std::string &_outFileName,libMode & _lM,int &_scale,int & threadNumber);

/** Tworzy tablice 2D  
 * @param _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param _h wysokośc bitmapy 
 * @return zaalokowana tablica 2D i wyzerowana 
 */
unsigned int ** returnTabVal(const unsigned int _w,const unsigned int _h,const int & _scale);

/** zwraca wsk tablice 1D BGR 
 * @param [in,out] _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param [in,out] _h wysokośc bitmapy 
 * @param [in,out] _bW szerokośc bitmapy w bajtach 
 * @return wskaźnik na zaalokowaną tablicę 1D BGR... 
 */
unsigned char * readBmp(const char * filename, unsigned int & _w,unsigned int &  _h,unsigned int &  _bW);

/** zapisuje skonwertowany obraz w txt
 * @param [in,out] _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param [in,out] _h wysokośc bitmapy 
 * @return Nic. 
 */
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h,const char * _filename,const int & _scale);

/** zwraca znak, której jest przypisany zakres wartosci   
 * @param  _v Wartość (musi być z zakresu [0,255]), która decyduje jaki znak zostanie zwrócony  
 * @return Znak, który symbolizuje obszar pikseli (obszar może się składać z jednego piksela)
 */
char returnChar (const unsigned int _v);



#endif