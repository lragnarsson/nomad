//
// Created by Lage Ragnarsson on 12.09.21.
//

#ifndef NOMAD_DESERT_CHUNK_TYPE_H
#define NOMAD_DESERT_CHUNK_TYPE_H

namespace world {
    class DesertChunkType : public ChunkType {
        [[nodiscard]] TerrainMap GenerateHeightMap(int seed) const override;

        [[nodiscard]] TerrainMap3D GenerateTerrainColor(int seed) const override;
    };
}
#endif //NOMAD_DESERT_CHUNK_TYPE_H