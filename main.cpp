/** @file */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>
#include <string>
#include <thread>
#include <vector>
#include <chrono> 

#include "mainFunction.hpp"
//  -i input 
//  -o output 
//  -c || -a bilioteka c ||asm 
// -s [liczba]
int main(int argc, char ** argv)
{
  std::string outFileName="txt";
  std::string inFileName="bitmapy/postac.bmp";
  std::vector<std::thread> vThread;
  int threadNumber=64;
  unsigned char *pImage; ///<wsk na początek bitmapy 
  unsigned int byteWidth; ///< szerokośc obrazku w bajtach (wyrównane)
  unsigned int width;
  unsigned int height;
  unsigned int** tabValues; ///< tablica 2D w której każda komórka symbolizuje znak 
  int scale =3;							///<ile razy ma być mniejsza szerokość i wys.  obrazka od obrazka oryginalnego
  libMode lM=libMode::libC;
  void (*convertPixToTabOfVal)(unsigned char *,unsigned int **,const unsigned int,const unsigned int, ///<wsk na funk
                               const unsigned int, const unsigned int, const int);
  void* handle=nullptr; ///<uchwyt do biblioteki dynamicznej
  if(!readParams(argc,argv,inFileName,outFileName,lM,scale,threadNumber))
  {
    helpParams();
    return 1;
  }

  pImage=readBmp(inFileName.c_str(),width,height,byteWidth);
  if(pImage==nullptr) 
  {
    return 1;
  }
  unsigned int sizeH=std::ceil((float)height/scale);
  unsigned int sizeW=std::ceil((float)width/scale);
 	tabValues=returnTabVal(sizeW,sizeH,scale); 
	 
 
  if(lM==libMode::libC)
    handle = dlopen("./libC.so", RTLD_LAZY); 
  else if(lM==libMode::libAsm)
    std::cout<<"LIB ASM NIE DZIĄŁA JESZCZE\n"; 

  if (!handle)
  {
    std::cout<<dlerror();
    printf("handle error");
    return 1;
  }
  convertPixToTabOfVal=(void (*)(unsigned char *,unsigned int **,const unsigned int  ,const unsigned int,const unsigned int,
                const unsigned int,const int ))dlsym(handle,"convertPixToTabOfVal");
								
  auto start = std::chrono::_V2::high_resolution_clock::now();
  {
    int interval=height/threadNumber;
    for(int i=0;i<threadNumber;i++)
    {
      vThread.push_back(std::thread (convertPixToTabOfVal,pImage,tabValues,width,i*interval,interval*(i+1),byteWidth,scale));    
    }
    if(height%threadNumber!=0)
      vThread.push_back(std::thread (convertPixToTabOfVal,pImage,tabValues,width,threadNumber*interval,height,byteWidth,scale));    
  }
  
  for(auto it=vThread.begin();it!=vThread.end();++it)
    it->join();

  auto stop = std::chrono::_V2::high_resolution_clock::now();

  dlclose(handle);
	
  writeTxt(tabValues,width,height,outFileName.c_str(),scale); 

  auto duration =std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "czas wykonania: "<< duration.count()<<" ms"<< std::endl; 

  delete [] pImage;
	for(unsigned int i=0;i<sizeH;i++)
	{
		delete [] tabValues[i];
	}
	delete [] tabValues;
  return 0;
  }







































// vThread.push_back(std::thread (test,pImage,tabValues,width,0,height/2,byteWidth,scale));
  // vThread.push_back(std::thread(test,pImage,tabValues,width,height/2,height,byteWidth,scale));
  // (*test)(pImage,tabValues,width,0,height,byteWidth,scale);