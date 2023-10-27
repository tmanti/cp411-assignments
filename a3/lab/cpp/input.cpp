/*
 * input.cpp
 * standard input
 * compile: g++ -std=c++0x input.cpp -o input.exe
 * run: input.exe
 */
 
#include <iostream>
#include <string>
using namespace std; 

int main()
{
  int a;
  cout << "Input an integer value:";
  cin >> a;
  cout << "The value entered:" << a << endl;
  cin.ignore(20, '\n'); // flush to the \n position
  
  cout << "Enter a string:" << endl;
  string str;  
  getline(cin, str);  //cin >> str; only gets first word, separated space, tabs, ...
  cout << "The string entered:" << str << endl;
  
  cout << "Enter a string:" << endl;
  char buffer[80]; 
  cin >> buffer;  
  cout << "The string entered:" << buffer << endl;
  
  
  do {
    cout << "Enter a string (quit by *):";
    getline(cin,str);
    cout << "Entered: " << str << '\n';
  } while (str != "*");

  
   
  return 0;
}
