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

namespace world {
    class Chunk {
    public:
        const int x;
        const int z;

        const TerrainMap continentalness;
        const TerrainMap erosion;
        const TerrainMap peakyness;

        const TerrainMap heightMap;
        const TerrainMap3D terrainColorMap;
        const std::vector<Tile> tiles;

        Chunk(int x, int z);

        static int ChunkId(int x, int z);

    private:
        TerrainMap GenerateHeightMap() const;

        TerrainMap3D GenerateTerrainColor() const;

        TerrainMap GenerateContinentalness() const;

        TerrainMap GenerateErosion() const;

        TerrainMap GeneratePeakyness() const;

        std::vector<Tile> GenerateTiles() const;
    };
}
#endif //NOMAD_CHUNK_H
