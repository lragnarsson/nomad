//
// Created by Lage Ragnarsson on 20.09.21.
//

#include "state.h"
#include "state_math.h"

#include <iostream>

namespace people {

    void people::State::update(const State &newState) {
        if (_verb != newState._verb) {
            std::cerr << "Tried to update state of type " << _verb << " with " << newState._verb << std::endl;
            return;
        }

        // TODO: better way?
        if (std::holds_alternative<float>(_value) && std::holds_alternative<float>(newState.getValue())) {
            float fusedValue;
            float fusedCertainty;
            fuseFloats(std::get<float>(_value), std::get<float>(newState.getValue()), _uncertainty,
                       newState.getCertainty(), fusedValue, fusedCertainty);
            _value = fusedValue;
            _uncertainty = clampUncertainty(fusedCertainty);
        } else if (std::holds_alternative<int>(_value) && std::holds_alternative<int>(newState.getValue())) {
            float fusedValue;
            float fusedCertainty;
            float v1 = (float) std::get<int>(_value);
            float v2 = (float) std::get<int>(newState.getValue());
            fuseFloats(v1, v2, _uncertainty, newState.getCertainty(), fusedValue, fusedCertainty);
            _value = static_cast<int>(std::round(fusedValue));
            _uncertainty = clampUncertainty(fusedCertainty);
        } else if (std::holds_alternative<bool>(_value) && std::holds_alternative<bool>(newState.getValue())) {
            float fusedValue;
            float fusedCertainty;
            float v1 = std::get<bool>(_value) ? 1.f : 0.f;
            float v2 = std::get<bool>(newState.getValue()) ? 1.f : 0.f;
            fuseFloats(v1, v2, _uncertainty, newState.getCertainty(), fusedValue, fusedCertainty);
            _value = fusedValue >= 0.5f;
            _uncertainty = clampUncertainty(fusedCertainty);
        } else if (std::holds_alternative<Location>(_value) && std::holds_alternative<Location>(newState.getValue())) {
            std::get<Location>(_value).fuse(
                    _uncertainty, std::get<Location>(newState.getValue()), newState.getCertainty());
            _uncertainty = clampUncertainty(_uncertainty);
        } else if (std::holds_alternative<Subject>(_value) && std::holds_alternative<Subject>(newState.getValue())) {
            _value = newState.getValue();
            _uncertainty = newState.getCertainty();
        } else {
            std::cerr << "Failed to update state!" << std::endl;
            return;
        }
    }
}
