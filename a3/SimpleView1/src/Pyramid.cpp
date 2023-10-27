#include "Pyramid.hpp"

Pyramid::Pyramid()
{
	// set set cordinate values for all vertices
    vertex[0][0] =  0.0; vertex[0][1] =  0.0; vertex[0][2] = 1.0; // Apex
    vertex[1][0] = -1.0; vertex[1][1] = -1.0; vertex[1][2] = 0.0; // Base vertex 1
    vertex[2][0] = -1.0; vertex[2][1] =  1.0; vertex[2][2] = 0.0; // Base vertex 2
    vertex[3][0] =  1.0; vertex[3][1] =  1.0; vertex[3][2] = 0.0; // Base vertex 3
    vertex[4][0] =  1.0; vertex[4][1] = -1.0; vertex[4][2] = 0.0; // Base vertex 4
    
    // other faces
    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 0;// Front face
    face[1][0] = 0; face[1][1] = 2; face[1][2] = 3; face[1][3] = 0;// Right face
    face[2][0] = 0; face[2][1] = 3; face[2][2] = 4; face[2][3] = 0;// Back face
    face[3][0] = 0; face[3][1] = 4; face[3][2] = 1; face[3][3] = 0;// Left face

    r = 1.0;
    g = 1.0;
    b = 0.0;
}

void Pyramid::drawFace(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);

    for(int j = 0; j < 4; j++){
        int ind = face[i][j];
        glVertex3f(vertex[ind][0], vertex[ind][1], vertex[ind][2]);
    }

    glEnd();
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 // set color
    glColor3f(r,g,b);
 // draw all faces
    for(int i = 0; i < 4; i++){
        drawFace(i);
    }

    glPopMatrix();
}

