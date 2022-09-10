//
// Created by Lage Ragnarsson on 20.09.21.
//

#ifndef NOMAD_WORLD_STATE_H
#define NOMAD_WORLD_STATE_H

#include <unordered_map>
#include "state.h"

namespace people {
    class WorldState {
    public:
        WorldState() = default;

        void upsert(const State &state);

    private:
        std::unordered_map<int, State> states;
    };
}
#endif //NOMAD_WORLD_STATE_H
