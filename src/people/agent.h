//
// Created by Lage Ragnarsson on 21.09.21.
//

#ifndef NOMAD_AGasdENT_H
#define NOMAD_AGasdENT_H

#include "subject.h"
#include "action.h"

#include <vector>
#include <algorithm>

namespace people {
    class Agent : public Subject {
    public:
        Agent() = default;

        void upsertBeliefs(const State &state) { _beliefs.upsert(state); }

        void addAction(const Action *action) { _actions.push_back(action); }

        void removeAction(const Action *action) {
            _actions.erase(std::remove(_actions.begin(), _actions.end(), action), _actions.end());
        }

    private:
        WorldState _beliefs;
        std::vector<const Action *> _actions;
    };
}
#endif //NOMAD_AGENT_H
