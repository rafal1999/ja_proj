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
/**
* @todo zrobic zapisa do pliku a nie na terminal 
*/
void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h)
{
  // c
  FILE *pF = fopen("txt","w");
   for(int i=(_h-1);i>-1;i--)
  {
		fprintf(pF,";");
    for(int j=0;j<_w/3;j++)
    {
			fprintf(pF,"%c",returnChar(tab[i][j]));
    }
    fprintf(pF,";\n");
  }
  fclose(pF);
}
char returnChar(const unsigned int _v)
{
  if  (_v<=(255) && _v>=(240))	{return ' ';}
  if  (_v<(240) && _v>=(220))		{return '\'';}
	if	(_v<(220) && _v>=(200))		{return '*';}
	if	(_v<(200) && _v>=(180))		{return '-';}
	if	(_v<(180) && _v>=(160))		{return '+';}
	if	(_v<(160) && _v>=(140))		{return '|';}
	if	(_v<(120) && _v>=(100))		{return '%';}
	if	(_v<(100) && _v>=(80))		{return '$';}
	if	(_v<(80) && _v>=(40))			{return '@';}
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