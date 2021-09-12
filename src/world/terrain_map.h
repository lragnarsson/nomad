//
// Created by Lage Ragnarsson on 11.09.21.
//

#ifndef NOMAD_TERRAIN_MAP_H
#define NOMAD_TERRAIN_MAP_H

#include "world_constants.h"

#include <glm/glm.hpp>

#include <vector>

namespace world {
    class TerrainMap {
    public:
        TerrainMap(const float value) {
            data.reserve(CHUNK_WIDTH * CHUNK_HEIGHT);
            clear(value);
        }

        float getAt(int x, int z) const { return data[getTileIndex(x, z)]; }

        void setAt(const int x, const int z, float value) { data[getTileIndex(x, z)] = value; }

        float InterpBiLinear(int x, int z, int xi, int zi) const;

        float getMax() const { return max; }

        float getMin() const { return min; }

        void clear(float value);

        void AddSimplexNoise(float frequencyFactorX, float frequencyFactorY, float amplitudeFactor, int seed);

        void Rescale(float min, float max);

    private:
        std::vector<float> data;
        float max = 0.f;
        float min = 0.f;
    };
}
#endif //NOMAD_TERRAIN_MAP_H
