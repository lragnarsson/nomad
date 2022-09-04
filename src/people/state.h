//
// Created by Lage Ragnarsson on 20.09.21.
//

#ifndef NOMAD_ppl_STATE_H
#define NOMAD_ppl_STATE_H

#include <glm/glm.hpp>
#include <string>
#include <utility>
#include <chrono>
#include <variant>
#include "location.h"
#include "subject.h"

namespace people {

    /**
     * Read like:
     * _subject _verb _value with _uncertainty
     *
     * Agent foo HAS_A Object bar with 0.2 uncertainty
     *
     * */
    class State {
        using Value = std::variant<bool, int, float, Location, Subject>;

    public:
        State() = default;

        State(int id, Value value, float uncertainty) :
                _verb{id}, _value{value}, _uncertainty{uncertainty} {}

        [[nodiscard]] int getId() const { return _verb; }

        [[nodiscard]] Value getValue() const { return _value; }

        [[nodiscard]] float getCertainty() const { return _uncertainty; }

        [[nodiscard]] Subject *getSubject() const { return _subject; }

        void update(const State &state);

    protected:
        int _verb;
        Value _value;
        float _uncertainty;
        Subject *_subject;
    };
}
#endif //NOMAD_STATE_H
