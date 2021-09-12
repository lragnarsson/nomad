//
// Created by Lage Ragnarsson on 12.09.21.
//

#include "terrain_map.h"
#include "tile.h"
#include "chunk_type.h"
#include "plains_chunk_type.h"


namespace world {
    TerrainMap PlainsChunkType::GenerateHeightMap(const int seed) const {
        world::TerrainMap heightMap{0.f};
        heightMap.AddSimplexNoise(0.3f, 0.3f, 16.f, seed);
        heightMap.AddSimplexNoise(2.f, 2.f, 1.f, seed);
        heightMap.AddSimplexNoise(6.f, 6.f, 0.1f, seed);
        heightMap.AddSimplexNoise(16.f, 16.f, 0.07f, seed);
        return heightMap;
    }

    TerrainMap3D PlainsChunkType::GenerateTerrainColor(int seed) const {
        world::TerrainMap3D colorMap{glm::vec3(.2f, .35f, .2f)};
        colorMap.AddSimplexNoise(glm::vec3(1.f, 1.f, 1.f),
                                 glm::vec3(.1f, .1f, .1f), seed);
        colorMap.AddSimplexNoise(glm::vec3(10.f, 10.f, 10.f),
                                 glm::vec3(.02f, .02f, .02f), seed);
        colorMap.Rescale(glm::vec3(0.2f, 0.4f, 0.2f), glm::vec3(0.4f, .65f, .4f));
        return colorMap;
    }
}