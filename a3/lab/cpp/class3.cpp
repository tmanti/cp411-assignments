/*
 * polymorphism, abstract of classes
 * compile: g++ -std=c++0x class3.cpp -o class3.exe
 * run: class3.exe
*/

#include <iostream>
using namespace std;

// Example 1: new method of the same name different derived classes
class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b) { width=a; height=b; }
};
class Rectangle: public Polygon {
  public:
    int area() { return width*height; }
};
class Triangle: public Polygon {
  public:
    int area() { return width*height/2; }
};


// Example 2: polymorphism
class Polygon1 {
  protected:
    int width, height;
  public:
    void set_values (int a, int b) { width=a; height=b; }
    virtual int area () { return 0; } // defined, can be redefined in derived classes
};
class Rectangle1: public Polygon1 {
  public:
    int area () { return width * height; } // redefined, then base method won't be called
};
class Triangle1: public Polygon1 {
  public:
    int area () { return (width * height / 2); } 
};

// Example 3: abstract class
class Polygon2 {
  protected:
    int width, height;
  public:
    void set_values (int a, int b) { width=a; height=b; }
    virtual int area (void) = 0; // not defined, need to be defined in derived classes
};
class Rectangle2: public Polygon2 {
  public:
    int area (void) { return (width * height); }  // defined
};
class Triangle2: public Polygon2 {
  public:
    int area (void) { return (width * height / 2); } // defined
};


int main () {
  // Example 1: test
  Rectangle rect;
  Triangle trgl;
  Polygon *ppoly1 = &rect;
  Polygon *ppoly2 = &trgl;
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  cout << rect.area() << '\n';  // area is not defined in Polygon
  cout << trgl.area() << '\n';
  
  // Example 2: test  
  Rectangle1 rect2;
  Triangle1 trgl2;
  Polygon1 poly;
  Polygon1 * ppoly4 = &rect2;
  Polygon1 * ppoly5 = &trgl2;
  Polygon1 * ppoly6 = &poly;
  ppoly4->set_values (4,5);
  ppoly5->set_values (4,5);
  ppoly6->set_values (4,5);
  cout << ppoly4->area() << '\n';  // area is not defined in Polygon1
  cout << ppoly5->area() << '\n';
  cout << ppoly6->area() << '\n';
  
  // Example 3: test
  Rectangle2 rect3;
  Triangle2 trgl3;
  Polygon2 * ppoly7 = &rect3;
  Polygon2 * ppoly8 = &trgl3;
  ppoly7->set_values (4,5);
  ppoly8->set_values (4,5);
  cout << ppoly7->area() << '\n';
  cout << ppoly8->area() << '\n';
  
  return 0;
}