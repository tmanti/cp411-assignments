/*
 * friend, inheritance of classes
 * compile: g++ -std=c++0x class2.cpp -o class2.exe
 * run: class2.exe
*/

#include <iostream>
using namespace std;

// Example 1: friend
class Square;
class Rectangle {
    int width, height;
  public:
    int area ()
      {return (width * height);}
    void convert (Square a);
};
class Square {
  friend class Rectangle; // Friend class, add all methods of friend class to this class
  private:
    int side;
  public:
    Square (int a) : side(a) {}
};
void Rectangle::convert (Square a) {
  width = a.side;
  height = a.side;
}

// Example 2: inheritance between classes 
class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b;}
};
class Rectangle1: public Polygon {  
  public:
    int area ()
      { return width * height; }
};
class Triangle: public Polygon {
  public:
    int area ()
      { return width * height / 2; }
};

  
// Example 3: Inheritance of more classes, many-to-one inheritance 
class Polygon2 {
  protected:
    int width, height;
  public:
    Polygon2 (int a, int b) : width(a), height(b) {}
};  
class Output {
  public:
    static void print (int i);
};
void Output::print (int i) {
  cout << i << '\n';
}
class Rectangle2: public Polygon2, public Output {
  public:
    Rectangle2 (int a, int b) : Polygon2(a,b) {}
    int area ()
      { return width*height; }
};
class Triangle2: public Polygon2, public Output {
  public:
    Triangle2 (int a, int b) : Polygon2(a,b) {}
    int area ()
      { return width*height/2; }
};  
 
// Example 4: one-to-many inheritance  
class Mother {
  public:
    Mother () { cout << "Mother: no parameters\n"; }
    Mother (int a) { cout << "Mother: int parameter\n"; }
};
class Daughter : public Mother { 
  public:
    Daughter (int a)        // will first call Mother's no-argument constructor 
	{ cout << "Daughter: int parameter\n\n"; }
};
class Son : public Mother {
  public:
    Son (int a) : Mother(a) // will first call Mother's parameter constructor 
	{ cout << "Son: int parameter\n\n"; }
};

int main () {
  // Example 1
  Rectangle rect;
  Square sqr (4);
  rect.convert(sqr);
  cout << rect.area() << '\n';
  
  // Example 2
  Rectangle1 rect1;
  Triangle trgl;
  rect1.set_values (4,5);
  trgl.set_values (4,5);
  cout << rect1.area() << '\n';
  cout << trgl.area() << '\n';
   
  // Example 3
  Rectangle2 rect2 (4,5);
  Triangle2 trgl2 (4,5);
  rect2.print (rect2.area());
  Triangle2::print (trgl2.area());
  
  // Example 4
  Daughter kelly(0);
  Son bud(0);  
  
  return 0;
}