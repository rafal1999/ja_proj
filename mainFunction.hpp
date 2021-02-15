/** @file 
 * Funkcje używane w częsci głównej programu napisane w języku C++
*/
#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>
/** przchowuje którą bibliotekę ma używać program */
 enum class libMode {
  libC,           ///<biblioteka C
  libAsm          ///<biblioteka Asm
   };
 
/** Funkcja jest wywoływana w przypadku podania  błednych parametrów 
 * i wyświetla opis wszystkich przełączników
 * @return Nic.
 */

 void helpParams();

/** Funkcja czyta parametry podane z wiersza lini poleceń 
 * @param _argc  liczba parametrów 
 * @param _argv  paramet podane przez użytkownika 
 * @param [in,out] _inFileName nawa pliku wejściowego 
 * @param	[in,out] _outFileName nazwa pliku wyjścowege 
 * @param [in,out] _lM  informuje, którą bibliotekę wykorzystuje program  
 * @param [in,out] _scale skala z jaką ma być przetworzony wynikowy plik
 * @param [in,out] _threadNumber liczba wątków 
 * @return true jeśli wszystkie parametry są poprawne 
 * @return false jeśli parametry są niepoprawne   
 */
bool readParams(const int _argc, char ** _argv,std::string &  _inFileName,std::string &_outFileName,libMode & _lM,int &_scale,int & _threadNumber);

/** Funkcja dynamiczie alkouje tablice 2D  (wsk na wsk)
 * @param _w szerokość bitmapy w bajtach (wyrównanej)
 * @param _h wysokośc bitmapy 
 * @param _scale skala z jaką będze przetwarzany obraz 
 * @return Zaalokowana tablica 2D i wyzerowana 
 */
unsigned int ** returnTabVal(const unsigned int _w,const unsigned int _h,const int & _scale);

/** Funkcja czyta bitmape i zwraca wskaźnik na tablice (1D)  BGRBGR...  
 * @param filename nazwa pliku wejściowego 
 * @param [in,out] _w szerokość bitmapy (w bajtach) (już wyrównanej)
 * @param [in,out] _h wysokośc bitmapy 
 * @param [in,out] _bW szerokośc bitmapy w bajtach 
 * @return Wskaźnik na zaalokowaną tablicę 1D BGR... 
 */
unsigned char * readBmp(const char * filename, unsigned int & _w,unsigned int &  _h,unsigned int &  _bW);

/** Funkcja zapisuje skonwertowany obraz do pliku tekstowego
 * @param tab tablica 2 wymiarowa (wsk na wsk)
 * @param [in,out] _w szerokość bitmapy (w bajtach już wyrównanych)
 * @param [in,out] _h wysokośc bitmapy 
 * @param _filename nazwa pliku wyjściowego
 * @param _scale skala obrazka wyjściowego  
 * @return Nic. 
 */
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h,const char * _filename,const int & _scale);

/** Konwertuje wartość na znak, któremu jest przypisany zakres wartości
 * @param  _v Wartość (musi być z zakresu [0,255]), która decyduje jaki znak zostanie zwrócony  
 * @return Znak, który symbolizuje obszar pikseli (obszar może się składać z jednego piksela)
 */
char returnChar (const unsigned int _v);



#endif