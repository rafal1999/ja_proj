/** @file */
#include "mainFunction.hpp"
#include <cstring>
#include <string>

void helpParams()
{
	std::cout<<"help";
}


bool readParams(const int _argc,char ** _argv,std::string & _inFileName, std::string & _outFileName,libMode & _lM, int &_scale)
{
	printf("tutaj READPARAMS");
  if(_argc!=8)
  {
    return false;
  }
  for(int i=1;i<8;i++)
  {
		std::string arg =_argv[i];
    if("-i"==arg)
    {
			if(i+1<8)
      	_inFileName=_argv[i+1];
			else 
				return 0;
		}
    if("-o"==arg)
    {
			if(i+1<8)
				_outFileName=_argv[i+1];
			else 
				return 1;
    }
    if("-s"==arg)
    {
      _scale=std::stoi(_argv[i+1]);
			// _scale=5:	
    }
    if("-a"==arg)
    {
      _lM=libMode::libAsm;
    }
		if("-c"==arg)
    {
      _lM=libMode::libC;
    }
  }

  return true;
}

unsigned char * readBmp(const char * _filename,unsigned int & _w,unsigned int &  _h)
{
  unsigned char header[54];
  FILE * pF=fopen(_filename,"rb");
  if(pF==nullptr)
  {
    std::cout<<"bład w otwieraniu pliku:"<<_filename<<std::endl;
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

void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h,const char * _filename,const int & _scale)
{
  // c
  FILE *pF = fopen(_filename,"w");
   for(int i=(_h-1);i>-1;i--)
  {
		fprintf(pF,";");
    for(int j=0;j<_w/(3*_scale);j++)
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
  return '#'; 
}
unsigned int ** returnTabVal(const unsigned int _w,const unsigned int _h,const int &_scale)
{
  unsigned int ** tab;
  tab=new unsigned int *[_h];
  for(int i=0;i<_h;i++)
  {
  	tab[i]=new unsigned int [_w/(3*_scale)];
  }
		for(int i=0;i<_h;i++)
	{
		for(int j=0;j<(_w/(3*_scale));j++)//bardzo ważne dzielnie przez 3 możew w przyszłosci przez 6 9 ... zaleznie ile pikseli bedę chciał połknąć 
    {	
			 tab[i][j]=0;
    }
	}	
  return tab;
}