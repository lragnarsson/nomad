//
// Created by Lage Ragnarsson on 26.09.21.
//

#ifndef NOMAD_ACTION_H
#define NOMAD_ACTION_H

#include "state.h"
#include "world_view.h"

#include <utility>
#include <vector>
#include <iostream>

namespace ai {
    class Action {
    public:

        Action(std::string name, std::vector<State> preConditions, std::vector<State> results)
                : _name{name}, _preConditions{std::move(preConditions)}, _results{std::move(results)} {};

        float canPerform(const WorldView &worldView);

        float computeCost() const { return 0.5f; }

        std::string getName() const { return _name; }

        friend std::ostream &operator<<(std::ostream &out, const Action &a);

    private:
        std::string _name;
        std::vector<State> _preConditions;
        std::vector<State> _results;
    };
}
#endif //NOMAD_ACTION_H
