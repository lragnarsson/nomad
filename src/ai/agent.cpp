//
// Created by Lage Ragnarsson on 26.09.21.
//

#include "agent.h"

namespace ai {

    void ai::Agent::addAction(const std::shared_ptr<Action> &action) {
        if (std::find(_actions.begin(), _actions.end(), action) == _actions.end()) {
            _actions.push_back(action);
        }
    }

    std::vector<std::shared_ptr<Action>> Agent::getPerformableActions() const {
        const float threshold = 0.5f;
        std::vector<std::shared_ptr<Action>> results;
        std::copy_if(_actions.begin(), _actions.end(), std::back_inserter(results),
                     [this, &threshold](const std::shared_ptr<Action> &a) {
                         return a->canPerform(_worldView) <= threshold;
                     });

        return results;
    }
}