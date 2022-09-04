//
// Created by Lage Ragnarsson on 11.09.21.
//

#include "terrain_map.h"

#include <FastNoiseLite.h>

#include <iostream>

namespace world {
    float TerrainMap::InterpBiLinear(const int x, const int z, const int xi, const int zi) const {
        int deltaX = 2 * xi - 1;
        int deltaZ = 2 * zi - 1;
        return 0.25f *
               (getAt(x, z) +
                getAt(x + deltaX, z) +
                getAt(x, z + deltaZ) +
                getAt(x + deltaX, z + deltaZ));
    }

    void TerrainMap::Rescale(const float newMin, const float newMax) {
        const float scaleFactor = (newMax - newMin) / (max - min);
        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] = scaleFactor * data[i];
        }
    }

    void
    TerrainMap::AddSimplexNoise(const int x, const int z, const float frequencyFactorX, const float frequencyFactorY,
                                const float amplitudeFactor) {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetSeed(WORLD_SEED);

        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] += amplitudeFactor *
                       noise.GetNoise((float) (x + getTileX(i)) * frequencyFactorX,
                                      (float) (z + getTileZ(i)) * frequencyFactorY);
            if (data[i] > max) max = data[i];
            if (data[i] < min) min = data[i];
        }
        std::cout << "Height bounds: [" << min << ", " << max << "]" << std::endl;
    }

    void TerrainMap::clear(float value) {
        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] = value;
        }
        min = value;
        max = value;
    }
}