//
// Created by joonasvalamaki on 2/3/23.
//

#ifndef RT_COLOR_HPP
#define RT_COLOR_HPP

#include <stdint.h>

namespace rt {
    class Color {

    public:
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
    };
}

#endif //RT_COLOR_HPP
