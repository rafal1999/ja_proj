/** @file */
#include <stdio.h>
#include <math.h>
/**
 * @param _pImage wsk na początek bitmapy 
 * @param _tavVal tablica 2 d każda wartość symbolizuje jeden znak  
 */

void convertPixToTabOfVal(unsigned char * _pImage,unsigned int **_tabVal,const unsigned int  _width,const unsigned int  _height,const unsigned int _byteWidth,const int  _scale) 
{
  int n,m,index=0;
  int sizeH=ceil((float)_height/_scale);
  int sizeW=ceil((float)_width/_scale);
  for (int y = 0; y < _height; y++)
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
  for (int y = 0; y < sizeH; y++)
  {
    for (int x = 0; x<sizeW; x++)
    {
      _tabVal[y][x]/=3*_scale*_scale;
    }

  }

  return;
}



  

