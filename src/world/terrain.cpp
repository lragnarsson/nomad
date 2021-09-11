//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "terrain.h"

#include <FastNoiseLite.h>

#include <iostream>

namespace world {

    void TerrainMap::AddSimplexNoise(float frequencyFactor, float amplitudeFactor) {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetSeed(WORLD_SEED);

        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                data[i][j] -= amplitudeFactor * noise.GetNoise(i * frequencyFactor, j * frequencyFactor);
            }
        }
    }

    float TerrainMap::getAt(const int x, const int z) const {
        int clampedX = std::max(0, std::min(x, MAP_WIDTH - 1));
        int clampedZ = std::max(0, std::min(z, MAP_HEIGHT - 1));
        return data[clampedX][clampedZ];
    }

    /** Generate terrain in XZ plane from heightmap */
    TerrainQuad::TerrainQuad(const int x, const int z, const TerrainMap &heightMap) : x{x}, z{z},
                                                                                      y{heightMap.getAt(x, z)} {
        // 0---1      3
        // | /      / |
        // 2      5---4
        // Local quad coordinates of the two triangles:
        const int xi[QUAD_INDICES] = {0, 1, 0, 1, 1, 0};
        const int zi[QUAD_INDICES] = {0, 0, 1, 0, 1, 1};
        // Local coordinates of points to use for normal vector calculation:
        const int nxi[QUAD_INDICES] = {0, 1, -1, 1, 0, -1};
        const int nzi[QUAD_INDICES] = {-1, 0, 0, 0, 1, 0};

        for (int i = 0; i < QUAD_INDICES; i++) {
            vertices[i].position.x = QUAD_SIZE * (static_cast<float>(x + xi[i])) - 0.5f * QUAD_SIZE;
            vertices[i].position.z = QUAD_SIZE * (static_cast<float>(z + zi[i])) - 0.5f * QUAD_SIZE;
            vertices[i].position.y = InterpHeightBiLinear(xi[i], zi[i], heightMap);

            vertices[i].normal = CalculateNormal(vertices[i].position, xi[i], zi[i], nxi[i], nzi[i], heightMap);
            //vertices[i].color = i < 3 ? glm::vec3{.6f, 0.f, 0.f} : glm::vec3{0.f, .6f, 0.f};
            vertices[i].color = glm::vec3{0.7f, 0.7f, 0.6f};

            indices[i] = i;
        }
    }

    float TerrainQuad::InterpHeightBiLinear(const int xi, const int zi, const TerrainMap &heightMap) const {
        int deltaX = 2 * xi - 1;
        int deltaZ = 2 * zi - 1;
        return 0.25f *
               (heightMap.getAt(x, z) +
                heightMap.getAt(x + deltaX, z) +
                heightMap.getAt(x, z + deltaZ) +
                heightMap.getAt(x + deltaX, z + deltaZ));
    }

    glm::vec3
    TerrainQuad::CalculateNormal(const glm::vec3 vertexPos, const int xi, const int zi, const int nxi, const int nzi,
                                 const TerrainMap &heightMap) const {
        const float deltaX = (2.f * static_cast<float>(xi) - 1.f) / QUAD_SIZE;
        const float deltaZ = (2.f * static_cast<float>(zi) - 1.f) / QUAD_SIZE;

        const glm::vec3 u = glm::normalize(glm::vec3{x, y, z} - vertexPos);
        const glm::vec3 v = glm::normalize(
                glm::vec3{x, y, z} - glm::vec3{x + nxi, heightMap.getAt(x + nxi, z + nzi), z + nzi});
        return glm::cross(u, v);
    }

    void Terrain::GenerateTerrainQuads(const TerrainMap &heightMap) {
        int numQuads = MAP_WIDTH * MAP_HEIGHT;

        for (int i = 0; i < numQuads; i++) {
            int x = i % MAP_WIDTH;
            int z = i / MAP_WIDTH;
            quads[i] = TerrainQuad(x, z, heightMap);
        }
    }

    Terrain::Terrain() {
        world::TerrainMap heightMap;
        heightMap.AddSimplexNoise(2.f, 2.f);
        heightMap.AddSimplexNoise(6.f, 0.8f);
        heightMap.AddSimplexNoise(16.f, 0.2f);
        GenerateTerrainQuads(heightMap);
    }
}