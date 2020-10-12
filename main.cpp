#include <iostream>



extern "C" int m();

extern "C" int test();
int main()
{
  std::cout<<"test\n";
  m();
  test();
  return 0;
}