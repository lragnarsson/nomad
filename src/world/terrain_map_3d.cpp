//
// Created by Lage Ragnarsson on 11.09.21.
//

#include "terrain_map_3d.h"

#include <FastNoiseLite.h>


namespace world {
    void TerrainMap3D::Rescale(const glm::vec3 newMin, const glm::vec3 newMax) {
        const glm::vec3 scaleFactor = (newMax - newMin) / (max - min);
        for (int i = 0; i < NUM_TILES; i++) {
            data[i] = scaleFactor * data[i];
        }
    }

    void TerrainMap3D::AddSimplexNoise(glm::vec3 frequencyFactor, glm::vec3 amplitudeFactor) {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetSeed(WORLD_SEED * 2);

        for (int i = 0; i < NUM_TILES; i++) {
            const float x = amplitudeFactor.x * noise.GetNoise((float) getChunkX(i) * frequencyFactor.x,
                                                               (float) getChunkZ(i) * frequencyFactor.x);
            const float y = amplitudeFactor.y * noise.GetNoise((float) getChunkX(i) * frequencyFactor.y,
                                                               (float) getChunkZ(i) * frequencyFactor.y);
            const float z = amplitudeFactor.z * noise.GetNoise((float) getChunkX(i) * frequencyFactor.z,
                                                               (float) getChunkZ(i) * frequencyFactor.z);
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
        for (int i = 0; i < NUM_TILES; i++) {
            data[i] = value;
        }
        min = value;
        max = value;
    }
}