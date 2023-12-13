/*
 * Description: implementation of object.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "object.hpp"

NODE *new_node(SHAPE *object){
	NODE *n = (NODE *)malloc(sizeof(NODE));
	n->next = NULL;
	n->prev = NULL;

	n->object = object;

	return n;
}

void insert(LIST *list, SHAPE *object) {
	NODE *n = new_node(object);
	if(list->start == NULL){
		list->start = n;
		list->end = n;
	} else {
		n->next = list->start;
		list->start->prev = n;
		list->start = n;
	}
}

void deleteNode(LIST *list, NODE **selectp) {
	NODE *to_del = (*selectp);
	if(to_del->prev == NULL){
		list->start = to_del->next;
	} else {
		to_del->prev->next = to_del->next;
	}

	if(to_del->next == NULL){
		list->end = to_del->prev;
	} else {
		to_del->next->prev = to_del->prev;
	}
}

void clearList(LIST *list) {
	NODE *temp, *np = list->start;
	while (np != NULL) {
		temp = np;
		np = np->next;
		free(temp);
	}
	list->start = NULL;
	list->end = NULL;
}

void drawShape(SHAPE *object) {
	if (object->type == RECTANGLE) {  // rectangle
		// draw filled rectangle
		// draw outline
		glColor3f(object->fr, object->fg, object->fb);
		glBegin(GL_QUADS);            
			glVertex2i(object->x1, object->y1);
			glVertex2i(object->x1, object->y2);
			glVertex2i(object->x2, object->y2);
			glVertex2i(object->x2, object->y1);
		glEnd();

		glColor3f(object->sr, object->sg, object->sb);
		glBegin(GL_LINES);
			glVertex2i(object->x1, object->y1);
			glVertex2i(object->x1, object->y2);
			glVertex2i(object->x2, object->y2);
			glVertex2i(object->x2, object->y1);
		glEnd();

	} else if (object->type == CIRCLE) {  // circle
		circleMidpointFill(object->x1, object->y1, object->x2, object->y2, object->fr, object->fg, object->fb, object->swidth);
		circleMidpoint(object->x1, object->y1, object->x2, object->y2, object->sr, object->sg, object->sb, object->swidth);
	}
}

void drawShapeHighLight(SHAPE *object) {
	// draw outline with high light color
	if (object->type == RECTANGLE) {  // rectangle
		// draw filled rectangle
		// draw outline
		

	} else if (object->type == CIRCLE) {  // circle
		//GLint r = object->x2;
	}
}

void drawList(LIST *list) {
	NODE *p = list->start;
	while (p) {
		drawShape(p->object);
		p = p->next;
	}
}

void setPixel(GLint x, GLint y, GLint psize) {
	glPointSize(psize);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x, const GLint& y, GLint swidth) {
// ...
	setPixel(xc+x, yc+y, swidth);
	setPixel(xc+x, yc-y, swidth);
	setPixel(xc+y, yc+x, swidth);
	setPixel(xc+y, yc-x, swidth);
	setPixel(xc-x, yc+y, swidth);
	setPixel(xc-x, yc-y, swidth);
	setPixel(xc-y, yc+x, swidth);
	setPixel(xc-y, yc-x, swidth);
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat sr, GLfloat sg, GLfloat sb, GLint swidth) {
	GLint p = 1-x2;
	GLint x= 0, y=x2;

	glColor3f(sr, sg, sb);

	circlePlotPoints(x1, y1, x, y, swidth);

	while(x<y){
		x++;
		if(p<0) p+=2*x+1;
		else {
			y--;
			p+=2*(x-y)+1;
		}
		circlePlotPoints(x1, y1, x, y, swidth);
	}
}

void circlePlotPointsFill(GLint xc, GLint yc, GLint x, GLint y, GLint swidth) {
	glLineWidth(swidth);
	glBegin(GL_LINES);
		glVertex2i(xc+x, yc+y);
		glVertex2i(xc+x, yc-y);
		glVertex2i(xc+y, yc+x);
		glVertex2i(xc+y, yc-x);
		glVertex2i(xc-x, yc+y);
		glVertex2i(xc-x, yc-y);
		glVertex2i(xc-y, yc+x);
		glVertex2i(xc-y, yc-x);
	glEnd();
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat fr, GLfloat fg, GLfloat fb, GLint strokew) {
	GLint p = 1-x2;
	GLint x= 0, y=x2;
	glColor3f(fr, fg, fb);
	circlePlotPointsFill(x1, y1, x, y, strokew);
	while(x<y){
		x++;
		if(p<0)p+=2*x+1;
		else {
			y--;
			p+=2*(x-y)+1;
		}
		circlePlotPointsFill(x1, y1, x, y, strokew);
	}
}
