#include <iostream>
#include <SFML/Graphics.hpp>
#include "Turtle.h"
#include "L_system.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1800, 1800), "SFML shapes", sf::Style::Default, settings);
    sf::Clock clock;

    Turtle turtle = Turtle(sf::Vector2f(50, 400));

    L_system l_system = {turtle, "IIIF"};//"^X[B-F][+B-F][|B-F][-B-F]"};
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