//
// Created by Lage Ragnarsson on 06.09.21.
//

#ifndef NOMAD_TERRAIN_H
#define NOMAD_TERRAIN_H

#include "../genom/g_vertex.h"

namespace world {
    static const int WORLD_SEED = 42;
    static const int MAP_HEIGHT = 128;
    static const int MAP_WIDTH = 128;
    static const int NUM_QUADS = MAP_HEIGHT * MAP_WIDTH;
    static const int QUAD_VERTICES = 6;
    static const int QUAD_INDICES = 6;
    static const float QUAD_SIZE = 1.f;

    struct TerrainMap {
        float data[MAP_HEIGHT][MAP_WIDTH] = {{0.f}};

        float getAt(int x, int z) const;

        void AddSimplexNoise(float frequencyFactor, float amplitudeFactor);
    };

    struct TerrainQuad {
        genom::GVertex vertices[QUAD_VERTICES] = {};
        uint32_t indices[QUAD_INDICES] = {};

        TerrainQuad() = default;

        TerrainQuad(int x, int y, const TerrainMap &terrainMap);

    private:
        int x, z;
        float y;

        float InterpHeightBiLinear(int xi, int zi, const TerrainMap &heightMap) const;

        glm::vec3
        CalculateNormal(glm::vec3 vertexPos, int xi, int zi, int nxi, int nzi, const TerrainMap &heightMap) const;
    };

    class Terrain {
    public:
        Terrain();

        TerrainQuad quads[NUM_QUADS];
    private:
        void GenerateTerrainQuads(const TerrainMap &heightMap);
    };


}
#endif //NOMAD_TERRAIN_H
