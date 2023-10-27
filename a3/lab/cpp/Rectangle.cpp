/*
 * Rectangle method implementation
 * compile: g++ -c Rectangle.cpp
*/

#include "Rectangle.hpp"

void Rectangle::set_values(int x, int y) {
  width = x;
  height = y;
}

int Rectangle::area() {
  return width*height;
}
