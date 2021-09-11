//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "terrain.h"
#include "terrain_map.h"

namespace world {
    /** Generate terrain in XZ plane from heightmap */
    Tile::Tile(const int x, const int z, const TerrainMap &heightMap, const TerrainMap3D &colorMap) :
            x{x}, z{z}, y{heightMap.getAt(x, z)} {
        vertices.reserve(TILE_VERTICES);
        indices.reserve(TILE_VERTICES);
        // 0---1      3
        // | /      / |
        // 2      5---4
        // Local quad coordinates of the two triangles:
        const int xi[TILE_INDICES] = {0, 1, 0, 1, 1, 0};
        const int zi[TILE_INDICES] = {0, 0, 1, 0, 1, 1};
        for (int i = 0; i < TILE_INDICES; i++) {
            vertices[i].position.x = TILE_SIZE * (static_cast<float>(x + xi[i])) - 0.5f * TILE_SIZE;
            vertices[i].position.z = TILE_SIZE * (static_cast<float>(z + zi[i])) - 0.5f * TILE_SIZE;
            vertices[i].position.y = InterpHeightBiLinear(xi[i], zi[i], heightMap);

            vertices[i].color = colorMap.getAt(x, z);
            //vertices[i].color = i < 3 ? glm::vec3{.6f, 0.f, 0.f} : glm::vec3{0.f, .6f, 0.f};

            indices[i] = i;
        }
        // Flat Shading Normals:
        const glm::vec3 n1 = CalculateNormal(vertices[0].position, vertices[1].position, vertices[2].position);
        vertices[0].normal = vertices[1].normal = vertices[2].normal = n1;
        const glm::vec3 n2 = CalculateNormal(vertices[4].position, vertices[5].position, vertices[3].position);
        vertices[3].normal = vertices[4].normal = vertices[5].normal = n2;
    }

    float Tile::InterpHeightBiLinear(const int xi, const int zi, const TerrainMap &heightMap) const {
        int deltaX = 2 * xi - 1;
        int deltaZ = 2 * zi - 1;
        return 0.25f *
               (heightMap.getAt(x, z) +
                heightMap.getAt(x + deltaX, z) +
                heightMap.getAt(x, z + deltaZ) +
                heightMap.getAt(x + deltaX, z + deltaZ));
    }

    glm::vec3 Tile::CalculateNormal(const glm::vec3 p0, const glm::vec3 p1, const glm::vec3 p2) const {
        const glm::vec3 u = glm::normalize(p2 - p0);
        const glm::vec3 v = glm::normalize(p1 - p0);
        return -glm::cross(u, v);
    }

    void Terrain::GenerateTerrainQuads(const TerrainMap &heightMap, const TerrainMap3D &colorMap) {
        int numQuads = CHUNK_WIDTH * CHUNK_HEIGHT;
        for (int i = 0; i < numQuads; i++) {
            int x = i % CHUNK_WIDTH;
            int z = i / CHUNK_WIDTH;
            tiles[i] = Tile(x, z, heightMap, colorMap);
        }
    }

    Terrain::Terrain() {
        tiles.reserve(NUM_TILES);

        world::TerrainMap heightMap{0.f};
        heightMap.AddSimplexNoise(0.5f, 8.f);
        heightMap.AddSimplexNoise(4.f, 1.f);
        heightMap.AddSimplexNoise(16.f, 0.1f);

        world::TerrainMap3D colorMap{glm::vec3(.2f, .4f, .2f)};
        colorMap.AddSimplexNoise(glm::vec3(3.f, 3.f, 3.f),
                                 glm::vec3(.1f, .1f, .1f));
        colorMap.Rescale(glm::vec3(0.3f, 0.6f, 0.3f), glm::vec3(0.6f, .9f, .6f));
        GenerateTerrainQuads(heightMap, colorMap);
    }

}