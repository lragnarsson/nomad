//
// Created by Lage Ragnarsson on 12.09.21.
//

#include "chunk_type.h"

namespace world {
    std::vector<Tile> ChunkType::GenerateTiles(const TerrainMap &heightMap,
                                               const TerrainMap3D &terrainColorMap) const {
        std::vector<Tile> tiles;
        tiles.reserve(NUM_CHUNK_TILES);

        for (int i = 0; i < NUM_CHUNK_TILES; i++) {
            int x = i % CHUNK_WIDTH;
            int z = i / CHUNK_WIDTH;
            tiles.emplace_back(x, z, heightMap, terrainColorMap);
        }
        return tiles;
    }
}