//
// Created by Lage Ragnarsson on 11.09.21.
//

#include "terrain_map_3d.h"

#include <FastNoiseLite.h>


namespace world {
    glm::vec3 TerrainMap3D::InterpBiLinear(const int x, const int z, const int xi, const int zi) const {
        int deltaX = 2 * xi - 1;
        int deltaZ = 2 * zi - 1;
        return 0.25f *
               (getAt(x, z) +
                getAt(x + deltaX, z) +
                getAt(x, z + deltaZ) +
                getAt(x + deltaX, z + deltaZ));
    }

    void TerrainMap3D::Rescale(const glm::vec3 newMin, const glm::vec3 newMax) {
        const glm::vec3 scaleFactor = (newMax - newMin) / (max - min);
        for (int i = 0; i < NUM_CHUNK_TILES; i++) {
            data[i] = scaleFactor * data[i];
        }
    }

    void
    TerrainMap3D::AddSimplexNoise(const glm::vec3 frequencyFactor, const glm::vec3 amplitudeFactor, const int seed) {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetSeed(WORLD_SEED * 2);

        for (int i = 0; i < NUM_CHUNK_TILES; i++) {
            const float x = amplitudeFactor.x * noise.GetNoise((float) getTileX(i) * frequencyFactor.x,
                                                               (float) getTileZ(i) * frequencyFactor.x);
            const float y = amplitudeFactor.y * noise.GetNoise((float) getTileX(i) * frequencyFactor.y,
                                                               (float) getTileZ(i) * frequencyFactor.y);
            const float z = amplitudeFactor.z * noise.GetNoise((float) getTileX(i) * frequencyFactor.z,
                                                               (float) getTileZ(i) * frequencyFactor.z);
            data[i] += glm::vec3(x, y, z);

            if (data[i].x > max.x) max.x = data[i].x;
            if (data[i].y > max.y) max.y = data[i].y;
            if (data[i].z > max.z) max.z = data[i].z;

            if (data[i].x < min.x) min.x = data[i].x;
            if (data[i].y < min.y) min.y = data[i].y;
            if (data[i].z < min.z) min.z = data[i].z;
        }
    }

    void TerrainMap3D::clear(glm::vec3 value) {
        for (int i = 0; i < NUM_CHUNK_TILES; i++) {
            data[i] = value;
        }
        min = value;
        max = value;
    }
}