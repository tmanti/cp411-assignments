#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <GL/glut.h>
#include <windows.h>
#include <vector>

#include "Chunk.hpp"

enum Direction {
    North, South, West, East
};

class World {
protected:
    int world_seed;
    std::vector<Chunk> loaded_chunks;
public:
    int world_x, world_y;
    int render_distance;
    World(int seed, int rend);
    std::vector<Chunk> getLoadedChunks();
    void LoadChunks(Direction dir);
    
private:
    void initWorld();
    void UnloadChunks();
};

#endif  /* WORLD_HPP_ */