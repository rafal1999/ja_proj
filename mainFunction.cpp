/** @file */
#include "mainFunction.hpp"

unsigned char * readBmp(const char * _filname,unsigned int & _w,unsigned int &  _h)
{
  unsigned char header[54];
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
//TODO zrobic zapisa do pliku a nie na terminal 
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h)
{
  // c
  FILE *pF = fopen("txt","w");
   for(int i=(_h-1);i>-1;i--)
  {
    for(int j=0;j<_w/3;j++)
    {
			printf("%c",returnChar(tab[i][j]));
    }
    printf("\n");
  }
  (pF,"%i",tab[0][0]);
  fclose(pF);
}
char returnChar(const unsigned int _v)
{
  char tabOfchars[]={' ','*','|','=','@'};//na razie 5 znaków 
  if  (_v<=(255) && _v>=(240))	{return ' ';}
  else 													{return '#';} 
  return 0; //tymaczasowo
}
unsigned int ** returnTabVal(const unsigned int _w,const unsigned int _h)
{
  unsigned int ** tab;
  tab=new unsigned int *[_h];
  for(int i=0;i<_h;i++)
  {
  	tab[i]=new unsigned int [_w/3];
  }
		for(int i=0;i<_h;i++)
	{
		for(int j=0;j<(_w/3);j++)//bardzo ważne dzielnie przez 3 możew w przyszłosci przez 6 9 ... zaleznie ile pikseli bedę chciał połknąć 
    {	
			 tab[i][j]=0;
    }
		printf("\n");
	}	
  return tab;
}