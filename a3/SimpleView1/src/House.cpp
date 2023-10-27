#include "House.hpp"

House::House(){
    // set set cordinate values for all vertices
    vertex[0][0] = -1.0; vertex[0][1] = -1.0; vertex[0][2] = -1.0; // Vertex 0
    vertex[1][0] = -1.0; vertex[1][1] = -1.0; vertex[1][2] = 1.0; // Vertex 1 aaaaaa
    vertex[2][0] =  -1.0; vertex[2][1] =  1.0; vertex[2][2] = 1.0; // Vertex 2aaaaaa
    vertex[3][0] = -1.0; vertex[3][1] =  1.0; vertex[3][2] = -1.0; // Vertex 3
    vertex[4][0] = 1.0; vertex[4][1] = 1.0; vertex[4][2] =  -1.0; // Vertex 4
    vertex[5][0] =  1.0; vertex[5][1] = -1.0; vertex[5][2] =  -1.0; // Vertex 5
    vertex[6][0] =  1.0; vertex[6][1] =  -1.0; vertex[6][2] =  1.0; // Vertex 6aaaa
    vertex[7][0] = 1.0; vertex[7][1] =  1.0; vertex[7][2] =  1.0; // Vertex 7aaaaaaa
    vertex[8][0] = 0.0; vertex[8][1] = 0.0; vertex[8][2] = 2.0; // peak of house

    // Faces (using vertex indices)
    cube_face[0][0] = 0; cube_face[0][1] = 1; cube_face[0][2] = 2; cube_face[0][3] = 3; cube_face[0][4] = 0; // left face
    cube_face[1][0] = 0; cube_face[1][1] = 5; cube_face[1][2] = 4; cube_face[1][3] = 3; cube_face[1][4] = 0;// back face
    cube_face[2][0] = 5; cube_face[2][1] = 4; cube_face[2][2] = 7; cube_face[2][3] = 6; cube_face[2][4] = 5;// right face
    cube_face[3][0] = 1; cube_face[3][1] = 2; cube_face[3][2] = 7; cube_face[3][3] = 6; cube_face[3][4] = 1;// front face
    cube_face[4][0] = 2; cube_face[4][1] = 3; cube_face[4][2] = 4; cube_face[4][3] = 7; cube_face[4][4] = 2;// top face
    cube_face[5][0] = 0; cube_face[5][1] = 1; cube_face[5][2] = 6; cube_face[5][3] = 5; cube_face[5][4] = 0;// bottom face

    //pyramid faces
    pyr_face[0][0] = 8; pyr_face[0][1] = 1; pyr_face[0][2] = 2; pyr_face[0][3] = 8;// Front face
    pyr_face[1][0] = 8; pyr_face[1][1] = 2; pyr_face[1][2] = 7; pyr_face[1][3] = 8;// Right face
    pyr_face[2][0] = 8; pyr_face[2][1] = 7; pyr_face[2][2] = 6; pyr_face[2][3] = 8;// Back face
    pyr_face[3][0] = 8; pyr_face[3][1] = 6; pyr_face[3][2] = 1; pyr_face[3][3] = 8;// Left face

    //cubecolor
    cube_r = 1.0;
    cube_g = 0.0;
    cube_b = 0.0;
    //pyramiud color
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
    for(int i = 0; i < 4; i++){
        drawPyrFace(i);
    }

    glPopMatrix();
}

void House::drawCubeFace(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);

    for(int j = 0; j < 5; j++){
        int ind = cube_face[i][j];
        glVertex3f(vertex[ind][0], vertex[ind][1], vertex[ind][2]);
    }

    glEnd();
}

void House::drawPyrFace(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);

    for(int j = 0; j < 4; j++){
        int ind = pyr_face[i][j];
        glVertex3f(vertex[ind][0], vertex[ind][1], vertex[ind][2]);
    }

    glEnd();
}