//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "chunk.h"

#include <utility>
#include "terrain_map.h"

namespace world {
    Chunk::Chunk(const int x, const int z) :
            x{x}, z{z},
            continentalness{GenerateContinentalness()},
            erosion{GenerateErosion()},
            peakyness{GeneratePeakyness()},
            heightMap{GenerateHeightMap()},
            terrainColorMap{GenerateTerrainColor()},
            tiles{GenerateTiles()} {

    }


    TerrainMap Chunk::GenerateContinentalness() const {
        world::TerrainMap continentalness{0.f};
        //continentalness.AddSimplexNoise(x, z, .7f, 3.f, 3.5f);
        //continentalness.AddSimplexNoise(x, z, 16.f, 32.f, 0.3f);
        return continentalness;
    }

    TerrainMap Chunk::GenerateErosion() const {
        world::TerrainMap erosion{0.f};
        //erosion.AddSimplexNoise(x, z, .7f, 3.f, 3.5f);
        //erosion.AddSimplexNoise(x, z, 16.f, 32.f, 0.3f);
        return erosion;
    }

    TerrainMap Chunk::GeneratePeakyness() const {
        world::TerrainMap peakyness{0.f};
        //peakyness.AddSimplexNoise(x, z, .7f, 3.f, 3.5f);
        //peakyness.AddSimplexNoise(x, z, 16.f, 32.f, 0.3f);
        return peakyness;
    }


    TerrainMap Chunk::GenerateHeightMap() const {
        world::TerrainMap heightMap{0.f};
        heightMap.AddSimplexNoise(x, z, .7f, 3.f, 3.5f);
        heightMap.AddSimplexNoise(x, z, 16.f, 32.f, 0.3f);
        return heightMap;
    }

    TerrainMap3D Chunk::GenerateTerrainColor() const {
        world::TerrainMap3D colorMap{glm::vec3(250.f / 256.f, 213.f / 256.f, 165.f / 256.f)};
        colorMap.AddSimplexNoise(x, z,
                                 glm::vec3(1.f, 1.f, 1.f),
                                 glm::vec3(.1f, .1f, .1f));
        colorMap.AddSimplexNoise(x, z,
                                 glm::vec3(10.f, 10.f, 10.f),
                                 glm::vec3(.06f, .06f, .06f));
        return colorMap;
    }

    std::vector<Tile> Chunk::GenerateTiles() const {
        std::vector<Tile> tiles;
        tiles.reserve(NUM_CHUNK_TILES);

        for (int i = 0; i < NUM_CHUNK_TILES; i++) {
            int xx = i % CHUNK_WIDTH;
            int zz = i / CHUNK_WIDTH;
            tiles.emplace_back(xx, zz, heightMap, terrainColorMap);
        }
        return tiles;
    }

    int Chunk::ChunkId(const int x, const int z) {
        uint hash = (uint) x;
        hash ^= (uint) z << 16;
        hash ^= (uint) z >> 16;
        return hash ^ WORLD_SEED;
    }
}