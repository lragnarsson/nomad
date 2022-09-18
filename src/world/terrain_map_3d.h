//
// Created by Lage Ragnarsson on 11.09.21.
//

#ifndef NOMAD_TERRAIN_MAP_3D_H
#define NOMAD_TERRAIN_MAP_3D_H

#include "world_constants.h"

#include <glm/glm.hpp>

#include <vector>

namespace world {
    class TerrainMap3D {
    public:
        TerrainMap3D(const glm::vec3 value) {
            data.reserve(TERRAIN_MAP_SIZE * 3);
            clear(value);
        }

        glm::vec3 getAt(int x, int z) const { return data[getTileIndex(x, z)]; }

        void setAt(const int x, const int z, glm::vec3 value) { data[getTileIndex(x, z)] = value; }

        glm::vec3 InterpBiLinear(int x, int z, int xi, int zi) const;

        glm::vec3 getMax() const { return max; }

        glm::vec3 getMin() const { return min; }

        void clear(glm::vec3 value);

        void Rescale(glm::vec3 min, glm::vec3 max);

        void AddSimplexNoise(int x_offset, int z_offset, glm::vec3 frequencyFactors, glm::vec3 amplitudeFactors);

    private:
        std::vector<glm::vec3> data;

        glm::vec3 min = glm::vec3{0.f, 0.f, 0.f};
        glm::vec3 max = glm::vec3{0.f, 0.f, 0.f};
    };
}

#endif //NOMAD_TERRAIN_MAP_3D_H