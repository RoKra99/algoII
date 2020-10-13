#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

namespace seb
{
    float euclid_dist(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }

    class Ball
    {
    private:
        std::vector<sf::Vector2f> points;
        sf::Vector2f center;
        float radius;

        void recalculateCenter2()
        {
            float sumX = 0.0, sumY = 0.0;
            int size = points.size();
            for (int i = 0; i < size; ++i)
            {
                sumX += points[i].x;
                sumY += points[i].y;
            }
            center.x = sumX / size;
            center.y = sumY / size;
            recalculateRadius();
        }

        void recalculateCenter()
        {
            if (points.size() <= 2)
            {
                recalculateCenter2();
            }
            else
            { // from geeks for geeks
                float x1, x2, x3, y1, y2, y3;
                x1 = points[0].x;
                x2 = points[1].x;
                x3 = points[2].x;
                y1 = points[0].y;
                y2 = points[1].y;
                y3 = points[2].y;

                float x12 = x1 - x2;
                float x13 = x1 - x3;

                float y12 = y1 - y2;
                float y13 = y1 - y3;

                float y31 = y3 - y1;
                float y21 = y2 - y1;

                float x31 = x3 - x1;
                float x21 = x2 - x1;

                // x1^2 - x3^2
                float sx13 = pow(x1, 2) - pow(x3, 2);

                // y1^2 - y3^2
                float sy13 = pow(y1, 2) - pow(y3, 2);

                float sx21 = pow(x2, 2) - pow(x1, 2);
                float sy21 = pow(y2, 2) - pow(y1, 2);

                float f = ((sx13) * (x12) + (sy13) * (x12) + (sx21) * (x13) + (sy21) * (x13)) / (2 * ((y31) * (x12) - (y21) * (x13)));
                float g = ((sx13) * (y12) + (sy13) * (y12) + (sx21) * (y13) + (sy21) * (y13)) / (2 * ((x31) * (y12) - (x21) * (y13)));

                float c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1;

                // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0
                // where centre is (h = -g, k = -f) and radius r
                // as r^2 = h^2 + k^2 - c
                float h = -g;
                float k = -f;
                float sqr_of_r = h * h + k * k - c;

                // r is the radius
                float r = sqrt(sqr_of_r);

                center.x = h;
                center.y = k;
                radius = r;
            }
        }

        void recalculateRadius()
        {
            radius = euclid_dist(center, points[0]);
        }

    public:
        Ball()
        {
            center = sf::Vector2f{0.0, 0.0};
            radius = 0.0;
        }

        Ball(const std::vector<sf::Vector2f> &points)
        {
            if (points.size() > 0 && points.size() <= 3)
            {
                this->points = points;
                recalculateCenter();
            }
        }

        sf::Vector2f getCenter() const
        {
            return center;
        }

        float getRadius() const
        {
            return radius;
        }

        void insert(const sf::Vector2f &point)
        {
            points.push_back(point);
            recalculateCenter();
            recalculateRadius();
        }

        bool checkInside(const sf::Vector2f &point)
        {
            if (points.size() > 1)
            {
                float distToCenter = euclid_dist(center, point);
                return distToCenter <= radius;
            }
            return false;
        }

        int pointCount() const
        {
            return points.size();
        }
    };

    // always picking the last element of points
    Ball smallestEnclosingBall(std::vector<sf::Vector2f> points, Ball q)
    {
        if (points.size() == 0 || q.pointCount() == 3)
        {
            return q;
        }
        sf::Vector2f x = points[points.size() - 1];
        points.pop_back();
        Ball b = smallestEnclosingBall(points, q);
        if (b.checkInside(x))
        {
            return b;
        }
        q.insert(x);
        return smallestEnclosingBall(points, q);
    }

} // namespace seb