#include <memory>

//
// Created by Gentoo Huentoo on 2019-04-18.
//

#include "Turtle.h"

Turtle::Turtle(const sf::VertexArray &vertexArray, const sf::Vector2f &pos, const sf::Vector2f &direction)
        : vertexArray(vertexArray), pos(pos), direction(direction) {}

Turtle::Turtle(const sf::Vector2f &pos, const sf::Vector2f &direction) : pos(pos), direction(direction) {}

Turtle::Turtle(const sf::Vector2f &pos) : pos(pos) {}

void Turtle::goWithoutDrawing() {
    pos += direction * size;
}

void Turtle::goWithDrawing() {
    vertexVector.emplace_back(pos, fillcolor);
    //vertexArray.append(sf::Vertex(pos, fillcolor));
    pos += direction * size;
    //vertexArray.append(sf::Vertex(pos, fillcolor));
    vertexVector.emplace_back(pos, fillcolor);
}

void Turtle::turnRight() {
    direction = sf::Vector2f(direction.y, -direction.x);
}

void Turtle::turnLeft() {
    direction = sf::Vector2f(-direction.y, direction.x);
}

void Turtle::turnDown() {
    direction = sf::Vector2f(0.f, 1.f);
}

void Turtle::turnUp() {
    direction = sf::Vector2f(0.f, -1.f);
}

void Turtle::rotateDirection(float angle) {
    angle *= M_PI / 180.f;
    const float cs = cos(angle);
    const float sn = sin(angle);

    float nx = direction.x * cs - direction.y * sn;
    float ny = direction.x * sn + direction.y * cs;

    direction = sf::Vector2f(nx, ny);
}

const sf::VertexArray &Turtle::getVertexArray() const {
    return vertexArray;
}

void Turtle::clear() {
    vertexArray = sf::VertexArray(sf::Lines);
    vertexVector.clear();
}

void Turtle::flush(sf::RenderWindow &window) {
    window.draw(vertexArray);
    vertexArray.clear();
}

void Turtle::saveState() {
    states.push(std::make_unique<Turtle>(*this));
}

void Turtle::previousState() {
    pos = states.top()->pos;
    direction = states.top()->direction;
    size = states.top()->size;
    fillcolor = states.top()->fillcolor;
    states.pop();
}

Turtle::Turtle(const Turtle &t) {
    pos = t.pos;
    direction = t.direction;
    size = t.size;
    fillcolor = t.fillcolor;
}

float Turtle::getSize() const {
    return size;
}

void Turtle::setSize(float size) {
    Turtle::size = size;
}

void Turtle::setFillcolor(const sf::Color &fillcolor) {
    Turtle::fillcolor = fillcolor;
}

const sf::Color &Turtle::getFillcolor() const {
    return fillcolor;
}

void Turtle::removeLast() {
    if(!vertexVector.empty()){
        vertexVector.pop_back();
        vertexVector.pop_back();
    }
}

const std::vector<sf::Vertex> &Turtle::getVertexVector() const {
    return vertexVector;
}
