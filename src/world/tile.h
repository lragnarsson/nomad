//
// Created by Lage Ragnarsson on 12.09.21.
//

#ifndef NOMAD_TILE_H
#define NOMAD_TILE_H

#include "../genom/g_vertex.h"
#include "terrain_map.h"
#include "terrain_map_3d.h"
#include "world_constants.h"


namespace world {
    struct Tile {
        const int x;
        const int z;
        const float y;
        const std::vector<genom::GVertex> vertices;
        const std::vector<uint32_t> indices;

        Tile(int x, int z, const TerrainMap &terrainMap, const TerrainMap3D &colorMap);

    private:
        static inline glm::vec3 CalculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

        static std::vector<genom::GVertex> GenerateGeometry(int x, int y,
                                                            const TerrainMap &terrainMap,
                                                            const TerrainMap3D &colorMap);
    };
}
#endif //NOMAD_TILE_H
