#include "World.hpp"

#include "Chunk.hpp"

#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>

World::World(int seed, int rend) : world_seed(seed), render_distance(rend) {
    initWorld();
    world_x = 0;
    world_y = 0;
}

std::vector<Chunk> World::getLoadedChunks() {
    return loaded_chunks;
}

void World::initWorld(){
    for(int i = -render_distance; i <= render_distance; i++){
        for(int j = -render_distance; j <= render_distance; j++){
            //std::cout << i << j << "\n";
            loaded_chunks.push_back(Chunk(world_seed, i*CHUNKSIZE, j*CHUNKSIZE));
        }
    } 
}

void World::LoadChunks(Direction dir){
    switch(dir){
        case North:
            world_y-=1;
            for(int i = -render_distance; i <= render_distance; i++){
                loaded_chunks.push_back(Chunk(world_seed, (world_x+i)*CHUNKSIZE, (world_y-render_distance)*CHUNKSIZE));
            }
            break;

        case South:
            world_y+=1;
            for(int i = -render_distance; i <= render_distance; i++){
                loaded_chunks.push_back(Chunk(world_seed, (world_x+i)*CHUNKSIZE, (world_y+render_distance)*CHUNKSIZE));
            }
            break;

        case East:
            world_x+=1;
            for(int i = -render_distance; i <= render_distance; i++){
                loaded_chunks.push_back(Chunk(world_seed, (world_x+render_distance)*CHUNKSIZE, (world_y+i)*CHUNKSIZE));
            }
            break;

        case West:
            world_x-=1;
            for(int i = -render_distance; i <= render_distance; i++){
                loaded_chunks.push_back(Chunk(world_seed, (world_x-render_distance)*CHUNKSIZE, (world_y+i)*CHUNKSIZE));
            }
            break;
    }
    UnloadChunks();
}

void World::UnloadChunks() {
    std::vector<int> bad_chunks;
    for (int i = 0; i < loaded_chunks.size(); i++){
        int* pos = loaded_chunks[i].getWorldPos();
        if(abs(world_x - pos[0]) > render_distance || abs(world_y - pos[1]) > render_distance){
            bad_chunks.push_back(i);
        }
        free(pos);
    }

    //std::cout << "unload | " << bad_chunks.size() << "\n";

    for (int i = 0; i < bad_chunks.size(); i++){
        loaded_chunks[bad_chunks[i]] = loaded_chunks.back();
        loaded_chunks.pop_back();
    }
}