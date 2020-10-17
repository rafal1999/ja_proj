#include <iostream>
#include <fstream>
 #include <dlfcn.h>


 unsigned char header[54];

unsigned char * readBMP(const char * filname);

int main()
{
  // int (*m)();
  // void* handle = dlopen("libC.so", RTLD_LAZY);
  // //double * p= new double(2.2);
  // m=  (int (*)())dlsym(handle,"test");
  //   if (!handle)
  // {
  //   return 1;
  // }
  unsigned char *pImage; 
  unsigned char *p; 
  pImage=readBMP("dwanadwa.bmp");
  p=pImage;
  std::cout<<"p="<<(unsigned int)*p<<std::endl;
  
  for(int i=0;i<15;i++)
  {
    printf("%i\n",*p);
    p++;
  }
  FILE *pF = fopen("d.bmp","wb");
  
  fwrite(header,sizeof(unsigned char),54,pF);
  fwrite(pImage,sizeof(unsigned char),16,pF);
  fclose(pF);
  delete [] pImage;
  return 0;
}

unsigned char * readBMP(const char * _filname)
{
  FILE * pF=fopen(_filname,"rb");
  if(pF==nullptr)
  {
    std::cout<<"bład"<<std::endl;
    return nullptr;
  }
  // unsigned char header[54];
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
  std::cout<<std::endl<<width<<":"<<height<<std::endl;
  unsigned char *pP= new unsigned char [width*height];
  fread(pP,sizeof(unsigned char),width*height,pF);
    fclose(pF);
  return pP;
}