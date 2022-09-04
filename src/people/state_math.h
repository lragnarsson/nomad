//
// Created by Lage Ragnarsson on 21.09.21.
//

#ifndef NOMAD_STATE_MATH_H
#define NOMAD_STATE_MATH_H

#include <algorithm>

namespace people {
    static constexpr float MAX_UNCERTAINTY = 1.f;
    static constexpr float MIN_UNCERTAINTY = 0.001f;

    static void fuseFloats(float x1, float x2, float p1, float p2,
                           float &x3, float &p3) {
        p3 = (p1 * p2) / (p1 + p2);
        x3 = p3 * (x1 / p1 + x2 / p2);
    }

    static float clampUncertainty(float c) { return std::min(MAX_UNCERTAINTY, std::max(MIN_UNCERTAINTY, c)); }
}
#endif //NOMAD_STATE_MATH_H
