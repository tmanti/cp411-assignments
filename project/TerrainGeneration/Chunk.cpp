#include "Chunk.hpp"
#include "FastNoise.h"
#include <iostream>

Chunk::Chunk(int seed, GLint x, GLint y) : start_x(x), start_y(y) {
    noise = fnlCreateState();
    noise.seed = seed;
    noise.noise_type = FNL_NOISE_PERLIN;

    generateHeightMap();
}

void Chunk::generateHeightMap() {
    //std::cout << "NOISE TEST" << (fnlGetNoise2D(&noise, start_x, start_y)+0.5)*20 << "|" << start_x << "|" << start_y << "\n";
    for (int i = 0; i <= CHUNKSIZE; ++i) {
        //std::cout << i << "\n";
        for (int j = 0; j <= CHUNKSIZE; ++j) {
            HeightMap[i][j] = fnlGetNoise2D(&noise, (start_x+i)*4, (start_y+j)*4)+0.4;
        }
    }
}

// Function to get the height at absolute coordinates (x, y)
GLfloat Chunk::getHeight(GLint x, GLint y) {
    return getHeightRel(x-start_x, y-start_y);
}

// Function to get the height at relative coordinates within the chunk
GLfloat Chunk::getHeightRel(GLint x_rel, GLint y_rel) {
    if (x_rel >= 0 && x_rel <= CHUNKSIZE && y_rel >= 0 && y_rel <= CHUNKSIZE) {
        return HeightMap[x_rel][y_rel];
    } else {
        //std::cout << x_rel << "|" << y_rel << "\n";
        return 0.0f;
    }
}

int* Chunk::getWorldPos(){
    int* pos = new int [2];
    pos[0] = start_x/CHUNKSIZE;
    pos[1] = start_y/CHUNKSIZE;
    return pos;
}