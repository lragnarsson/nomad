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

    void TerrainMap::AddNoise(const int x, const int z, FastNoiseLite noise, const float amplitude) {
        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] += amplitude *
                       noise.GetNoise((float) (x + getTileX(i)),
                                      (float) (z + getTileZ(i)));
            if (data[i] > max) max = data[i];
            if (data[i] < min) min = data[i];
        }
        //std::cout << "Height bounds: [" << min << ", " << max << "]" << std::endl;
    }

    void TerrainMap::clear(float value) {
        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] = value;
        }
        min = value;
        max = value;
    }
}