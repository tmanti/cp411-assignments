#ifndef CHUNK_HPP_
#define CHUNK_HPP_

#include <GL/glut.h>
#include <windows.h>
#include "FastNoise.h"

#define CHUNKSIZE 16

class Chunk {
protected:
    GLfloat HeightMap[CHUNKSIZE+1][CHUNKSIZE+1];
public:
    GLint start_x, start_y;
    Chunk(int seed, GLint x, GLint y);
    GLfloat getHeight(GLint x, GLint y);
    GLfloat getHeightRel(GLint x_rel, GLint y_rel);
    int* getWorldPos();
private:
    fnl_state noise;
    void generateHeightMap();
};

#endif  /* CHUNK_HPP_ */