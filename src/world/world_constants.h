//
// Created by Lage Ragnarsson on 11.09.21.
//

#ifndef NOMAD_WORLD_CONSTANTS_H
#define NOMAD_WORLD_CONSTANTS_H

#include <algorithm>
#include <iostream>


namespace world {
    static constexpr int WORLD_SEED = 42;
    static constexpr int CHUNK_LENGTH = 512;
    static constexpr int CHUNK_WIDTH = 512;
    static constexpr int NUM_CHUNK_TILES = CHUNK_LENGTH * CHUNK_WIDTH;
    static constexpr int TERRAIN_MAP_LENGTH = CHUNK_LENGTH + 2;
    static constexpr int TERRAIN_MAP_WIDTH = CHUNK_WIDTH + 2;
    static constexpr int TERRAIN_MAP_SIZE = TERRAIN_MAP_LENGTH * TERRAIN_MAP_WIDTH;

    static constexpr int TILE_VERTICES = 6;
    static constexpr float TILE_SIZE = 1.f;

    /*     3:  12 13 14 15
     *  1  2:  08 09 10 11
     *  0  1:  04 05 06 07
     *     0:  00 01 02 03
     *
     *         0  1  2  3
     *            0  1
     */
    static inline int getTileIndex(const int x, const int z) {
        //std::cout << "getTileIndex: " << x + 1 + TERRAIN_MAP_WIDTH * (z + 1) << std::endl;
        return x + 1 + TERRAIN_MAP_WIDTH * (z + 1);
    }

    static inline int getTileX(int i) {
        return i % TERRAIN_MAP_WIDTH;
    }

    static inline int getTileZ(int i) {
        return i / TERRAIN_MAP_WIDTH;
    }
}

#endif //NOMAD_WORLD_CONSTANTS_H

