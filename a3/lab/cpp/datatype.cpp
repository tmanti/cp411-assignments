/*
 * datatype.cpp
 * compile: g++ -std=c++0x datatype.cpp -o datatype.exe
 * run: datatype.exe
 * source: https://www.cplusplus.com/doc/tutorial/
 */
 
#include <iostream>
using namespace std; 

int main()
{
  cout << "char types" << endl; 
  char c1 = 'A';
  cout << "c1:" << c1 << ", sizeof(c1):"<< sizeof(c1) << endl;
  char16_t c2 = 'A';
  cout << "c2:" << c2 << ", sizeof(c2):"<< sizeof(c2) << endl;
  char32_t c3 = 'A';
  cout << "c3:" << c3 << ", sizeof(c3):"<< sizeof(c3) <<endl;
  
  cout << "int types are the same C (signed char, signed short int, signed int, signed long int, signed long long int (64 bits), unsigned ..." << endl; 
  int a=10;            
  int b(3);              // also initialize b to 3
  int c{2};              // also initialize c to 2
  int d = a + b + c;
  cout << d << endl;
  
  // type casting with auto, and decltype()
  auto a1 = a;
  decltype(b) b1 = b;
  cout << a1+b1 << endl; 
  
  // signed/unsigned long long int types 
  signed long long int a2 = 1111111111111111111;
  cout << a2<< endl;
  
  // Boolean type
  cout << "boolean type, size is 1" << endl; 
  bool e = true, f = false; 
  cout << "e:" << e << ", sizeof(e):" << sizeof(e) << endl;
  cout << "f:" << f << ", sizeof(f):" << sizeof(f) << endl;

  return 0;
}
