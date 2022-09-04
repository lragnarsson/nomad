//
// Created by Lage Ragnarsson on 26.09.21.
//

#include "belief.h"

void ai::Belief::update(const Belief &other) {
    if (other.getUncertainty() < _uncertainty) {
        _state.setFlag(other.getState().getFlag());
    }
}

std::ostream &ai::operator<<(std::ostream &out, const ai::Belief &b) {
    out << "ai::Belief(" << b.getState() << ", " << b.getUncertainty() << ")";
    return out;
}

