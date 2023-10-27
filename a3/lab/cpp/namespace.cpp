/*
 * namespace.cpp
 * description: examples of namespace
 * compile: g++ -std=c++0x namespace.cpp -o namespace.exe
 * run: namespace.exe
 */
 
#include <iostream>
namespace newstd = std;  // use namespace to define a aliasing for std

// use namespace to define a group of variables
// same variable identifiers can be reused in different namespace
namespace first
{
  int x = 5;
  int y = 10;
  int z = 20;
}

namespace second
{
  double x = 3.1416;
  double y = 2.7183;
  int z = 4;
}


// use namespace to define a group of functions
namespace foo
{
  int value() { return 5; }
}

// use namespace to define a group of variables and functions
namespace bar
{
  const double pi = 3.1416;
  double value() { return 2*pi; }
}

int main () {
  newstd::cout << "namespace newstd=std" << newstd::endl; 
	
  using namespace newstd;
  cout << "using namespace newstd" << endl; 
	
  cout << "namespace first" << endl; 
  cout << first::x << '\n'; 
  cout << first::z << '\n';  
  
  cout << "using first::y" << endl; 
  using first::y;    
  cout << y << '\n'; 
  
  cout << "using namespace second" << endl; 
  using namespace second;
  cout << x << '\n';
  cout << y << '\n';
  cout << z << '\n'; 

  cout << "namespace foo and bar" << endl; 
  cout << foo::value() << '\n';
  cout << bar::value() << '\n';
  cout << bar::pi << '\n';
 
 return 0;
}