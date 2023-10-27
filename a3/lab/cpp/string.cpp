/*
 * string.cpp string object
 * compile: g++ -std=c++0x string.cpp -o string.exe
 * run: string.exe
 */
 
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std; 

int main()
{
  string str1; 
  str1 = "string 1";
  cout << str1 << endl;
  cout << sizeof(str1) << endl;
  cout << &str1 << endl;
  
  string str2("string 2");
  cout << str2 << endl;
  cout << sizeof(str2) << endl;  
  cout << &str2 << endl;
  
  string str3 = str2;
  cout << str3 << endl;
  cout << sizeof(str3) << endl; 
  cout << &str3 << endl;  
  
  
  string *strp = new string("string"); 
  cout << *strp << endl;
  cout << sizeof(strp) << endl; 
  cout << strp << endl;
  delete strp;
  
  // string to integer by string stream
  str1 = "123";
  int a;
  stringstream b(str1); 
  b >> a;
  cout << str1 << " " << b << " " << a << '\n';
  
  // C string is a character array with \0 at the end
  char arr1[] = "character array";
  cout << arr1 << endl;
  
  // assign C string to C++ string
  str1 = arr1; 
  cout << str1 << endl;
  
  // covert C++ string to C string
  cout << str1.c_str() << endl; 
  
  
  return 0;
}
