//
// Created by Gentoo Huentoo on 2019-04-18.
//

#ifndef L_SYSTEM_L_SYSTEM_H
#define L_SYSTEM_L_SYSTEM_H

#include "Turtle.h"
#include <unordered_map>
#include <functional>
#include <string>
#include <random>
#include <math.h>

#define DEFAULT_ANGLE 45.f

class L_system {
private:
    Turtle turtle;
    std::string _string;
    int iterator = 0;
public:
    L_system() = default;

    const Turtle &getTurtle() const;

    void setSizeTurtle(float);

    explicit L_system(const std::string &string);

    L_system(const Turtle &turtle, const std::string &_string);

    void update();

    void draw();

    int getNesting();

    void moveIterator(unsigned long);

    void clearTurtle();

    sf::VertexArray getVertexArray();
};


#endif //L_SYSTEM_L_SYSTEM_H
