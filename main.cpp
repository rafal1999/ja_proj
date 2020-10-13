#include <iostream>
#include <fstream>





extern "C" int m();

extern "C" int test();
extern "C" int maxofthree(int64_t, int64_t, int64_t);
extern "C" double zwroc_double(double  * p );

unsigned char * readBMP(const char * filname);

int main()
{

  std::cout<<readBMP("k.bmp")<<std::endl;
  return 0;
}

unsigned char * readBMP(const char * _filname)
{
  std::ifstream inF(_filname, std::ios::binary);
 
  if(!inF.is_open())
  {
    std::cout<<"bład"<<std::endl;
    return nullptr;

  }
return nullptr;
}