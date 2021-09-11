//
// Created by Lage Ragnarsson on 11.09.21.
//

#ifndef NOMAD_TERRAIN_MAP_H
#define NOMAD_TERRAIN_MAP_H

#include "world_constants.h"

#include <glm/glm.hpp>

#include <vector>

namespace world {
    //TODO: Generics???
    class TerrainMap {
    public:
        TerrainMap(const float value) {
            data.reserve(CHUNK_WIDTH * CHUNK_HEIGHT);
            clear(value);
        }

        float getAt(int x, int z) const { return data[getChunkIndex(x, z)]; }

        void setAt(const int x, const int z, float value) { data[getChunkIndex(x, z)] = value; }

        float getMax() const { return max; }

        float getMin() const { return min; }

        void clear(float value);

        void AddSimplexNoise(float frequencyFactor, float amplitudeFactor);

        void Rescale(float min, float max);

    private:
        std::vector<float> data;
        float max = 0.f;
        float min = 0.f;
    };
}
#endif //NOMAD_TERRAIN_MAP_H
