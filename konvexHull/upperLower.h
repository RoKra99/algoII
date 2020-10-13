#pragma once

#include "stack.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstring>
#include <iostream>

constexpr int UPPER = 0;
constexpr int LOWER = 1;

using datastructures::Stack;

namespace upperLower
{

    template <typename T>
    bool vec2fCompare(const T &a, const T &b)
    {
        if (a.x == b.x)
        {
            return a.y < b.y;
        }
        return a.x < b.x;
    }

    template <typename T>
    float ccw(const T &p0, const T &p1, const T &p2)
    {
        return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    }

    template <typename T>
    Stack<T> halfHull(const std::vector<T> &points, int part)
    {
        Stack<T> hull;
        int increment = 0;
        int begin = 0;

        if (part == LOWER)
        {
            hull.push(points[0]);
            hull.push(points[points.size() - 1]);
            hull.push(points[points.size() - 2]);
            begin = points.size() - 3;
            increment = -1;
        }
        else
        {
            hull.push(points[points.size() - 1]);
            hull.push(points[0]);
            hull.push(points[1]);
            begin = 2;
            increment = 1;
        }

        for (int i = begin; i >= 0 && i < points.size(); i += increment)
        {
            while (hull.size() > 1 && ccw<T>(hull.preTop(), hull.getTop(), points[i]) >= 0)
            {
                hull.pop();
            }
            hull.push(points[i]);
        }
        return hull;
    }

    template <typename T>
    Stack<T> upperLowerCH(std::vector<T> &points)
    {
        Stack<T> upper;
        Stack<T> lower;
        std::sort(points.begin(), points.end(), vec2fCompare<T>);

        upper = halfHull<T>(points, UPPER);
        lower = halfHull<T>(points, LOWER);

        upper.append(lower);
        return upper;
    }
} // namespace upperLower
