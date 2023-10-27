/*
 * exceptions 
 * compile: g++ -std=c++0x class5.cpp -o class5.exe
 * run: class5.exe
 */

#include <iostream>
#include <exception>

using namespace std;

// Example 3 : user defined exception class
class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "My exception happened";
  }
} myex;


int main () {
  // Example 1 : directly throw 	
  try
  {
    throw 20;
  }
  catch (int e)
  {
    cout << "An exception occurred. Exception Nr. " << e << '\n';
  }
  
  // Example 2 : use provided exception class
   try
  {
    int* myarray= new int[1000];
  }
  catch (exception& e)
  {
    cout << "Standard exception: " << e.what() << endl;
  } 
  
  // Example 3 : use user defined exception class
  try
  {
    throw myex;
  }
  catch (exception& e)
  {
    cout << e.what() << '\n';
  }
  
  return 0;
}