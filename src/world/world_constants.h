//
// Created by Lage Ragnarsson on 11.09.21.
//

#ifndef NOMAD_WORLD_CONSTANTS_H
#define NOMAD_WORLD_CONSTANTS_H

#include <algorithm>

namespace world {
    static constexpr int WORLD_SEED = 42;
    static constexpr int CHUNK_HEIGHT = 256;
    static constexpr int CHUNK_WIDTH = 256;
    static constexpr int NUM_CHUNK_TILES = CHUNK_HEIGHT * CHUNK_WIDTH;
    static constexpr int TILE_VERTICES = 6;
    static constexpr float TILE_SIZE = 1.f;

    static inline int getTileIndex(const int x, const int z) {
        const int clampedX = std::max(0, std::min(x, CHUNK_WIDTH - 1));
        const int clampedZ = std::max(0, std::min(z, CHUNK_HEIGHT - 1));
        return clampedX + CHUNK_WIDTH * clampedZ;
    }

    static inline int getTileX(int i) {
        return i % CHUNK_WIDTH;
    }

    static inline int getTileZ(int i) {
        return i / CHUNK_HEIGHT;
    }
}

#endif //NOMAD_WORLD_CONSTANTS_H

