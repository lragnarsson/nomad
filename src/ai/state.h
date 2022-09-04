//
// Created by Lage Ragnarsson on 26.09.21.
//

#ifndef NOMAD_STATE_H
#define NOMAD_STATE_H

#include <string>
#include <utility>
#include <iostream>


namespace ai {
    class State {
    public:
        State(std::string name, bool flag) : _name{std::move(name)}, _flag{flag} {}

        const std::string &getName() const { return _name; }

        bool getFlag() const { return _flag; }

        void setFlag(bool flag) { _flag = flag; }

        friend std::ostream &operator<<(std::ostream &out, const State &s);

    private :
        std::string _name;
        bool _flag;
    };
}
#endif //NOMAD_STATE_H
