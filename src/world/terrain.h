//
// Created by Lage Ragnarsson on 06.09.21.
//

#ifndef NOMAD_TERRAIN_H
#define NOMAD_TERRAIN_H

#include "../genom/g_vertex.h"
#include "terrain_map.h"
#include "terrain_map_3d.h"
#include "world_constants.h"

namespace world {
    struct Tile {
        std::vector<genom::GVertex> vertices;
        std::vector<uint32_t> indices;

        Tile(const int x, const int y, const TerrainMap &terrainMap, const TerrainMap3D &colorMap);

    private:
        int x, z;
        float y;

        float InterpHeightBiLinear(int xi, int zi, const TerrainMap &heightMap) const;

        glm::vec3 CalculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) const;
    };

    class Terrain {
    public:
        std::vector<Tile> tiles;

        Terrain();


    private:
        void GenerateTerrainQuads(const TerrainMap &heightMap, const TerrainMap3D &colorMap);
    };
}
#endif //NOMAD_TERRAIN_H
