//
// Created by Lage Ragnarsson on 11.09.21.
//

#include "terrain_map.h"

#include <FastNoiseLite.h>

#include <iostream>

namespace world {
    void TerrainMap::Rescale(const float newMin, const float newMax) {
        const float scaleFactor = (newMax - newMin) / (max - min);
        for (int i = 0; i < NUM_TILES; i++) {
            data[i] = scaleFactor * data[i];
        }
    }

    void TerrainMap::AddSimplexNoise(float frequencyFactor, float amplitudeFactor) {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetSeed(WORLD_SEED);

        for (int i = 0; i < NUM_TILES; i++) {
            data[i] += amplitudeFactor *
                       noise.GetNoise((float) getChunkX(i) * frequencyFactor, (float) getChunkZ(i) * frequencyFactor);
            if (data[i] > max) max = data[i];
            if (data[i] < min) min = data[i];
        }
        std::cout << "Height bounds: [" << min << ", " << max << "]" << std::endl;
    }

    void TerrainMap::clear(float value) {
        for (int i = 0; i < NUM_TILES; i++) {
            data[i] = value;
        }
        min = value;
        max = value;
    }
}