/* 
 * main function to use Rectangle class 
 * compile: g++ Rectangle.cpp Rectangle_main.cpp -o Rectangle_main.exe 
 * run: Rectangle_main.exe 
*/
#include <iostream>
#include "Rectangle.hpp"
using namespace std;

int main () {
  Rectangle rect;
  rect.set_values(3,4);
  cout << "area:" << rect.area() << endl;
  return 0;
}


