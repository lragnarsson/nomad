//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "chunk.h"

#include <utility>
#include "terrain_map.h"
#include "FastNoiseLite.h"

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
        //continentalness.AddNoise(x, z, .7f, 3.f, 3.5f);
        //continentalness.AddNoise(x, z, 16.f, 32.f, 0.3f);
        return continentalness;
    }

    TerrainMap Chunk::GenerateErosion() const {
        world::TerrainMap erosion{0.f};
        //erosion.AddNoise(x, z, .7f, 3.f, 3.5f);
        //erosion.AddNoise(x, z, 16.f, 32.f, 0.3f);
        return erosion;
    }

    TerrainMap Chunk::GeneratePeakyness() const {
        world::TerrainMap peakyness{0.f};
        //peakyness.AddNoise(x, z, .7f, 3.f, 3.5f);
        //peakyness.AddNoise(x, z, 16.f, 32.f, 0.3f);
        return peakyness;
    }


    TerrainMap Chunk::GenerateHeightMap() const {
        world::TerrainMap heightMap{0.f};

        FastNoiseLite noise1;
        noise1.SetSeed(WORLD_SEED);

        noise1.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise1.SetFrequency(0.0005);

        noise1.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise1.SetFractalOctaves(5);
        noise1.SetFractalGain(0.9f);

        heightMap.AddNoise(x, z, noise1, 34.f);

        FastNoiseLite noise2;
        noise2.SetSeed(WORLD_SEED);
        noise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise2.SetFrequency(0.01f);
        noise2.SetFractalOctaves(3);
        noise2.SetFractalType(FastNoiseLite::FractalType_Ridged);

        heightMap.AddNoise(x, z, noise2, 1.f);

        return heightMap;
    }

    TerrainMap3D Chunk::GenerateTerrainColor() const {
        world::TerrainMap3D colorMap{glm::vec3(50.f / 256.f, 75.f / 256.f, 30.f / 256.f)};

        FastNoiseLite noise;
        noise.SetSeed(WORLD_SEED);

        noise.SetNoiseType(FastNoiseLite::NoiseType_Value);
        noise.SetFrequency(1.f);
        colorMap.AddNoise(x, z, noise, glm::vec3(0.05f, 0.05f, 0.05f));

        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.01f);
        noise.SetFractalOctaves(3);
        noise.SetFractalType(FastNoiseLite::FractalType_Ridged);
        colorMap.AddNoise(x, z, noise, glm::vec3(0.075f, 0.075f, 0.075f));

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