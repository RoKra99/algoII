#pragma once

#include "stack.h"
#include <vector>
#include <algorithm>
#include "upperLower.h"
#include <cmath>

using datastructures::Stack;

namespace graham
{

    template <typename T>
    bool vec2CompareY(const T &a, const T &b)
    {
        return a.y == b.y ? a.x < b.x : a.y < b.y;
    }


    // not quite right, since colinear points are not filtered out
    template <typename T>
    Stack<T> grahamScan(std::vector<T> &points)
    {
        const T p0 = *std::min_element(points.begin(), points.end(), vec2CompareY<T>);

        std::sort(points.begin(), points.end(),
                  [&p0](const T &a, const T &b) {
                      return atan2(a.y - p0.y, a.x - p0.x) < atan2(b.y - p0.y, b.x - p0.x);
                  });

        Stack<T> hull;
        std::size_t start = 0;
        if (points[0] == p0)
        {
            start = 3;
            hull.push(points[0]);
            hull.push(points[1]);
            hull.push(points[2]);
        }
        else
        {
            start = 2;
            hull.push(p0);
            hull.push(points[0]);
            hull.push(points[1]);
        }

        for (std::size_t i = start; i < points.size(); ++i)
        {
            if (points[i] == p0)
            {
                continue;
            }
            while (hull.size() > 1 && upperLower::ccw<T>(hull.preTop(), hull.getTop(), points[i]) <= 0)
            {
                hull.pop();
            }
            hull.push(points[i]);
        }
        hull.push(p0);
        return hull;
    }

} // namespace graham