/*
 * class4.cpp
 * class casting
 * compile: g++ -std=c++0x class4.cpp -o class4.exe
 * run: class4.exe 
 */

// implicit conversion of classes:
#include <iostream>
#include <exception>
#include <typeinfo>  // for functions of type info 
using namespace std;

// cast
class A {};
class B {
public:
  // conversion from A (constructor):
  B (const A& x) {}
  // conversion from A (assignment):
  B& operator= (const A& x) {return *this;}
  // conversion to A (type-cast operator)
  operator A() {return A();}
};


// Type casting
class Dummy {
    int i,j;
	public:
	Dummy(int x, int y) : i(x), j(y) {}
};
class Addition {
    int x,y;
  public:
    Addition (int a, int b) { x=a; y=b; }
    int result() { return x+y;}
};


//dynamic_cast
class Base { virtual void dummy() {} };
class Derived: public Base { int a; };


void print (char * str)
{
  cout << str << '\n';
}

int main ()
{
  A foo;
  B bar = foo;    // calls constructor
  bar = foo;      // calls assignment
  foo = bar;      // calls type-cast operator
  
  
  Dummy d{1,2};
  Addition *padd;
  padd = (Addition*) &d;
  cout << padd->result() << endl;
  
   try {
    Base * pba = new Derived;
    Base * pbb = new Base;
    Derived * pd;

    pd = dynamic_cast<Derived*>(pba);
    if (pd==0) cout << "Null pointer on first type-cast.\n";

    pd = dynamic_cast<Derived*>(pbb);
    if (pd==0) cout << "Null pointer on second type-cast.\n";

  } catch (exception& e) {cout << "Exception: " << e.what();}
  
 
  const char * c = "sample text";
  print ( const_cast<char *> (c) );
  
  
  int * a,b;
  a=0; b=0;
  if (typeid(a) != typeid(b))
  {
    cout << "a and b are of different types:\n";
    cout << "a is: " << typeid(a).name() << '\n';
    cout << "b is: " << typeid(b).name() << '\n';
  }
  
  try {
    Base* a = new Base;
    Base* b = new Derived;
    cout << "a is: " << typeid(a).name() << '\n';
    cout << "b is: " << typeid(b).name() << '\n';
    cout << "*a is: " << typeid(*a).name() << '\n';
    cout << "*b is: " << typeid(*b).name() << '\n';
  } catch (exception& e) { cout << "Exception: " << e.what() << '\n'; }
  
  return 0;
}