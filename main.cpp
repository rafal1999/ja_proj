/** @file */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>
#include <string>

#include "mainFunction.hpp"
//  -i input 
//  -o output 
//  -c || -a bilioteka c ||asm 
// -s [liczba]
int main(int argc, char ** argv)
{
  for(int i=0;i<argc;i++)
  {
    std::cout<<"parametry "<<argv[i]<<std::endl;
  }
  
  std::string outFileName="txt";
  std::string inFileName="bitmapy/logo.bmp";
  unsigned char *pImage; 
  unsigned int byteWidth; ///< szerokośc obrazku w bajtach (wyrównane)
  unsigned int width;
  unsigned int height;
  unsigned int** tabValues; ///< komurka tablicy sybolizuje jeden znak 
  int scale =10;							///<skala w jaką ma być przeskalowany obrazek 
  libMode lM;
  pImage=readBmp(inFileName.c_str(),width,height,byteWidth);
  std::cout<<byteWidth<<std::endl;
  if(pImage==nullptr) 
  {
    return 1;
  }
 	tabValues=returnTabVal(width,height,scale); 
	 
  void (*test)(unsigned char *,unsigned int **,const unsigned int, const unsigned int, const unsigned int, const int);
   void* handle = dlopen("./libC.so", RTLD_LAZY); 
  if (!handle)
  {
    std::cout<<dlerror();
    printf("handle error");
    return 1;
  }
  test=(void (*)(unsigned char *,unsigned int **,const unsigned int  ,const unsigned int,const unsigned int,const int ))dlsym(handle,"convertPixToTabOfVal");
  (*test)(pImage,tabValues,width,height,byteWidth,scale);
  dlclose(handle);
  writeTxt(tabValues,width,height,outFileName.c_str(),scale); 

  delete [] pImage;
	for(int i=0;i<height/scale;i++)
	{
		delete [] tabValues[i];
	}
	delete [] tabValues;
  return 0;
  }


