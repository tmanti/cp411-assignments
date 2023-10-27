#ifndef HOUSE_H
#define HOUSE_H

#include "Cube.hpp"
#include "Pyramid.hpp"
#include "Shape.hpp"

class House: public Shape{
protected:
	GLfloat cube_vertex[8][3];  /* 2D array to store cube vertices */
	GLint cube_face[6][4];      /* 2D array to store faces */
	GLfloat cube_r, cube_g, cube_b;       /* color House */

	GLfloat pyr_vertex[5][3];  /* 2D array to store cube vertices */
	GLint pyr_face[6][3];      /* 2D array to store faces */
	GLfloat pyr_r, pyr_g, pyr_b;       /* color Pyramid */
public:
	House();
	void draw();
	void drawPyrFace(int i);
	void drawCubeFace(int i);
};

#endif