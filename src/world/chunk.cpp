//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "chunk.h"

#include <utility>
#include "terrain_map.h"

namespace world {
    Chunk::Chunk(const int x, const int z, std::shared_ptr<ChunkType> chunkType) :
            x{x}, z{z}, seed{ChunkSeed(x, z)}, chunkType_{std::move(chunkType)},
            heightMap{chunkType_->GenerateHeightMap(seed)},
            terrainColorMap{chunkType_->GenerateTerrainColor(seed)},
            tiles{chunkType_->GenerateTiles(heightMap, terrainColorMap)} {}

    int Chunk::ChunkSeed(const int x, const int z) {
        uint hash = (uint) x;
        hash ^= (uint) z << 16;
        hash ^= (uint) z >> 16;
        return hash ^ WORLD_SEED;
    }
}