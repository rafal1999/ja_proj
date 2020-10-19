#include <iostream>
#include <fstream>
#include <dlfcn.h>


unsigned char header[54];
char tabOfchars[]={' ','*','|','=','@'};//na razie 5 znaków 
unsigned char * readBMP(const char * filname);

int main(int argc, char ** argv)
{
  int txtImageWidht=100;
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
  pImage=readBMP("jeden .bmp");
  p=pImage;
  std::cout<<"p=ddd"<<(unsigned int)*p<<std::endl;
  unsigned char **t=nullptr;
  t=new  unsigned char* [4];//ilość komórek  wsk bedze zależna od ilości wątków 
  unsigned char ** pStartT = t;

  *t=p;
  t++;
  *t=p+(4*3);
  t++;
  *t=p+(8*3);

  t++;
  *t=p+(12*3);
  t-=3;
  *t+=3*2+6;//poruszasz się po ala 2 d tab
  for(int i=0;i<12*4;i++)
  {
    printf("%d-%i\n",i,*p);
    p++;
  }
  for(int i=0;i<12;i++);

 printf("eeee%i",**t);
  FILE *pF = fopen("d.bmp","w");
  fwrite(header,sizeof(unsigned char),54,pF);
  fwrite(pImage,sizeof(unsigned char),12*4,pF);
  fclose(pF);
  delete [] pImage;
  delete [] pStartT;
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