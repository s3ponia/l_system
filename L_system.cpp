//
// Created by Gentoo Huentoo on 2019-04-18.
//

#include "L_system.h"

L_system::L_system(const std::string &string) : _string(string) {}

void L_system::update() {
    std::string res = "";
    for (; iterator < _string.length(); ++iterator) {
        if (alphabetTranscript.find(_string[iterator]) != alphabetTranscript.end())
            alphabetTranscript.at(_string[iterator])(*this);
        else if (alphabetRules.find(_string[iterator]) != alphabetRules.end()) {
            res += alphabetRules.at(_string[iterator]);
        } else {
            res += _string[iterator];
        }
    }
    _string = res;
    iterator = 0;
}

void L_system::draw() {
    for (char ch:_string) {
        if (alphabetTranscriptTurtle.find(ch) != alphabetTranscriptTurtle.end())
            alphabetTranscriptTurtle.at(ch)(turtle);
    }
}

sf::VertexArray L_system::getVertexArray() {
    return turtle.getVertexArray();
}

L_system::L_system(const Turtle &turtle, const std::string &_string) : turtle(turtle), _string(_string) {}

const Turtle &L_system::getTurtle() const {
    return turtle;
}

void L_system::setSizeTurtle(float f) {
    turtle.setSize(f);
}

void L_system::moveIterator(unsigned long i) {
    iterator += i;
}

void L_system::clearTurtle() {
    turtle.clear();
}

int L_system::getNesting() {
    int res = 0;
    for (int i = 0; i < iterator; ++i) {
        if (_string[i] == '[')
            ++res;
        else if (_string[i] == ']')
            --res;
    }

    return res;
}
