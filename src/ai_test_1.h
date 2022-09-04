//
// Created by Lage Ragnarsson on 04.09.21.
//

#ifndef NOMAD_AI_TEST_1_H
#define NOMAD_AI_TEST_1_H

#include "ai/agent.h"
#include <vector>


namespace nomad {
    class AiTest1 {
    public:

        AiTest1();

        ~AiTest1();

        AiTest1(const AiTest1 &) = delete;

        AiTest1 &operator=(const AiTest1 &) = delete;

        void run();

    private:
        std::vector<ai::Agent> agents;
    };
}

#endif //NOMAD_AI_TEST_1_H
