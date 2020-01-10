//
// Created by Gentoo Huentoo on 2019-04-18.
//

#ifndef L_SYSTEM_TURTLE_H
#define L_SYSTEM_TURTLE_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <stack>
#include <functional>
#include <memory>

#define DEFAULT_LINE_COLOR sf::Color::Black

class Turtle {
private:
    std::vector <sf::Vertex> vertexVector = std::vector<sf::Vertex>();
    sf::VertexArray vertexArray = sf::VertexArray(sf::Lines);
    sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
    sf::Vector2f direction = sf::Vector2f(1.f, 0.f);

    float size = 15.f;
    std::stack <std::unique_ptr<Turtle>> states;
    sf::Color fillcolor = DEFAULT_LINE_COLOR;

public:
    Turtle() = default;

    void setFillcolor(const sf::Color &fillcolor);

    Turtle(const sf::VertexArray &vertexArray, const sf::Vector2f &pos, const sf::Vector2f &direction);

    Turtle(const Turtle &);

    Turtle(const sf::Vector2f &pos, const sf::Vector2f &direction);

    explicit Turtle(const sf::Vector2f &pos);

    Turtle(const sf::Vector2f &pos, float size_);

    void goWithoutDrawing();

    void goWithDrawing();

    void turnLeft();

    void turnRight();

    void turnDown();

    void turnUp();

    void rotateDirection(float);

    void flush(sf::RenderWindow &);

    void saveState();

    void previousState();

    void clear();

    void setSize(float size);

    float getSize() const;

    const sf::Color &getFillcolor() const;

    const sf::VertexArray &getVertexArray() const;

    const std::vector <sf::Vertex> &getVertexVector() const;

    void removeLast();
};


#endif //L_SYSTEM_TURTLE_H
