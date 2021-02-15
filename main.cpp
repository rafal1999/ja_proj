
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
int test(int argc, char ** argv,long int &t1,long int &t2);

//  -i input 
//  -o output 
//  -c || -a bilioteka c ||asm 
// -s [liczba]
int main(int argc, char ** argv)
{
  long int t1=0;
  long int t2=0;
  for(int i=0;i<1;i++)
    test(argc,argv,t1,t2);

  std::cout<<"czas 1: "<<t1/10<<" "<<std::endl;
  std::cout<<"czas 2: "<<t2/10<<std::endl;
  return 0;
  }

  int test(int argc, char ** argv,long int &t1,long int &t2)
  {
    std::string outFileName="txt";
  std::string inFileName="bitmapy/postac.bmp";
  int threadNumber=1;
  unsigned char *pImage; ///<wsk na początek bitmapy 
  unsigned int byteWidth; ///< szerokośc obrazku w bajtach (wyrównane)
  unsigned int width;
  unsigned int height;
  unsigned int heightTabVal;
  unsigned int widthTabVal;
  unsigned int** tabValues; ///< tablica 2D w której każda komórka symbolizuje znak 
  int scale =3;							///<ile razy ma być mniejsza szerokość i wys.  obrazka od obrazka oryginalnego
  libMode lM=libMode::libC;
  void (*convertPixToTabOfVal)(unsigned char *,unsigned int **,unsigned int, unsigned int, ///<wsk na funk
                                unsigned int,  unsigned int, unsigned int);
  void (*average) (unsigned int **, unsigned int,unsigned int , unsigned int ,unsigned int);                        
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
  
 	tabValues=returnTabVal(width,height,scale); 
	heightTabVal=height/scale;
  widthTabVal= width/scale;
 
  if(lM==libMode::libC)
    handle = dlopen("./libC.so", RTLD_LAZY); 
  else if(lM==libMode::libAsm)
    handle = dlopen("./libasm.so", RTLD_LAZY); 

  if (!handle)
  {
    std::cout<<dlerror();
    printf("handle error");
    return 1;
  }
  std::cout<<"liczba wątków: "<<threadNumber<<std::endl;
	if(lM==libMode::libC)
  { 
    convertPixToTabOfVal=(void (*)(unsigned char *,unsigned int **, unsigned int  , unsigned int, unsigned int,
                 unsigned int,unsigned int ))dlsym(handle,"convert");
    average=(void (*)(unsigned int **, unsigned int,unsigned int , unsigned int ,unsigned int))
                      dlsym(handle,"average");
    {
      std::vector<std::thread> vThread;				
      auto start = std::chrono::_V2::high_resolution_clock::now();
      
        unsigned int interval=height/threadNumber;
        for(int i=0;i<threadNumber;i++)
        {
          vThread.push_back(std::thread (convertPixToTabOfVal,pImage,tabValues,width,i*interval,interval*(i+1),byteWidth,scale));    
        }
        if(height%threadNumber!=0)
          vThread.push_back(std::thread (convertPixToTabOfVal,pImage,tabValues,width,threadNumber*interval,height,byteWidth,scale));    
      

      for(auto it=vThread.begin();it!=vThread.end();++it)
        it->join();

      auto stop = std::chrono::_V2::high_resolution_clock::now();
      auto duration =std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
      std::cout << "czas wykonania: "<< duration.count()<<" ms"<< std::endl;
       t1+=duration.count();
    }
    {
      std::vector<std::thread> vThread;				
      auto start = std::chrono::_V2::high_resolution_clock::now();
      
        unsigned int interval=heightTabVal/threadNumber;
        for(int i=0;i<threadNumber;i++)
        {
          vThread.push_back(std::thread (average,tabValues,widthTabVal,i*interval,interval*(i+1),scale));    
        }
        if(heightTabVal%threadNumber!=0)
          vThread.push_back(std::thread (average,tabValues,widthTabVal,threadNumber*interval,heightTabVal,scale));    
      

      for(auto it=vThread.begin();it!=vThread.end();++it)
        it->join();

      auto stop = std::chrono::_V2::high_resolution_clock::now();
      auto duration =std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
      std::cout << "czas wykonania: "<< duration.count()<<" ms"<< std::endl;
      t2+=duration.count();
    }
    
  }
  if(lM==libMode::libAsm)
  { 
    convertPixToTabOfVal=(void (*)(unsigned char *,unsigned int **, unsigned int  , unsigned int, unsigned int,
                 unsigned int,unsigned int ))dlsym(handle,"convert_asm");
    void (*average) (unsigned int **,const unsigned int ,const unsigned int,const int,const unsigned int); 
    average=(void (*)(unsigned int **,const unsigned int ,const unsigned int,const int,const unsigned int))
                      dlsym(handle,"average_asm");
    {
      std::vector<std::thread> vThread;				
      auto start = std::chrono::_V2::high_resolution_clock::now();
      
        unsigned int interval=height/threadNumber;
        for(int i=0;i<threadNumber;i++)
        {
          vThread.push_back(std::thread (convertPixToTabOfVal,pImage,tabValues,byteWidth,width,interval*(i+1),scale,i*interval));    
        }
        if(height%threadNumber!=0)
          vThread.push_back(std::thread (convertPixToTabOfVal,pImage,tabValues,byteWidth,width,height,scale,interval*threadNumber));    
      

      for(auto it=vThread.begin();it!=vThread.end();++it)
        it->join();

      auto stop = std::chrono::_V2::high_resolution_clock::now();
      auto duration =std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
      std::cout << "czas wykonania: "<< duration.count()<<" ms"<< std::endl;
      t1+=duration.count();
    }
    {
      std::vector<std::thread> vThread;				
      auto start = std::chrono::_V2::high_resolution_clock::now();
      
        unsigned int interval=heightTabVal/threadNumber;
        for(int i=0;i<threadNumber;i++)
        {
          vThread.push_back(std::thread (average,tabValues,interval*(i+1),widthTabVal,scale,i*interval));    
        }
        if(heightTabVal%threadNumber!=0)
          vThread.push_back(std::thread (average,tabValues,heightTabVal,widthTabVal,scale,interval*threadNumber));    
      

      for(auto it=vThread.begin();it!=vThread.end();++it)
        it->join();

      auto stop = std::chrono::_V2::high_resolution_clock::now();
      auto duration =std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
      std::cout << "czas wykonania sredni: "<< duration.count()<<" ms"<< std::endl;
      t2+=duration.count();
    }
    
  }
  dlclose(handle);
  writeTxt(tabValues,width,height,outFileName.c_str(),scale); 

  

  delete [] pImage;
	for(unsigned int i=0;i<std::ceil((float)height/scale);i++)
	{
		delete [] tabValues[i];
	}
	delete [] tabValues;
    return 0;
  }