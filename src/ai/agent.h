//
// Created by Lage Ragnarsson on 26.09.21.
//

#ifndef NOMAD_AGENT_H
#define NOMAD_AGENT_H

#include "world_view.h"
#include "action.h"

#include <vector>

namespace ai {
    class Agent {
    public:

        void addAction(const std::shared_ptr<Action> &action);

        const WorldView &getWorldView() { return _worldView; }

        void updateWorldView(const Belief &belief) { _worldView.updateBelief(belief); }

        std::vector<std::shared_ptr<Action>> getPerformableActions() const;

    private:
        WorldView _worldView;
        std::vector<std::shared_ptr<Action>> _actions;
    };
}
#endif //NOMAD_AGENT_H
