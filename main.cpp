#include <iostream>
#include <fstream>
#include <dlfcn.h>

struct Pixel
{
   char blue,green,red;
};

 unsigned char header[54];
// extern "C" int m();

// extern "C" int test();
// extern "C" int maxofthree(int64_t, int64_t, int64_t);
// extern "C" double  zwroc_double(double  * p );

Pixel * readBMP(const char * filname);

int main()
{
  int (*m)();
  void* handle = dlopen("libC.so", RTLD_LAZY);
  //double * p= new double(2.2);
  m=  (int (*)())dlsym(handle,"test");

 std::cout<<"readBMO="<<(*m)()<<std::endl;
if (!handle)
{
  return 1;
}
// int a=  ;
  return 0;
}

Pixel * readBMP(const char * _filname)
{
  FILE * pF=fopen(_filname,"rb");
  if(pF==nullptr)
  {
    std::cout<<"bład"<<sizeof(unsigned int)<<std::endl;
    return nullptr;
  }
  int o=1;
  fread(header,sizeof(unsigned char),54,pF);
  unsigned int width = *(int*)&header[18];
  unsigned int height = *(int*)&header[22];
  std::cout<<std::endl<<width<<":"<<height<<std::endl;
  width*=3;

  if(width % 4) //wyrównanie do 4
  {
    std::cout<<"wyrównanie!"<<std::endl;
    width += 4 - (width % 4);
  }
  // Pixel* pP=new Pixel[width * height];
  unsigned char *t= new unsigned char ;
  for (unsigned int i = 0; i < width*height ; i++)
  {
       if(i%3==0)
    {
      
      std::cout<<o<<"#------------\n";
      o++;
    }
    
    //  fread(pP,sizeof(Pixel),3,pF);
    fread(t,sizeof(unsigned char),1,pF);
    printf("%d--%u\n",i,*t);
 
  }
  
  // std::cout<< int (pP->blue)<<";"<<int(pP[0].green)<<";"<< int(pP->red);
  //printf("%u",*t);

  
  delete pF;

  //  FILE * p=fopen("test.bmp","w");
  // fclose(p);
  
  // delete pF;
  // fwrite(header,sizeof(unsigned char),54,pF);
  // fwrite(pP,sizeof(unsigned char),width*height,pF);


// delete [] pP ;
  return nullptr;
}