//
// Created by Lage Ragnarsson on 12.09.21.
//

#ifndef NOMAD_CHUNKTYPE_H
#define NOMAD_CHUNKTYPE_H

#include "terrain_map.h"
#include "terrain_map_3d.h"
#include "tile.h"

namespace world {
    class ChunkType {
    public:
        [[nodiscard]] std::vector<Tile> GenerateTiles(const TerrainMap &heightMap,
                                                      const TerrainMap3D &terrainColorMap) const;

        virtual TerrainMap GenerateHeightMap(int seed) const = 0;

        virtual TerrainMap3D GenerateTerrainColor(int seed) const = 0;
    };
}

#endif //NOMAD_CHUNKTYPE_H
