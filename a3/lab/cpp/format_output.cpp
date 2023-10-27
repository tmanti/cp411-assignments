/*
 * format_output.cpp
 * format output, better use C printf function
 * compile: g++ -std=c++0x format_output.cpp -o format_output.exe
 * run: format_output.exe
 * source: adopted from http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html/
 */
 
#include <iostream>

using std::cout;
using std::endl;
using std::dec;
using std::oct;
using std::hex;

int main()
{
  long int pos_value =  12345678;  
  long int neg_value = -87654321;
  float value = 2.71828;

  cout << "The decimal value 12345678 is printed out as" << endl;
  cout << "decimal:     " << pos_value << endl;
  cout << "octal:       " << oct << pos_value << endl;
  cout << "hexadecimal: " << hex << pos_value << endl << endl;

  cout << "The decimal value -87654321 is printed out as" << endl;
  cout << "decimal:     " << dec << neg_value << endl;
  cout << "octal:       " << oct << neg_value << endl;
  cout << "hexadecimal: " << hex << neg_value << endl << endl;

  cout << "The decimal value 2.71828 is printed out as" << endl;
  cout << "decimal:     " << dec << value << endl;
  cout << "octal:       " << oct << value << endl;
  cout << "hexadecimal: " << hex << value << endl << endl;
  
  return 0;
}
