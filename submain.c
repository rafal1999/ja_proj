/** @file */
#include <stdio.h>


void convertPixToTabOfVal(unsigned char ** _pPix,unsigned int **_tabVal,const unsigned int  _w,const unsigned int  _h) 
{
  
	printf("\n-----------C\n");
  for(int i=0;i<_h;i++)
  {
    for(int j=0;j<_w/3;j++)
    {
      for(int o=0;o<3;o++)
      {
      	_tabVal[i][j]+=**_pPix;
      	*_pPix+=sizeof(unsigned char);
      }
			 _tabVal[i][j]/=3;
    }
		_pPix++;	
  }
	printf("\n------\n");
	for(int i=0;i<_h;i++)
	{
		for(int j=0;j<_w/3;j++)
    {	
			 printf("|%3i|",_tabVal[i][j]);
    }
		printf("\n");
	}	
  return;
}

void test ()
{
  printf("tse");
}