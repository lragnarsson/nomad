//
// Created by Lage Ragnarsson on 26.09.21.
//

#include "world_view.h"

namespace ai {

    void ai::WorldView::updateBelief(const Belief &belief) {
        std::string stateName = belief.getState().getName();
        if (_beliefs.contains(stateName)) {
            _beliefs.at(stateName).update(belief);
        } else {
            _beliefs.emplace(stateName, belief);
        }
    }
}