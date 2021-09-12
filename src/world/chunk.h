//
// Created by Lage Ragnarsson on 06.09.21.
//

#ifndef NOMAD_CHUNK_H
#define NOMAD_CHUNK_H

#include "../genom/g_vertex.h"
#include "terrain_map.h"
#include "terrain_map_3d.h"
#include "world_constants.h"
#include "tile.h"
#include "chunk_type.h"

namespace world {
    class Chunk {
    public:
        const int x;
        const int z;
        const int seed;

        const std::shared_ptr<ChunkType> chunkType_;

        const TerrainMap heightMap;
        const TerrainMap3D terrainColorMap;
        const std::vector<Tile> tiles;

        Chunk(int x, int z, std::shared_ptr<ChunkType> chunkType);

        static int ChunkSeed(int x, int z);
    };
}
#endif //NOMAD_CHUNK_H
