//
// Created by Lage Ragnarsson on 26.09.21.
//

#include "action.h"

#include <algorithm>

namespace ai {

    float ai::Action::canPerform(const WorldView &worldView) {
        float uncertainty = 0.f;
        for (const auto &state: _preConditions) {
            const auto &belief = worldView.getBelief(state.getName());
            if (state.getFlag() == belief.getState().getFlag()) {
                uncertainty = std::max(uncertainty, belief.getUncertainty());
            } else {
                uncertainty = std::max(uncertainty, 1.f - belief.getUncertainty());
            }
        }
        return uncertainty;
    }

    std::ostream &operator<<(std::ostream &out, const Action &a) {
        out << "ai::Action(" << a.getName() << ")";
        return out;
    }
}