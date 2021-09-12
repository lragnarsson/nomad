//
// Created by Lage Ragnarsson on 12.09.21.
//

#ifndef NOMAD_WORLD_H
#define NOMAD_WORLD_H

#include <memory>
#include "chunk_type.h"
#include "plains_chunk_type.h"
#include "desert_chunk_type.h"

#include "../genom/g_game_object.h"

namespace world {
    class World {
    public:
        void GetTerrainObjects(int x, int z, genom::GDevice &gDevice, std::vector<genom::GGameObject> &results);

    private:
        const std::shared_ptr<ChunkType> PLAINS_CHUNK = std::make_shared<world::PlainsChunkType>();
        const std::shared_ptr<ChunkType> DESERT_CHUNK = std::make_shared<world::DesertChunkType>();
    };
}
#endif //NOMAD_WORLD_H
