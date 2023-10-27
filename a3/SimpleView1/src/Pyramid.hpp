/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */
#ifndef PYRAMID_H
#define PYRAMID_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];  /* 2D array to store cube vertices */
	GLint face[4][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color Pyramid */
public:
	Pyramid();
	void draw();
	void drawFace(int);
};

#endif
