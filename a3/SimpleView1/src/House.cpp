#include "House.hpp"

House::House(){
    // set set cordinate values for all vertices
    cube_vertex[0][0] = -1.0; cube_vertex[0][1] = -1.0; cube_vertex[0][2] = -1.0; // cube_vertex 0
    cube_vertex[1][0] =  1.0; cube_vertex[1][1] = -1.0; cube_vertex[1][2] = -1.0; // cube_vertex 1
    cube_vertex[2][0] =  1.0; cube_vertex[2][1] =  1.0; cube_vertex[2][2] = -1.0; // cube_vertex 2
    cube_vertex[3][0] = -1.0; cube_vertex[3][1] =  1.0; cube_vertex[3][2] = -1.0; // cube_vertex 3
    cube_vertex[4][0] = -1.0; cube_vertex[4][1] = -1.0; cube_vertex[4][2] =  1.0; // cube_vertex 4
    cube_vertex[5][0] =  1.0; cube_vertex[5][1] = -1.0; cube_vertex[5][2] =  1.0; // cube_vertex 5
    cube_vertex[6][0] =  1.0; cube_vertex[6][1] =  1.0; cube_vertex[6][2] =  1.0; // cube_vertex 6
    cube_vertex[7][0] = -1.0; cube_vertex[7][1] =  1.0; cube_vertex[7][2] =  1.0; // cube_vertex 7

    // cube_faces (using cube_vertex indices)
    cube_face[0][0] = 0; cube_face[0][1] = 1; cube_face[0][2] = 2; cube_face[0][3] = 3; // Bottom cube_face
    cube_face[1][0] = 4; cube_face[1][1] = 5; cube_face[1][2] = 6; cube_face[1][3] = 7; // Top cube_face
    cube_face[2][0] = 0; cube_face[2][1] = 1; cube_face[2][2] = 5; cube_face[2][3] = 4; // Front cube_face
    cube_face[3][0] = 1; cube_face[3][1] = 2; cube_face[3][2] = 6; cube_face[3][3] = 5; // Right cube_face
    cube_face[4][0] = 2; cube_face[4][1] = 3; cube_face[4][2] = 7; cube_face[4][3] = 6; // Back cube_face
    cube_face[5][0] = 3; cube_face[5][1] = 0; cube_face[5][2] = 4; cube_face[5][3] = 7; // Left cube_face

    //color
    cube_r = 1.0;
    cube_g = 0.0;
    cube_b = 0.0;

    // set set cordinate values for all vertices
    pyr_vertex[0][0] =  0.0; pyr_vertex[0][1] =  2.0; pyr_vertex[0][2] =  0.0; // Apex
    pyr_vertex[1][0] = -1.0; pyr_vertex[1][1] = 0.0; pyr_vertex[1][2] =  1.0; // Base pyr_vertex 1
    pyr_vertex[2][0] =  1.0; pyr_vertex[2][1] = 0.0; pyr_vertex[2][2] =  1.0; // Base pyr_vertex 2
    pyr_vertex[3][0] =  1.0; pyr_vertex[3][1] = 0.0; pyr_vertex[3][2] = -1.0; // Base pyr_vertex 3
    pyr_vertex[4][0] = -1.0; pyr_vertex[4][1] = 0.0; pyr_vertex[4][2] = -1.0; // Base pyr_vertex 4
    
    // other pyr_faces
    pyr_face[0][0] = 0; pyr_face[0][1] = 1; pyr_face[0][2] = 2; // Front pyr_face
    pyr_face[1][0] = 0; pyr_face[1][1] = 2; pyr_face[1][2] = 3; // Right pyr_face
    pyr_face[2][0] = 0; pyr_face[2][1] = 3; pyr_face[2][2] = 4; // Back pyr_face
    pyr_face[3][0] = 0; pyr_face[3][1] = 4; pyr_face[3][2] = 1; // Left pyr_face
    pyr_face[4][0] = 1; pyr_face[4][1] = 2; pyr_face[4][2] = 4; // Base triangle 1
    pyr_face[5][0] = 2; pyr_face[5][1] = 3; pyr_face[5][2] = 4; // Base triangle 2

    pyr_r = 1.0;
    pyr_g = 1.0;
    pyr_b = 0.0;
}

void House::draw(){
    glPushMatrix();
    this->ctmMultiply();
 // set color
    glColor3f(cube_r,cube_g,cube_b);
 // draw all faces
    for(int i = 0; i < 6; i++){
        drawCubeFace(i);
    }

    glColor3f(pyr_r, pyr_g, pyr_b);
     // draw all faces
    for(int i = 0; i < 6; i++){
        drawPyrFace(i);
    }

    glPopMatrix();
}

void House::drawCubeFace(int i)
{
// draw face i
    glBegin(GL_LINES);

    for(int j = 0; j < 4; j++){
        int ind = cube_face[i][j];
        glVertex3f(cube_vertex[ind][0], cube_vertex[ind][1], cube_vertex[ind][2]);
    }

    glEnd();
}

void House::drawPyrFace(int i)
{
// draw face i
    glBegin(GL_LINES);

    for(int j = 0; j < 3; j++){
        int ind = pyr_face[i][j];
        glVertex3f(pyr_vertex[ind][0], pyr_vertex[ind][1], pyr_vertex[ind][2]);
    }

    glEnd();
}