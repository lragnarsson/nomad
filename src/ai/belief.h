//
// Created by Lage Ragnarsson on 26.09.21.
//

#ifndef NOMAD_BELIEF_H
#define NOMAD_BELIEF_H

#include <utility>

#include "state.h"

namespace ai {
    class Belief {
    public:
        Belief(State state, float uncertainty) : _state{std::move(state)}, _uncertainty{uncertainty} {}

        void update(const Belief &other);

        float getUncertainty() const { return _uncertainty; }

        const State &getState() const { return _state; }

        friend std::ostream &operator<<(std::ostream &out, const Belief &b);


    private:
        State _state;
        float _uncertainty;
    };
}

#endif //NOMAD_BELIEF_H
