/*
 * function.cpp
 * description: C++ provides more ways to define functions
 * compile: g++ -std=c++0x function.cpp -o function.exe
 * run: function.exe
 */
 
#include <iostream>
#include <string>
using namespace std;

/* Example 1: pass by value */
void duplicate(int a, int b)
{
  a*=2;
  b*=2;
}

/* Example 2: pass by reference, change external values, like pass by pointers in C */
void duplicate1(int& a, int& b) 
{
  a*=2;
  b*=2;
}

/* Example 3: not allowed to change parameter values */
void foo (const int a, const int b)  
{
   cout << "x=" << a << ", y=" << b << endl;
}


/* Example 4: copy string values to functon */
string concatenate (string a, string b)
{
  return a+b;   // create and return new string value
}

/* Example 5: copy string references to function  */
string concatenate1 (string& a, string& b)
{
  return a+b;  // create and return new string value
}

// Example 6:
int increase_by (int a, int b=1)
{
  int r;
  r=a+b;
  return (r);
}

// Example 7: over load
int operate(int a, int b)
{
  return (a*b);
}

double operate(double a, double b)
{
  return (a+b);
}

// Example 8: function templates
template <class T>
T sum(T a, T b)
{ 
  return a+b;
}
template <class T, class U>
T sum2(T a, U b)
{
  T result;
  result = a + (T) b;
  return result;
}
template <class T, int N>
T fixed_add (T val)
{
  return val + N;
}


int main ()
{
	
  // Example 1, 2, 3	
  int x=1, y=2;
  duplicate (x, y);
  cout << "x=" << x << ", y=" << y << endl;
  
  duplicate1 (x, y);
  cout << "x=" << x << ", y=" << y << endl;
  
  foo (x, y);
  cout << "x=" << x << ", y=" << y << endl;
  
  // Example 4, 5
  string str1 = "hello ";
  string str2 = "world!";
  cout << concatenate(str1, str2) << endl;
  cout << concatenate1(str1, str2) << endl;
  
  // Example 6
  cout << "increase_by(2,1)  "  << increase_by(2, 1) << endl;
  cout << "increase_by(2)    "  << increase_by(2) << endl;
  cout << "increase_by(2,2)  "  << increase_by(2,2) << endl;
  
  // Example 7
  x=5;
  y=2;
  double n=5.0,m=2.0;
  cout << "operate(5,2)     " << operate (x,y) << '\n';
  cout << "operate(5.0,2.0) " << operate (n,m) << '\n';
  
  
  // Example 8:
  cout << "sum(5,2)     " << sum(x,y) << '\n';
  cout << "sum(5.0,2.0) " << sum(n,m) << '\n';
  cout << "sum<int>(5,2)     " << sum<int>(x,y) << '\n';
  cout << "sum<double>(5.0,2.0) " << sum<double>(n,m) << '\n';
  cout << "sum2<int,int>(5,2)     " << sum2<int,int>(x,y) << '\n';
  cout << "sum2<int,double>(5,2.2) " << sum2<int,double>(n,m) << '\n';
  cout << "sum2(5,2)     " << sum2(x,y) << '\n';
  cout << "sum2(5,2.2) " << sum2(5,2.2) << '\n';
  cout << fixed_add<int,2>(10) << '\n';
  cout << fixed_add<int,3>(10) << '\n'; 
   
  return 0;
}

