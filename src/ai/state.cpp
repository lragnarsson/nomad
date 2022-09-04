//
// Created by Lage Ragnarsson on 26.09.21.
//

#include "state.h"

namespace ai {

    std::ostream &operator<<(std::ostream &out, const State &s) {
        out << "ai::State(" << s.getName() << "=" << s.getFlag() << ")";
        return out;
    }
}
