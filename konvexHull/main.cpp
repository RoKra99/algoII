#include "upperLower.h"
#include "grahamScan.h"
#include <iostream>
#include "stack.h"
#include <cassert>
#include "math.h"
#include <ctime>

using datastructures::Stack;

int main()
{
    srand((unsigned)time(0));

    size_t pCount = 10000;
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    sf::Clock clock;
    sf::VertexArray vertexes = sf::VertexArray(sf::Points, pCount);

    std::vector<sf::Vector2f> vec;
    for (std::size_t i = 0; i < pCount; ++i)
    {
        sf::Vector2f p = sf::Vector2f{static_cast<float>(rand() % static_cast<int>(0.9 * width) + 0.05 * width), static_cast<float>(rand() % static_cast<int>(0.9 * height) + 0.05 * height)};
        vec.push_back(p);
        vertexes[i].position = p;
    }

    sf::Clock timer;
    Stack<sf::Vector2f> grahamHull = graham::grahamScan<sf::Vector2f>(vec);
    std::cout << "Time for " << pCount << " points: " << timer.getElapsedTime().asMilliseconds() << std::endl;
    timer.restart();
    Stack<sf::Vector2f> hull = upperLower::upperLowerCH<sf::Vector2f>(vec);
    std::cout << "Time for " << pCount << " points: " << timer.getElapsedTime().asMilliseconds() << std::endl;

    std::size_t count = hull.size();
    sf::VertexArray lines = sf::VertexArray(sf::LineStrip, count);
    for (std::size_t i = 0; i < count; ++i)
    {
        lines[i].position = hull.pop();
        lines[i].color = sf::Color::Red;
    }

    std::size_t grahamCount = grahamHull.size();
    sf::VertexArray grahamLines = sf::VertexArray(sf::LineStrip, grahamCount);
    for (std::size_t i = 0; i < grahamCount; ++i)
    {
        grahamLines[i].position = grahamHull.pop();
        grahamLines[i].color = sf::Color::Blue;
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "");
    window.display();
    while (window.isOpen())
    {
        window.clear();

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                } // switch keycode
            }     //switch eventtype
        }         // end eventPoll

        window.draw(vertexes);    // points
        window.draw(lines);       // convex hull by upperLower
        window.draw(grahamLines); // convex hull by grahamScan
        window.display();

        float time = clock.getElapsedTime().asSeconds();
        int fps = floor(1 / time);
        window.setTitle(std::to_string(fps));
        clock.restart();

    } // end isOpen

    return 0;
}