//
// Created by Lage Ragnarsson on 12.09.21.
//

#include "tile.h"

#include <vector>

namespace world {
    static constexpr int TILE_INDICES = 6;

    /** Generate terrain in XZ plane from heightmap */
    Tile::Tile(const int x, const int z, const TerrainMap &heightMap, const TerrainMap3D &colorMap) :
            x{x}, z{z}, y{heightMap.getAt(x, z)}, indices{{0, 1, 2, 3, 4, 5}},
            vertices{GenerateGeometry(x, z, heightMap, colorMap)} {}

    std::vector<genom::GVertex> Tile::GenerateGeometry(int x, int z,
                                                       const TerrainMap &heightMap,
                                                       const TerrainMap3D &colorMap) {
        std::vector<genom::GVertex> vertices(TILE_VERTICES);
        // 0---1      3
        // | /      / |
        // 2      5---4
        // Local quad coordinates of the two triangles:
        const int xi[TILE_INDICES] = {0, 1, 0, 1, 1, 0};
        const int zi[TILE_INDICES] = {0, 0, 1, 0, 1, 1};
        for (int i = 0; i < TILE_INDICES; i++) {
            vertices[i].position.x = TILE_SIZE * (static_cast<float>(x + xi[i])) - 0.5f * TILE_SIZE;
            vertices[i].position.z = TILE_SIZE * (static_cast<float>(z + zi[i])) - 0.5f * TILE_SIZE;
            vertices[i].position.y = heightMap.InterpBiLinear(x, z, xi[i], zi[i]);

            vertices[i].color = colorMap.InterpBiLinear(x, z, xi[i], zi[i]);
            //vertices[i].color = i < 3 ? glm::vec3{.6f, 0.1f, 0.1f} : glm::vec3{0.1f, .6f, 0.1f};
        }
        // Flat Shading Normals:
        const glm::vec3 n1 = CalculateNormal(vertices[0].position, vertices[1].position, vertices[2].position);
        vertices[0].normal = vertices[1].normal = vertices[2].normal = n1;
        const glm::vec3 n2 = CalculateNormal(vertices[4].position, vertices[5].position, vertices[3].position);
        vertices[3].normal = vertices[4].normal = vertices[5].normal = n2;
        return vertices;
    }

    glm::vec3 Tile::CalculateNormal(const glm::vec3 p0, const glm::vec3 p1, const glm::vec3 p2) {
        const glm::vec3 u = glm::normalize(p2 - p0);
        const glm::vec3 v = glm::normalize(p1 - p0);
        return glm::cross(v, u);
    }
}