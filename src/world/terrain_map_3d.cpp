//
// Created by Lage Ragnarsson on 11.09.21.
//

#include "terrain_map_3d.h"

#include <FastNoiseLite.h>


namespace world {
    glm::vec3 TerrainMap3D::interpBiLinear(const int x, const int z, const int xi, const int zi) const {
        int deltaX = 2 * xi - 1;
        int deltaZ = 2 * zi - 1;
        return 0.25f *
               (getAt(x, z) +
                getAt(x + deltaX, z) +
                getAt(x, z + deltaZ) +
                getAt(x + deltaX, z + deltaZ));
    }

    void TerrainMap3D::rescale(const glm::vec3 newMin, const glm::vec3 newMax) {
        const glm::vec3 scaleFactor = (newMax - newMin) / (max - min);
        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] = scaleFactor * data[i];
        }
    }

    void TerrainMap3D::AddNoise(const int x_offset, const int z_offset, FastNoiseLite noise, const glm::vec3 amplitude) {

        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            const float x = amplitude.x * noise.GetNoise((float) (x_offset + getTileX(i)),
                                                         (float) (z_offset + getTileZ(i)));
            const float y = amplitude.y * noise.GetNoise((float) (x_offset + getTileX(i)),
                                                         (float) (z_offset + getTileZ(i)));
            const float z = amplitude.z * noise.GetNoise((float) (x_offset + getTileX(i)),
                                                         (float) (z_offset + getTileZ(i)));
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

        for (int i = 0; i < TERRAIN_MAP_SIZE; i++) {
            data[i] = value;
        }
        min = value;
        max = value;
    }
}