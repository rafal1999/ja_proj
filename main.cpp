#include <iostream>



extern "C" int m();

extern "C" int test();
extern "C" int maxofthree(int64_t, int64_t, int64_t);
extern "C" double zwroc_double(double  * p );
int main()
{
  double *p=new double;
  *p=2.2;
 printf("%d\n", maxofthree(10, -4, -7));
  std::cout<<"test="<<zwroc_double(p);
  return 0;
}