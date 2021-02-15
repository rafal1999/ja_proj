/** @file 
 * Biblioteka C
*/


#include <stdio.h>
#include <math.h>

/** Funkja odpowednio dodaje bajty do komórek dynamicznie zaalkowanej tablicy tablicy 2D 
 * @param _pImage wsk na początek bitmapy 
 * @param _tabVal tablica 2D każda komórka tej tablicdoxyy przechowuje wartość znaku który ma być pokazany w pliku tekstowym 
 * @param _width szerokość obrazka  _tabVal
 * @param _startHeight wysokość obrazka  od której funk. ma liczyć 
 * @param _stopHeight wysokość obrazka  do której funk. ma liczyć
 * @param _byteWidth szerowkość bitmapy w bajtach 
 * @param _scale  ile razy ma być mniejsza szerokośc i wysokość obrazka w pliku txt względem bitmampy 
 * @return nic 
 */
void convert(unsigned char * _pImage,unsigned int **_tabVal,const unsigned int  _width,const unsigned int  _startHeight,
                  const unsigned int _stopHeight ,const unsigned int _byteWidth,const int  _scale) 
{
  int n,m;
  for (int y = _startHeight; y < _stopHeight; y++)
  {
    for (int x = 0; x<_width; x++)
    {
      n=x/_scale;
      m=y/_scale;
      _tabVal[m][n]+=_pImage[3*x+_byteWidth*y];
      _tabVal[m][n]+=_pImage[3*x+_byteWidth*y+1];
      _tabVal[m][n]+=_pImage[3*x+_byteWidth*y+2];
    }
  }
}
/** Funkcja liczy średnią dla każdej komórki aby wartości komórek były z przedziału [0,255]
 * @param tabVal tablica 2D (wsk na wsk) każda komórka tej tablicy przechowuje wartość znaku który ma być pokazany w pliku tekstowym 
 * @param _width szerokość obrazka  _tabVal
 * @param _startHeight wysokość obrazka  od której funk. ma liczyć 
 * @param _stopHeight wysokość obrazka  do której funk. ma liczyć
 * @param  _scale  ile razy ma jest mniejsza szerokośc i wysokość obrazka w pliku txt względem bitmampy 
 */
void average(unsigned int **_tabVal,const unsigned int  _width,const unsigned int   _startHeight,const unsigned int   _stopHeight,const int  _scale)
{
  
  for (int i = _startHeight; i < _stopHeight; i++)
  {
    for (int j = 0; j < _width; j++)
    {
      _tabVal[i][j]/=3.0*_scale*_scale;
    }
  }
}

