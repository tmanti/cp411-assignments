/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */
#include "Pyramid.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include <stdio.h>

extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;

Pyramid::Pyramid()
{
    vertex[0][0] = -1;  vertex[0][1] = -1;  vertex[0][2] = 0;
    vertex[1][0] = 1;	vertex[1][1] = -1;  vertex[1][2] = 0;
    vertex[2][0] = 1;	vertex[2][1] =  1; 	vertex[2][2] = 0;
    vertex[3][0] = -1;	vertex[3][1] =  1;	vertex[3][2] = 0;
    vertex[4][0] = 0;	vertex[4][1] = 0.0;	vertex[4][2] = 1.5;

    face[0][0] = 0;	   face[0][1] = 1;	face[0][2] = 4;//back
    face[1][0] = 1;	   face[1][1] = 2;	face[1][2] = 4;//right
    face[2][0] = 2;	   face[2][1] = 3;	face[2][2] = 4;//front
    face[3][0] = 3;	   face[3][1] = 0;	face[3][2] = 4;//left

    faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0; faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0; faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0; faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;

    //face normal
    // Calculate face normals using Newell's Method
    for (int i = 0; i < 4; i++) {
        Vector* normal = new Vector(0, 0, 0);
        for (int j = 0; j < 3; j++) {
            int next = (j + 1) % 3;
            normal->x += (vertex[face[i][j]][1] - vertex[face[i][next]][1]) * (vertex[face[i][j]][2] + vertex[face[i][next]][2]);
            normal->y += (vertex[face[i][j]][2] - vertex[face[i][next]][2]) * (vertex[face[i][j]][0] + vertex[face[i][next]][0]);
            normal->z += (vertex[face[i][j]][0] - vertex[face[i][next]][0]) * (vertex[face[i][j]][1] + vertex[face[i][next]][1]);
        }
        normal->normalize();
        faceNormal[i][0] = normal->x;
        faceNormal[i][1] = normal->y;
        faceNormal[i][2] = normal->z;
    }

    //vertex color
    vertexColor[0][0] = 1.0, vertexColor[0][1] = 1.0; vertexColor[0][2] = 1.0;
	vertexColor[1][0] = 1.0, vertexColor[1][1] = 1.0; vertexColor[1][2] = 1.0;
	vertexColor[2][0] = 1.0, vertexColor[2][1] = 1.0; vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0, vertexColor[3][1] = 1.0; vertexColor[3][2] = 1.0;
	vertexColor[4][0] = 1.0, vertexColor[4][1] = 1.0; vertexColor[4][2] = 1.0;

    //vertex normal
    for (int i = 0; i < 8; i++) {
        vertexNormal[i][0] = 0.0;
        vertexNormal[i][1] = 0.0;
        vertexNormal[i][2] = 0.0;
        for (int j = 0; j < 6; j++) {
            if (face[j][0] == i || face[j][1] == i || face[j][2] == i || face[j][3] == i) {
                // Calculate the weighted contribution of the face normal
                vertexNormal[i][0] += faceNormal[j][0];
                vertexNormal[i][1] += faceNormal[j][1];
                vertexNormal[i][2] += faceNormal[j][2];
            }
        }
    }

    r = 1.0;
    g = 1.0;
    b = 0;
}

void Pyramid::drawFace(GLint i)
{
    GLfloat shade = 1;
    switch (renderMode) {
	case WIRE:
        glColor3f(r, g, b);
        glBegin(GL_LINE_LOOP);
        for (int j=0; j<3; j++) {
            glVertex3fv(vertex[face[i][j]]);
        }
        glEnd();
        break;
    case CONSTANT:
        if (myLight.on == true) shade = getFaceShade(i, myLight);
		glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
		glBegin(GL_POLYGON);
		for (int j=0; j<3; j++) {
			glVertex3fv(vertex[face[i][j]]);
		}
		glEnd();
		break;
        
    case FLAT:
			glShadeModel(GL_FLAT);
	case SMOOTH:
			glEnable(GL_NORMALIZE);
			glShadeModel(GL_SMOOTH);

		glColor3f(faceColor[i][0], faceColor[i][1], faceColor[i][2]);
		glBegin(GL_POLYGON);
		for (int j=0; j<4; j++) {
			glVertex3fv(vertex[face[i][j]]);
		}
		glEnd();
	    break;
    }
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);

	for (int i = 0; i < 4; i++) {
		if(cullMode == BACKFACE ) {
			if (isFrontface(i, myCamera)) {
				drawFace(i);
			}
		}
		else {
			drawFace(i);
		}
	}

    glPopMatrix();
}


bool Pyramid::isFrontface(int faceindex, Camera camera) {
// your implementation
    Point p0 = Point();
    Point p1 = Point();
    Point p2 = Point();

    p0.set(vertex[face[faceindex][0]][0], vertex[face[faceindex][0]][1], vertex[face[faceindex][0]][2]);
    p1.set(vertex[face[faceindex][1]][0], vertex[face[faceindex][1]][1], vertex[face[faceindex][1]][2]);
    p2.set(vertex[face[faceindex][2]][0], vertex[face[faceindex][2]][1], vertex[face[faceindex][2]][2]);

    Vector p01 = Vector();
    Vector p12 = Vector();

    p01.setDiff(p1, p0);
    p12.setDiff(p2, p1);

    Vector N = p01.cross(p12);

    Vector peyeref = Vector();
    peyeref.setDiff(camera.ref, camera.eye);

    GLfloat result = N.dot(peyeref);

    if(result < 0){
        return true;
    } else {
        return false;
    }
}

GLfloat Pyramid::getFaceShade(int faceindex, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;

	
	// assign v the first vertex of face[faceindex][0]
	for (int i = 0; i < 3; i++) {
        v[i] = vertex[face[faceindex][0]][i];
    }
	v[3] = 1.0;  // Homogeneous coordinate

	// compute the position of vertex face[faceindex][0] in WCS
	GLfloat vWCS[4];
	Matrix mc = getMC();
    for (int i = 0; i < 4; i++) {
        vWCS[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            vWCS[i] += mc.mat[i][j] * v[j];
        }
    }

	// compute the light vector s[] = lightposition - face[faceindex][0]
	for (int i = 0; i < 3; i++) {
        s[i] = light.getMC().mat[i][3] - vWCS[i];
    }

    // normalize vector s
	GLfloat sLength = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
    for (int i = 0; i < 3; i++) {
        s[i] /= sLength;
    }

    // compute the normal of  face[faceindex] in WCS
	 GLfloat faceNormalLength = sqrt(faceNormal[faceindex][0] * faceNormal[faceindex][0] +
                                    faceNormal[faceindex][1] * faceNormal[faceindex][1] +
                                    faceNormal[faceindex][2] * faceNormal[faceindex][2]);
	GLfloat faceNormalWCS[3];
    for (int i = 0; i < 3; i++) {
        faceNormalWCS[i] = faceNormal[faceindex][i]/faceNormalLength;
    }

	 // compute v dot s
	
	temp = v[0]*s[0]+v[1]*s[1]+v[2]*s[2];

	// compute shade factor
	shade = light.I*light.Rd*temp; 

	if (shade < 0.01) shade = 0.1;
	if (shade > 0.99 ) shade = 0.9;

	return shade;
}


GLfloat Pyramid::getVertexShade(int i, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;
// your implementation
	return shade;
}