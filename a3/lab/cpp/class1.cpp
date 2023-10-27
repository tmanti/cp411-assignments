/*
 * basic class syntax
 * compile: g++ -std=c++0x class1.cpp -o class1.exe
 * run: class1.exe
*/
#include <iostream>
using namespace std;

// Example 0: simple class
class Rectangle {
  int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};
void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}


// Example 1: class with constructor
class Rectangle1 {
  int width, height;
  public:
    Rectangle1 (int,int); // constructor
    int area () {return (width*height);}
};
Rectangle1::Rectangle1 (int a, int b) {
  width = a;
  height = b;
}

// Example 2: class with multiple constructors
class Rectangle2 {
  int width, height;
  public:
    Rectangle2() {
	  width = 5;
      height = 5;
	}
    Rectangle2 (int a,int b) {
	  width = a;
      height = b;
	};
    int area (void) {return (width*height);}
};

// Example 3: class with constructor of initial values 
class Rectangle3 {
  int width, height;
  public:
    Rectangle3() {
	  width = 5;
      height = 5;
	}
    Rectangle3  (int a, int b) : width(a), height(b){}
    int area (void) {return (width*height);}
};


// Example 4: class with operator +, = 
class CVector {
  public:
    int x,y;
    CVector () {};
    CVector (int a,int b) : x(a), y(b) {}
    CVector operator + (const CVector&);
	CVector& operator = (const CVector&);
};
CVector CVector::operator+ (const CVector& param) {
  CVector temp;
  temp.x = x + param.x;
  temp.y = y + param.y;
  return temp;
}
CVector& CVector::operator= (const CVector& param) {
  x=param.x;
  y=param.y;
  return *this;
}


// Example 5: class with constant 
class MyClass {
  int x;
  public:
    MyClass(int val) : x(val) {}
    const int& get() const {return x;}  // constant
    int& get() {return x;}
};


// Example 6: class with destructor, copy and move constructors
class Example {
  string *ptr;
  public:
    Example() : ptr(new string) {}
    Example (const string& str) : ptr(new string(str)) {}
    ~Example() {delete ptr;} // destructor
	Example(const Example& x) : ptr(new string(x.content())) {} // copy constructor
    Example(Example&& x) : ptr(x.ptr) {x.ptr=nullptr;}          // move constructor
    const string& content() const {return *ptr;}    // access content:
	Example& operator = (Example&& x) {
      delete ptr; 
      ptr = x.ptr;
      x.ptr=nullptr;
      return *this;
    }
	Example operator+(const Example& rhs) {	 
      return Example(content()+rhs.content());
    }
};

// Example 7: class templates
template <class T> // T is a type template, can be int, float, double, etc 
class mypair {
    T a, b;
  public:
    mypair(T first, T second) {a=first; b=second;}
    T getmax();
};

template <class T>
T mypair<T>::getmax()
{
  T retval;
  retval = a>b? a : b;
  return retval;
}


// Example 8: class template with specialization
template <class T>
class mycontainer {
    T element;
  public:
    mycontainer (T arg) {element=arg;}
    T increase () {return ++element;}
};
template <> // class template specialization
class mycontainer <char> {
    char element;
  public:
    mycontainer (char arg) {element=arg;}
    char uppercase () {
      if ((element>='a')&&(element<='z'))
      element+='A'-'a';
      return element;
    }
};


int main () {
// Example 0 : test
  Rectangle rect;
  rect.set_values (3,4);
  cout << "area: " << rect.area() << endl;
  
  // Example 1 : test
  Rectangle1 recta (3,4);
  Rectangle1 rectb (5,6);
  cout << "rect area: " << recta.area() << endl;
  cout << "rectb area: " << rectb.area() << endl;
  
  // Example 2 : test
  Rectangle2 rectc(3,4);
  Rectangle2 rectd;
  cout << "rect area: " << rectc.area() << endl;
  cout << "rectb area: " << rectd.area() << endl;
  
  Rectangle2 recte{3,4};
  Rectangle2 rectf={3,4};
  cout << "rect area: " << recte.area() << endl;
  cout << "rectb area: " << rectf.area() << endl;
  
  // Example 3 : test
  Rectangle3 rectg{3,4};
  Rectangle3 recth={3,4};
  cout << "rect area: " << rectg.area() << endl;
  cout << "rectb area: " << recth.area() << endl;
  Rectangle3 *rectp = new Rectangle3(3, 4);
  cout << "*rectp's area: " << rectp->area() << '\n';
  
  // Example 4 : test 
  CVector foo (3,1);
  CVector bar (1,2);
  CVector result = foo + bar;
  cout << result.x << ',' << result.y << '\n';
  foo=bar;
  cout << foo.x << ',' << foo.y << '\n';
  cout << foo.x << ',' << foo.y << '\n';
 
 
 // Example 5:
  MyClass foo1(10);
  const MyClass bar1(20);
  foo1.get() = 15;            // ok: get() returns int&
  // bar.get() = 25;         // not valid: get() returns const int&
  cout << foo1.get() << '\n';
  cout << bar1.get() << '\n';
  
  // Example 6:
  Example foo2("Example");
  cout << "foo2's content: " << foo2.content() << '\n';
  Example bar2(foo2);
  cout << "bar2's content: " << bar2.content() << '\n';
  Example bar3 = foo2;
  cout << "bar3's content: " << bar3.content() << '\n';
  Example foo3 ("Exam");
  cout << "foo3's content: " << foo3.content() << '\n';
  Example bar4 = Example("ple");   // move-construction
  cout << "bar4's content: " << bar4.content() << '\n';
  foo3 = foo3 + bar4;               // move-assignment
  cout << "foo3=foo3_bar4 content:" << foo3.content() << '\n';
  
  // Example 7
  mypair <int> myobject (100, 75);
  cout << myobject.getmax();
  
  // Example 8  
  mycontainer<int> myint (7);
  mycontainer<char> mychar ('j');
  cout << myint.increase() << endl;
  cout << mychar.uppercase() << endl;
  
  return 0;
}
