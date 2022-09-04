//
// Created by Lage Ragnarsson on 04.09.21.
//

#include "ai_test_1.h"
#include "ai/belief.h"

#include <iostream>

namespace nomad {

    AiTest1::AiTest1() {
        agents.emplace_back(ai::Agent());
    }

    AiTest1::~AiTest1() {}

    void AiTest1::run() {
        ai::State HAS_FOOD{"has_food", true};
        ai::State IS_HUNGRY{"is_hungry", true};;
        ai::State IS_NOT_HUNGRY{"is_hungry", false};;

        auto ACT_EAT_FOOD = std::make_shared<ai::Action>(ai::Action{"eat_food",
                                                                    std::vector{HAS_FOOD, IS_HUNGRY},
                                                                    std::vector{IS_NOT_HUNGRY}});

        ai::Agent agent{};
        agent.addAction(ACT_EAT_FOOD);

        ai::Belief hasFood{HAS_FOOD, 0.1f};
        ai::Belief isHungry{IS_HUNGRY, 0.1f};
        agent.updateWorldView(hasFood);
        agent.updateWorldView(isHungry);

        //std::cout << hasFood;

        for (const auto &a: agent.getPerformableActions()) {
            std::cout << *a << std::endl;
        }

    }
}
