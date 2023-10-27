#include "Cube.hpp"

Cube::Cube()
{
	// set set cordinate values for all vertices
    vertex[0][0] = -1.0; vertex[0][1] = -1.0; vertex[0][2] = -1.0; // Vertex 0
    vertex[1][0] = -1.0; vertex[1][1] = -1.0; vertex[1][2] = 1.0; // Vertex 1
    vertex[2][0] =  -1.0; vertex[2][1] =  1.0; vertex[2][2] = 1.0; // Vertex 2
    vertex[3][0] = -1.0; vertex[3][1] =  1.0; vertex[3][2] = -1.0; // Vertex 3
    vertex[4][0] = 1.0; vertex[4][1] = 1.0; vertex[4][2] =  -1.0; // Vertex 4
    vertex[5][0] =  1.0; vertex[5][1] = -1.0; vertex[5][2] =  -1.0; // Vertex 5
    vertex[6][0] =  1.0; vertex[6][1] =  -1.0; vertex[6][2] =  1.0; // Vertex 6
    vertex[7][0] = 1.0; vertex[7][1] =  1.0; vertex[7][2] =  1.0; // Vertex 7

    // Faces (using vertex indices)
    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3; face[0][4] = 0; // left face
    face[1][0] = 0; face[1][1] = 5; face[1][2] = 4; face[1][3] = 3; face[1][4] = 0;// back face
    face[2][0] = 5; face[2][1] = 4; face[2][2] = 7; face[2][3] = 6; face[2][4] = 5;// right face
    face[3][0] = 1; face[3][1] = 2; face[3][2] = 7; face[3][3] = 6; face[3][4] = 1;// front face
    face[4][0] = 2; face[4][1] = 3; face[4][2] = 4; face[4][3] = 7; face[4][4] = 2;// top face
    face[5][0] = 0; face[5][1] = 1; face[5][2] = 6; face[5][3] = 5; face[5][4] = 0;// bottom face

    
    // other faces
    r = 1.0;
    g = 0.0;
    b = 0.0;
}

void Cube::drawFace(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);

    for(int j = 0; j < 5; j++){
        int ind = face[i][j];
        glVertex3f(vertex[ind][0], vertex[ind][1], vertex[ind][2]);
    }

    glEnd();
}

void Cube::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 // set color
    glColor3f(r, g, b); // Set the color for the cube
 // draw all faces
    for(int i = 0; i < 6; i++){
        drawFace(i);
    }

    glPopMatrix();
}

