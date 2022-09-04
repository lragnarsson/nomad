//
// Created by Lage Ragnarsson on 26.09.21.
//

#ifndef NOMAD_WORLD_VIEW_H
#define NOMAD_WORLD_VIEW_H

#include "belief.h"

#include <unordered_map>
#include <string>

namespace ai {
    class WorldView {
    public:
        const Belief &getBelief(const std::string &name) const { return _beliefs.at(name); }

        void updateBelief(const Belief &belief);

    private:
        std::unordered_map<std::string, Belief> _beliefs;
    };
}
#endif //NOMAD_WORLD_VIEW_H
