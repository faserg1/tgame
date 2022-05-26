#pragma once

#include <cstdint>

namespace tgame
{
    struct Position
    {
        int16_t x;
        int16_t y;
    };

    constexpr bool operator==(const Position &a, const Position &b)
    {
        return a.x == b.x && a.y == b.y;
    }

    constexpr Position operator+(const Position &a, const Position &b)
    {
        return {(int16_t)  (a.x + b.x), (int16_t) (a.y + b.y)};
    }

    constexpr Position operator-(const Position &a, const Position &b)
    {
        return {(int16_t) (a.x - b.x), (int16_t) (a.y - b.y)};
    }
}