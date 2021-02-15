#include "mainFunction.hpp"
#include <cstring>
#include <string>

void helpParams()
{
	std::cout<<"błędne parametry"<<std::endl;
  std::cout<<"-i <nawa_pliku_we>"<<std::endl;
  std::cout<<"-o <nawa_pliku_wy>"<<std::endl;
  std::cout<<"-s <wartość skali>"<<std::endl;
  std::cout<<"-t <liczba_wątków>"<<std::endl;
  std::cout<<"-a/-c wybór bilioteki asm/C"<<std::endl;
}


bool readParams(const int _argc,char ** _argv,std::string & _inFileName, std::string & _outFileName,libMode & _lM, int &_scale,int & _threadNumber)
{
  
  const int paramsNumber=10;
  if(_argc!=paramsNumber)
  {
    return false;
  }
  for(int i=1;i<paramsNumber;i++)
  {
		std::string arg =_argv[i];
    if("-i"==arg)
    {
			if(i+1<paramsNumber)
      	_inFileName=_argv[i+1];
			else 
				return 0;
		}
    if("-o"==arg)
    {
			if(i+1<paramsNumber)
				_outFileName=_argv[i+1];
			else 
				return 1;
    }
    if("-t"==arg)
    {
			if(i+1<paramsNumber)
      {
				_threadNumber=std::stoi(_argv[i+1]);
         if(_threadNumber<=0)
          return false;
      }
      else 
				return 1;
    }
    if("-s"==arg)
    {
      if(i+1<paramsNumber)
      {
        _scale=std::stoi(_argv[i+1]);
        if(_scale<=0)
          return false;
      }
      else 
        return 1;
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

unsigned char * readBmp(const char * _filename,unsigned int & _w,unsigned int &  _h,unsigned int & _bW)
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

  _bW=3*_w;

  if(_bW % 4) //wyrównanie do 4
  {
    std::cout<<"wyrównanie!"<<std::endl;
    _bW += 4 - (_bW % 4);
  }
  std::cout<<std::endl<<_w<<":"<<_h<<std::endl;
  unsigned char *pP= new unsigned char [_bW*_h];
  fread(pP,sizeof(unsigned char),_bW*_h,pF);
    fclose(pF);
  return pP;
}

void writeTxt(unsigned int **tab,const unsigned int & _w,const unsigned int &  _h,const char * _filename,const int & _scale)
{
  // c
  int sizeH=std::ceil((float)_h/_scale);
  int sizeW=std::ceil((float)_w/_scale);
  FILE *pF = fopen(_filename,"w");
   for(int i=(sizeH-1);i>-1;i--)
  {
		fprintf(pF,";");
    for(int j=0;j<sizeW;j++)
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
  else if (_v<(240) && _v>=(220))		{return '\'';}
	else if	(_v<(220) && _v>=(200))		{return '*';}
	else if	(_v<(200) && _v>=(180))		{return '-';}
	else if	(_v<(180) && _v>=(160))		{return '+';}
	else if	(_v<(160) && _v>=(140))		{return '|';}
	else if	(_v<(120) && _v>=(100))		{return '%';}
	else if	(_v<(100) && _v>=(80))		{return '$';}
	else if	(_v<(80) && _v>=(40))			{return '@';}
  return '#'; 
}
unsigned int ** returnTabVal(const unsigned int _width,const unsigned int _height,const int &_scale)
{
  unsigned int ** tab;
  unsigned int sizeH=std::ceil((float)_height/_scale);
  unsigned int sizeW=std::ceil((float)_width/_scale);
  tab=new unsigned int *[sizeH];
  for(unsigned int i=0;i<sizeH;i++)
  {
  	tab[i]=new unsigned int [sizeW];
  }
		for(int unsigned i=0;i<(sizeH);i++)
	{
		for(int unsigned j=0;j<(sizeW);j++) 
    {	
			 tab[i][j]=0;
    }
	}	
  return tab;
}