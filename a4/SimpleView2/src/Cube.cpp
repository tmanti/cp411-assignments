/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */
#include "Cube.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include <stdio.h>

extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;

Cube::Cube() {
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 1;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 1;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 1;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;//back
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;//front
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;//left
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;//top
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;//right
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;//bottom

	// faceColor //red, green, blue, yellow, magenda, cyan
	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0; faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0; faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0; faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0; faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0; faceColor[5][1] = 1.0; faceColor[5][2] = 1.0;

	// set or compute face normals
	faceNormal[0][0] = 0.0, faceNormal[0][1] = 0.0, faceNormal[0][2] = -1.0,
	faceNormal[1][0] = 0.0; faceNormal[1][1] = 0.0; faceNormal[1][2] = 1.0;
	faceNormal[2][0] = -1.0; faceNormal[2][1] = 0.0; faceNormal[2][2] = 0.0;
	faceNormal[3][0] = 0.0; faceNormal[3][1] = 1.0; faceNormal[3][2] = 0.0;
	faceNormal[4][0] = 1.0; faceNormal[4][1] = 0.0; faceNormal[4][2] = 0.0;
	faceNormal[5][0] = 0.0; faceNormal[5][1] = -1.0; faceNormal[5][2] = 0.0;
	
	// vertex color
	vertexColor[0][0] = 1.0, vertexColor[0][1] = 1.0; vertexColor[0][2] = 1.0;
	vertexColor[1][0] = 1.0, vertexColor[1][1] = 1.0; vertexColor[1][2] = 1.0;
	vertexColor[2][0] = 1.0, vertexColor[2][1] = 1.0; vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0, vertexColor[3][1] = 1.0; vertexColor[3][2] = 1.0;
	vertexColor[4][0] = 1.0, vertexColor[4][1] = 1.0; vertexColor[4][2] = 1.0;
	vertexColor[5][0] = 1.0, vertexColor[5][1] = 1.0; vertexColor[5][2] = 1.0;
	vertexColor[6][0] = 1.0, vertexColor[6][1] = 1.0; vertexColor[6][2] = 1.0;
	vertexColor[7][0] = 1.0, vertexColor[7][1] = 1.0; vertexColor[7][2] = 1.0;
	
	// vertex normal 
	vertexNormal[0][0] = -1; vertexNormal[0][1] = -1; vertexNormal[0][2] = -1;
	vertexNormal[1][0] = -1; vertexNormal[1][1] = 1; vertexNormal[1][2] = -1;
	vertexNormal[2][0] = 1; vertexNormal[2][1] = 1; vertexNormal[2][2] = -1;
	vertexNormal[3][0] = 1; vertexNormal[3][1] = -1; vertexNormal[3][2] = -1;
	vertexNormal[4][0] = -1; vertexNormal[4][1] = -1; vertexNormal[4][2] = 1;
	vertexNormal[5][0] = -1; vertexNormal[5][1] = 1; vertexNormal[5][2] = 1;
	vertexNormal[6][0] = 1; vertexNormal[6][1] = 1; vertexNormal[6][2] = 1;
	vertexNormal[7][0] = 1; vertexNormal[7][1] = -1; vertexNormal[7][2] = 1;	

	r = 1.0;
	g = 0.0;
	b = 0.0;
}

void Cube::drawFace(int i) {
	GLfloat shade = 1;
	switch (renderMode) {
	case WIRE:
	   glColor3f(r, g, b);
	   glBegin(GL_LINE_LOOP);
	   for (int j=0; j<4; j++) {
		   glVertex3fv(vertex[face[i][j]]);
	   }
       glEnd();
	   break;
	case CONSTANT:
		if (myLight.on == true) shade = getFaceShade(i, myLight);
		glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
		glBegin(GL_POLYGON);
		for (int j=0; j<4; j++) {
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

void Cube::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);

	for (int i = 0; i < 6; i++) {
		if  (cullMode == BACKFACE ) {
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

bool Cube::isFrontface(int faceindex, Camera camera) {
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


GLfloat Cube::getFaceShade(int faceindex, Light light) {
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


GLfloat Cube::getVertexShade(int i, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;
// your implementation
	return shade;
}

