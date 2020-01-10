#include <iostream>
#include <SFML/Graphics.hpp>
#include "Turtle.h"
#include "Mode.h"
#include "L_system.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1800, 1800), "SFML shapes", sf::Style::Default, settings);
    sf::Clock clock;

    Turtle turtle = Turtle(
#ifdef SIERPINSKI_TRIANGLE
            sf::Vector2f(window.getSize().x / 2 + 600, window.getSize().y - 100), 15.f
#elif defined(TREE_1)
            sf::Vector2f(window.getSize().x / 2, window.getSize().y - 100), 5.f
#elif defined(TREE_2)
            sf::Vector2f(window.getSize().x / 2, window.getSize().y - 100), 10.f
#endif
);

    L_system l_system = {turtle,
#ifdef SIERPINSKI_TRIANGLE
                         "++F" //sierpinski triangle setup
#elif defined(TREE_1)
                         "-F" // tree 1 setup
#elif defined(TREE_2)
                         "-F"
#endif
    };
    l_system.update();
    l_system.update();
    l_system.update();
    l_system.update();
    l_system.draw();
    window.clear(sf::Color::White);

    sf::Event event{};

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...
        window.draw(l_system.getTurtle().getVertexVector().data(), l_system.getTurtle().getVertexVector().size(),
                    sf::Lines);

        // end the current frame
        window.display();

        sf::Time begintime = clock.getElapsedTime();
        sf::Time time = begintime;

        while (time.asMilliseconds() - begintime.asMilliseconds() < 50) {
            time = clock.getElapsedTime();
        }
    }

    return 0;
}