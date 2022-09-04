//
// Created by Lage Ragnarsson on 21.09.21.
//

#ifndef NOMAD_LOCATION_H
#define NOMAD_LOCATION_H

#include "state_math.h"

namespace people {
    class Location {
    public:
        int x;
        int z;

        void fuse(float &uncertainty, const Location &other, float otherUncertainty);
    };
}
#endif //NOMAD_LOCATION_H
