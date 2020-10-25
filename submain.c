/** @file */
#include <stdio.h>


void convertPixToTabOfVal(unsigned char ** _pPix,unsigned int **_tabVal,const unsigned int  _w,const unsigned int  _h,const int  _scale) 
{
  
	printf("\n-----------C\n");
  for(int i=0;i<_h;i++)
  {
    for(int j=0;j<_w/(3*_scale);j++)
    {
      for(int o=0;o<(3*_scale);o++)
      {
      	_tabVal[i][j]+=**_pPix;
      	*_pPix+=sizeof(unsigned char);
      }
			 _tabVal[i][j]/=(3*_scale);
    }
		_pPix++;	
  }
  { //zakomentowany blok testowy 
	// printf("\n------\n");
	// for(int i=0;i<_h;i++)
	// {
	// 	for(int j=0;j<_w/3;j++)
  //   {	
	// 		 printf("|%3i|",_tabVal[i][j]);
  //   }
	// 	//  printf("\n");  
	// }
  }	
  return;
}