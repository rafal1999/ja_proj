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
  
  std::string outFileName;
  std::string inFileName;
  int txtImageWidht=100;
  unsigned char *pImage; 
  unsigned char *p; 
  unsigned int width;
  unsigned int height;
  unsigned int **tab;
  int scale =1;
  libMode lM;
  printf("\n\n-----\n");
  if(!readParams(argc,argv,inFileName,outFileName,lM,scale))
  {
    std::cout<<"błędne parametry"<<std::endl;
    std::cout<<"parmaetry"<<inFileName<<outFileName<<scale<<std::endl;
    return 1;
  }
  std::cout<<"parmaetry"<<inFileName<<outFileName<<scale<<int(lM)<<std::endl;
  pImage=readBmp("bitmapy/kaczor.bmp",width,height);
  if(pImage==nullptr) 
  {
    return 1;
  }
  std::cout<<std::endl<<width<<"--"<<height<<std::endl;
	tab=returnTabVal(width,height);
  p=pImage;
  std::cout<<"p=ddd"<<(unsigned int)*p<<std::endl;
  unsigned char **t=nullptr;//tablica BGR
  t=new  unsigned char* [height];//ilość komórek  wsk bedze zależna od ilości wątków 
  unsigned char ** pStartT = t;
	for (unsigned int i = 0; i < height; i++)
	{
		*t=p+(width*i);
		t++; //ostrożnie ostanie wywołanie petli wchodzi na nie swojapamięć!!!!
	}
	t-=(height);  //<-dlatego tutaj nie może być height -1 !!!!
  {//blok testowy nie otwierac 
  // for(int i=0;i<width*height;i++) //tu tylko testowe wyświetlanie 
  // {
  //   printf("|%3i|",*p);
	// 	if(i==11 ||i==23 || i==35 || i==47)
	// 		std::cout<<std::endl;
  //   p++;
  // }
	// printf("\n---------2D-------------\n");
  // for(int i=0;i<height;i++) //tu tylko testowe wyświetlanie 
  // {
  //   for(int j=0;j<width;j++)
  //   {
  //   	printf("|%3i|",**t);
	// 		*t+=sizeof(unsigned char);
  //   }
	// 	printf("\n");
	// 	*t-=sizeof(unsigned char) * width; // wroc
	// 	t++;
  // }
  // printf("\n---------2D-------------\n");
  
  // printf("\npokazywanie tablicy wartości testowe dogóry nogmi-----\n"); //pokazywanie tablicywartosći pamiętaj że tutaj skla może byc
  // for(int i=(height-1);i>-1;i--)
  // {
  //   for(int j=0;j<width/3;j++)
  //   {
  //     printf("|%3i|",tab[i][j]);
  //   }
  //   printf("\n");
  // }
}
  void (*test)(unsigned char **,unsigned int **,const unsigned int  ,const unsigned int  );
   void* handle = dlopen("./libC.so", RTLD_LAZY); 
  printf("+++++++\n"); 
  if (!handle)
  {
    std::cout<<dlerror();
    printf("handle error");
    return 1;
  }
 
  test=(void (*)(unsigned char **,unsigned int **,const unsigned int  ,const unsigned int ))dlsym(handle,"convertPixToTabOfVal");
  (*test)(pStartT,tab,width,height);
  dlclose(handle);
  writeTxt(tab,width,height,"txt"); //todo 
  { //zwalnianie pamięci 
  delete [] pImage;
  delete [] pStartT;
  for(int i=0;i<height;i++)
    delete  [] tab[i];
  delete [] tab;
  return 0;
  }
}

