#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"
#include <math.h>

bool DEBUG = false;

Camera::Camera(){
	eye.set(5.0, 5.0, 10.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::reset(void) { // make default camera
	eye.set(5.0, 5.0, 10.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::setViewNorm() {
	GLfloat x, y, z, sr;
	x = ref.x-eye.x;
	y = ref.y-eye.y;
	z = ref.z-eye.z;
	sr = sqrt(x*x + y*y + z*z);
	x = x/sr;
	y = y/sr;
	z = z/sr;
	viewNorm.set(x, y, z);
}

void Camera::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){
// rotate eye position in WCS
	angle = angle * 3.1415926 / 180.0;

	GLfloat eyeToRef[3] = {ref.x - eye.x, ref.y - eye.y, ref.z - eye.z};

	Matrix rotMatrix;
	rotMatrix.rotateMatrix(rx, ry, rz, angle);

	rotMatrix.multiplyVector(eyeToRef);

	eye.set(ref.x-eyeToRef[0], ref.y-eyeToRef[1], ref.z-eyeToRef[2]);
}

void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
// translate eye position in WCS
	eye.set(eye.x + tx, eye.y + ty, eye.z + tz);

	ref.set(ref.x + tx, ref.y + ty, ref.z + tz);
}

void Camera::setProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, aspect, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x,viewup.y,viewup.z);
}

