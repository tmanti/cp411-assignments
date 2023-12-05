#include "World.hpp"

#include "Chunk.hpp"

#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>

World::World(int seed) : world_seed(seed) {
    initWorld();
    world_x = 0;
    world_y = 0;
}

std::vector<Chunk> World::getLoadedChunks() {
    return loaded_chunks;
}

void World::initWorld(){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            std::cout << i << j << "\n";
            loaded_chunks.push_back(Chunk(world_seed, i*CHUNKSIZE, j*CHUNKSIZE));
        }
    } 
}

void World::LoadChunks(Direction dir){
    switch(dir){
        case North:
            world_y-=1;
            loaded_chunks.push_back(Chunk(world_seed, (world_x-1)*CHUNKSIZE, (world_y-1)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x)*CHUNKSIZE, (world_y-1)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x+1)*CHUNKSIZE, (world_y-1)*CHUNKSIZE));
            break;

        case South:
            world_y+=1;
            loaded_chunks.push_back(Chunk(world_seed, (world_x-1)*CHUNKSIZE, (world_y+1)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x)*CHUNKSIZE, (world_y+1)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x+1)*CHUNKSIZE, (world_y+1)*CHUNKSIZE));
            break;

        case East:
            world_x+=1;
            loaded_chunks.push_back(Chunk(world_seed, (world_x+1)*CHUNKSIZE, (world_y-1)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x+1)*CHUNKSIZE, (world_y)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x+1)*CHUNKSIZE, (world_y+1)*CHUNKSIZE));
            break;

        case West:
            world_x-=1;
            loaded_chunks.push_back(Chunk(world_seed, (world_x-1)*CHUNKSIZE, (world_y-1)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x-1)*CHUNKSIZE, (world_y)*CHUNKSIZE));
            loaded_chunks.push_back(Chunk(world_seed, (world_x-1)*CHUNKSIZE, (world_y+1)*CHUNKSIZE));
            break;
    }
    UnloadChunks();
}

void World::UnloadChunks() {
    std::vector<int> bad_chunks;
    for (int i = 0; i < loaded_chunks.size(); i++){
        int* pos = loaded_chunks[i].getWorldPos();
        if(abs(world_x - pos[0]) >= 2 || abs(world_y - pos[1]) >= 2){
            bad_chunks.push_back(i);
        }
        free(pos);
    }

    for (int i = 0; i < bad_chunks.size(); i++){
        loaded_chunks[bad_chunks[i]] = loaded_chunks.back();
        loaded_chunks.pop_back();
    }
}