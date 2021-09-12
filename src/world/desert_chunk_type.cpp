//
// Created by Lage Ragnarsson on 12.09.21.
//

#include "terrain_map.h"
#include "tile.h"
#include "chunk_type.h"
#include "desert_chunk_type.h"


namespace world {
    TerrainMap DesertChunkType::GenerateHeightMap(const int seed) const {
        world::TerrainMap heightMap{0.f};
        heightMap.AddSimplexNoise(.7f, 3.f, 3.5f, seed);
        heightMap.AddSimplexNoise(16.f, 32.f, 0.3f, seed);
        return heightMap;
    }

    TerrainMap3D DesertChunkType::GenerateTerrainColor(int seed) const {
        world::TerrainMap3D colorMap{glm::vec3(250.f / 256.f, 213.f / 256.f, 165.f / 256.f)};
        colorMap.AddSimplexNoise(glm::vec3(1.f, 1.f, 1.f),
                                 glm::vec3(.1f, .1f, .1f), seed);
        colorMap.AddSimplexNoise(glm::vec3(10.f, 10.f, 10.f),
                                 glm::vec3(.06f, .06f, .06f), seed);
        return colorMap;
    }
}