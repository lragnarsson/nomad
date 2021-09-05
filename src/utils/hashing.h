//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_HASHING_H
#define NOMAD_HASHING_H

namespace utils {
    // from: https://stackoverflow.com/a/57595105
    template<typename T, typename... Rest>
    void hashCombine(std::size_t &seed, const T &v, const Rest &... rest) {
        seed ^= std::hash < T > {}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    };

}
#endif //NOMAD_HASHING_H
