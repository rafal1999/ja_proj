#include <iostream>
#include <fstream>
#include <cstdio>
#include <dlfcn.h>
#include <cmath>

unsigned char header[54];

unsigned char * readBmp(const char * filname, unsigned int & _w,unsigned int &  _h);
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h);
char returnChar (const unsigned int _v);
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
  tab=new unsigned int *[4];
  *tab=new unsigned int [4];
  // tab[0][0]=10;
  pImage=readBmp("4na4.bmp",width,height);
  if(pImage==nullptr)
  {
    return 1;
  }
  
  p=pImage;
  std::cout<<"p=ddd"<<(unsigned int)*p<<std::endl;
  unsigned char **t=nullptr;//tablica BGR
  t=new  unsigned char* [4];//ilość komórek  wsk bedze zależna od ilości wątków 
  unsigned char ** pStartT = t;
  std::cout<<std::endl<<width<<"--"<<height<<std::endl;
  *t=p;
  t++;
  *t=p+(width);
  t++;
  *t=p+(width*2);

  t++;
  *t=p+(width*3);
  // t-=3;
  // *t+=3*2+6;//poruszasz się po ala 2 d tab
  for(int i=0;i<12*4;i++)
  {
    printf("%d-%i\n",i,*p);
    p++;
  }
 

  // printf("eeee%i",**t);
  void (*test)(unsigned char **,unsigned int **,const unsigned int  ,const unsigned int  );
  void* handle = dlopen("./libC.so", RTLD_LAZY);
  std::cout<<dlerror();
  if (!handle)
  {
    printf("handle error");
    return 1;
  }
  test=(void (*)(unsigned char **,unsigned int **,const unsigned int  ,const unsigned int ))dlsym(handle,"convertPixToTabOfVal");
  (*test)(pStartT,tab,12,4);
  dlclose(handle);
  
  // fprintf(pF,"%3i",12);
    
  
  // fwrite(header,sizeof(unsigned char),54,pF);
  // fwrite(pImage,sizeof(unsigned char),12*4,pF);
  delete [] pImage;
  delete [] pStartT;
  // writeTxt(tab,1,1);
  //  for(int i=0;i<1;i++)
     delete  [] *tab;
  delete [] tab;
  
  return 0;
}

unsigned char * readBmp(const char * _filname,unsigned int & _w,unsigned int &  _h)
{
  FILE * pF=fopen(_filname,"rb");
  if(pF==nullptr)
  {
    std::cout<<"bład w otwieraniu pliku:"<<_filname<<std::endl;
    return nullptr;
  }
  // unsigned char header[54];
  fread(header,sizeof(unsigned char),54,pF);
  _w = *(int*)&header[18];
  _h = *(int*)&header[22];

  _w*=3;

  if(_w % 4) //wyrównanie do 4
  {
    std::cout<<"wyrównanie!"<<std::endl;
    _w += 4 - (_w % 4);
  }
  std::cout<<std::endl<<_w<<":"<<_h<<std::endl;
  unsigned char *pP= new unsigned char [_w*_h];
  fread(pP,sizeof(unsigned char),_w*_h,pF);
    fclose(pF);
  return pP;
}
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h)
{
  // c
  FILE *pF = fopen("txt","w");
  // for (int i = 0; i < 4; i++)
  // {
  //   for(unsigned int j=0;j<_w;j++)
  //   {
    
  //   }
  // }
  fprintf(pF,"%i",tab[0][0]);
  // fwrite(header,sizeof(unsigned char),54,pF);
  // fwrite(pImage,sizeof(unsigned char),12*4,pF);
  fclose(pF);
}
char returnChar(const unsigned int _v)
{
  char tabOfchars[]={' ','*','|','=','@'};//na razie 5 znaków 
  if  (_v<=((pow(255,3))/3) && _v>=((pow(240,3))/3)) {return ' ';}
  else {return '# ';} 
  return 0; //tymaczasowo
}