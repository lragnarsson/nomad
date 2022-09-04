//
// Created by Lage Ragnarsson on 20.09.21.
//

#ifndef NOMAD_ppl_ACTION_H
#define NOMAD_ppl_ACTION_H

#include "world_state.h"

namespace people {
    class Action {
    public:
        const WorldState preConditions;
        const WorldState postState;
        const float cost;

        const void (*doer)(WorldState &state);

        //const void (*undoer)(State &state);

        Action(WorldState preConditions, WorldState postState, float cost, const void (*doer)(WorldState &state)) :
                preConditions{preConditions}, postState(postState), cost{cost}, doer{doer} {}

        bool canDo(const WorldState &state) const;

    private:

    };
}
#endif //NOMAD_ACTION_H
