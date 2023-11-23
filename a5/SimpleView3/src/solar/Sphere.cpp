#include "Sphere.hpp"

extern RenderMode renderMode;

Sphere::Sphere(GLdouble size) {
	radius = size;
	splices = 50;
	stacks = 50;
	textureID = 0;
	r=1;
	g=1;
	b=1;
	quad = gluNewQuadric();
}


void Sphere::setTextureID(GLuint id){
	textureID = id;
}

void Sphere::draw() {
	glPushMatrix();
	ctmMultiply();

	switch (renderMode) {
		case WIRE:
		case CONSTANT:
		case FLAT:
		case SMOOTH:
			glColor3f(r, g, b);
			glutSolidSphere(radius,splices,stacks);
			break;

		case TEXTURE:
			// your code
			{
			glPolygonMode(GL_BACK,GL_LINE);
			glPolygonMode(GL_FRONT,GL_FILL);
			glBindTexture(GL_TEXTURE_2D, textureID);
			
			GLfloat Pi = 3.1415926;
			GLfloat r = radius, a = 0, b = Pi, c=0, d = 2*Pi;
			GLfloat xs = (b-a)/stacks, ys=(d-c)/splices, theta, phi, x, y, z;
			for(int i=0; i<stacks; i++){//i stacks
				glBegin(GL_QUAD_STRIP);
				for(int j=0; j<=splices; j++){//j splices
					// compute the lower mesh point at (i, j)
					theta = a+i*xs;
					phi = c+j*ys;
					x = r * cos(theta) * cos(phi);
					y = r * cos(theta) * sin(phi);
					z = r * sin(theta);
					glTexCoord2f(theta /Pi, phi/(2*Pi));
					glVertex3f(x, y, z);

					// compute the upper mesh point at (i+1, j)
					theta = a+(i+1)*xs;
					phi = c+j*ys;
					x = r * cos(theta) * cos(phi);
					y = r * cos(theta) * sin(phi);
					z = r * sin(theta);
					glTexCoord2f(theta /Pi, phi/(2*Pi));
					glVertex3f(x, y, z);
				}
				glEnd();
			}
			}
			break;

		case PHONE:
			// your code
			break;
	}

	glPopMatrix();
}


