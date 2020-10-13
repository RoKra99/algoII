#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "smallestEnclosingBall.h"
#include <iostream>

int main()
{
    size_t pCount = 30000;
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;
    sf::Clock clock;
    std::vector<sf::Vector2f> points = std::vector<sf::Vector2f>();
    sf::VertexArray vertexes = sf::VertexArray(sf::Points, pCount);
    float minX = MAXFLOAT;
    float maxX = 0;
    float minY = MAXFLOAT;
    float maxY = 0;
    for (int i = 0; i < pCount; ++i)
    {
        sf::Vector2f p = sf::Vector2f{rand() % static_cast<int>(width / 4) + static_cast<int>(width / 4), rand() % static_cast<int>(height / 4) + static_cast<int>(height / 4)};
        points.push_back(p);
        if (p.x > maxX)
            maxX = p.x;
        if (p.x < minX)
            minX = p.x;
        if (p.y > maxY)
            maxY = p.y;
        if (p.y < minY)
            minY = p.y;
        vertexes[i].position = p;
    }
    std::vector<sf::Vector2f> test = {{minX, minY}, {maxX, maxY}};
    seb::Ball testBall(test);
    seb::Ball ball;
    sf::Clock runtime;
    for (size_t i = 0; i < 10; ++i)
    {
        ball = seb::smallestEnclosingBall(points, ball);
        float time = runtime.getElapsedTime().asMilliseconds();
        runtime.restart();
        std::cout << time << std::endl;
    }

    sf::CircleShape ts(testBall.getRadius());
    ts.setOrigin(testBall.getRadius(), testBall.getRadius());
    ts.setPosition(testBall.getCenter());
    ts.setOutlineColor(sf::Color::Blue);
    ts.setOutlineThickness(1);
    ts.setFillColor(sf::Color::Transparent);

    sf::CircleShape shape(ball.getRadius());
    shape.setOrigin(ball.getRadius(), ball.getRadius());
    shape.setPosition(ball.getCenter());
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Transparent);

    sf::RenderWindow window(sf::VideoMode(width, height), "Hello World!");
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

        window.draw(ts);
        window.draw(shape);
        window.draw(vertexes);
        window.display();
        float time = clock.getElapsedTime().asSeconds();
        int fps = floor(1 / time);
        window.setTitle(std::to_string(fps));
        clock.restart();
    } // end isOpen

    return 0;
}