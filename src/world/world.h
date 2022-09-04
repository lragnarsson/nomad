//
// Created by Lage Ragnarsson on 12.09.21.
//

#ifndef NOMAD_WORLD_H
#define NOMAD_WORLD_H

#include <memory>

#include "../genom/g_game_object.h"

namespace world {
    class World {
    public:
        void GetTerrainObjects(int x, int z, genom::GDevice &gDevice, std::vector<genom::GGameObject> &results);

    private:
    };
}
#endif //NOMAD_WORLD_H
