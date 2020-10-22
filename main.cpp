/** @file */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>

#include "mainFunction.hpp"
//  -i input 
//  -o output 
//  -c bilioteka c
//  -a biblioteka asm
int main(int argc, char ** argv)
{
  int txtImageWidht=100;
  unsigned char *pImage; 
  unsigned char *p; 
  unsigned int width;
  unsigned int height;
  unsigned int **tab;
  pImage=readBmp("4na4.bmp",width,height);
  if(pImage==nullptr)
  {
    return 1;
  }
	tab=returnTabVal(width,height);
  p=pImage;
  std::cout<<"p=ddd"<<(unsigned int)*p<<std::endl;
  unsigned char **t=nullptr;//tablica BGR
  t=new  unsigned char* [4];//ilość komórek  wsk bedze zależna od ilości wątków 
  unsigned char ** pStartT = t;
  std::cout<<std::endl<<width<<"--"<<height<<std::endl;
  
	for (unsigned int i = 0; i < height; i++)
	{
		*t=p+(width*i);
		t++; //ostrożnie ostanie wywołanie petli wchodzi na nie swojapamięć!!!!
	}
	t-=(height); //<-dlatego tutaj nie może być height -1 !!!!
 	
/*
	*t=p+(width*0);
	t++;
	// *t+=width;
  *t=p+(width*1);
  t++;
  *t=p+(width*2);

  t++;
  *t=p+(width*3);
	*/
  // t-=3;
  // *t+=3*2+6;//poruszasz się po ala 2 d tab
  // *t--;
    printf("test\n");
//###########################################################
  for(int i=0;i<width*height;i++)
  {
    printf("|%3i|",*p);
		if(i==11 ||i==23 || i==35 || i==47)
			std::cout<<std::endl;
    p++;
  }
	printf("\n----------------------\n");
  for(int i=0;i<height;i++)
  {
    for(int j=0;j<width;j++)
    {
    	printf("|%3i|",**t);
			*t+=sizeof(unsigned char);
    }
		printf("\n");
		*t-=sizeof(unsigned char) * width; // wroc
		t++;
  }
//##############################################################
  void (*test)(unsigned char **,unsigned int **,const unsigned int  ,const unsigned int  );
  void* handle = dlopen("./libC.so", RTLD_LAZY); 
  std::cout<<dlerror();
  if (!handle)
  {
    printf("handle error");
    return 1;
  }
  test=(void (*)(unsigned char **,unsigned int **,const unsigned int  ,const unsigned int ))dlsym(handle,"convertPixToTabOfVal");
  (*test)(pStartT,tab,width,height);
  dlclose(handle);
	//#########################################################
  printf("\n-----\n"); //pokazywanie tablicywartosći 
  for(int i=(height-1);i>-1;i--)
  {
    for(int j=0;j<width/3;j++)
    {
      printf("|%3i|",tab[i][j]);
    }
    printf("\n");
  }
  //########################################################
  writeTxt(tab,width,height);
  delete [] pImage;
  delete [] pStartT;
  // writeTxt(tab,1,1);
  for(int i=0;i<height;i++)
    delete  [] tab[i];
  delete [] tab;
  
  return 0;
}

