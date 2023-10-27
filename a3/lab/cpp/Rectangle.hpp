/*
 * header file for class definition
*/
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle {
  int width, height;
  public:
    void set_values(int,int);
    int area();
};

#endif