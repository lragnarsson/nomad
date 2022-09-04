//
// Created by Lage Ragnarsson on 20.09.21.
//


#include "world_state.h"

namespace people {

    void people::WorldState::upsert(const State &state) {
        if (states.contains(state.getId())) {
            states[state.getId()].update(state);
        } else {
            states[state.getId()] = state;
        }
    }
}