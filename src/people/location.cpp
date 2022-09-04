//
// Created by Lage Ragnarsson on 21.09.21.
//

#include "location.h"

#include <cmath>

namespace people {

    void Location::fuse(float &uncertainty, const Location &other, const float otherUncertainty) {
        float fusedValue;
        float fusedUncertainty;
        float x1 = static_cast<float> (x);
        float x2 = static_cast<float> (other.x);

        fuseFloats(x1, x2, uncertainty, otherUncertainty, fusedValue, fusedUncertainty);
        x = static_cast<int>(std::round(fusedValue));

        x1 = static_cast<float> (z);
        x2 = static_cast<float> (other.z);
        fuseFloats(x1, x2, uncertainty, otherUncertainty, fusedValue, fusedUncertainty);
        z = static_cast<int>(std::round(fusedValue));
        uncertainty = fusedUncertainty;
    }
}