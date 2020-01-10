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

static std::mt19937 gen(time(0));
static std::uniform_int_distribution<> uid(0, 10000000);

static const std::map<char, std::function<void(Turtle &)>> alphabetTranscriptTurtle{
        {'R',  [](Turtle &turtle) {
            turtle.setFillcolor(sf::Color(uid(gen) % 255, uid(gen) % 255, uid(gen) % 255));
        }},
        {'C',  [](Turtle &turtle) {
            turtle.setFillcolor(sf::Color::Black);
        }},
        {'D',  [](Turtle &turtle) {
            turtle.setSize(turtle.getSize() / 2);
        }},
        {'d',  [](Turtle &turtle) {
            turtle.setSize(turtle.getSize() / 2);
        }},
        {'T',  [](Turtle &turtle) {
            turtle.setSize(turtle.getSize() * std::sqrt(5));
        }},
        {'t',  [](Turtle &turtle) {
            turtle.setSize(turtle.getSize() / std::sqrt(5));
        }},
        {'~',  [](Turtle &turtle) {
            turtle.setSize(turtle.getSize() * 2);
        }},
        {'i',  [](Turtle &turtle) {
            turtle.goWithoutDrawing();
        }},
        {'I',  [](Turtle &turtle) {
            turtle.setSize(turtle.getSize() * 2);
        }},
        {'A',  [](Turtle &turtle) {
            turtle.goWithDrawing();
        }},
        {'B',  [](Turtle &turtle) {
            turtle.goWithDrawing();
        }},
        {'F',  [](Turtle &turtle) {
            turtle.goWithDrawing();
        }},
        {'f',  [](Turtle &turtle) {
            turtle.goWithoutDrawing();
        }},
        {'+',  [](Turtle &turtle) {
            turtle.turnLeft();
        }},
        {'-',  [](Turtle &turtle) {
            turtle.turnRight();
        }},
        {'&',  [](Turtle &turtle) {
            turtle.turnDown();
        }},
        {'^',  [](Turtle &turtle) {
            turtle.turnUp();
        }},
        {'\\', [](Turtle &turtle) {
            turtle.rotateDirection(26.565051177077986f);
        }},
        {'/',  [](Turtle &turtle) {
            turtle.rotateDirection(63.43494882292201f);
        }},
        {'|',  [](Turtle &turtle) {
            turtle.rotateDirection(180.f);
        }},
        {'[',  [](Turtle &turtle) {
            turtle.saveState();
        }},
        {']',  [](Turtle &turtle) {
            turtle.previousState();
        }},
        {'@',  [](Turtle &turtle) {
            turtle.rotateDirection(uid(gen) % 45);
        }},
        {'#',  [](Turtle &turtle) {
            turtle.rotateDirection(-(uid(gen) % 45));
        }},
        {'S',  [](Turtle &turtle) {
            sf::Color color = turtle.getFillcolor();
            turtle.setFillcolor(sf::Color(static_cast<sf::Uint8>(255 - (255 - color.r) / 1.1f),
                                          static_cast<sf::Uint8>(255 - (255 - color.g) / 1.1f),
                                          static_cast<sf::Uint8>(255 - (255 - color.b) / 1.1f)));
            turtle.setSize(turtle.getSize() / 1.1f);
        }}
};

static const std::map<char, std::string> alphabetRules{
        {'F', "[DDD+F-F-ff-F-F-ff+F-F-FF-F-F-ff+F-F-ff-F-F-ff-f|FF|\\TFt/+FF|f+f]f"}
        /*{'X',"/X"},
        {'F',"B!XXD[B-F][+B-F][|B-F][-B-F]"},
        {'f',"DDifII"}*/
};

static const std::map<char, std::function<void(L_system &)>> alphabetTranscript{
        {'?', [](L_system &l_system) {
            if (uid(gen) % 1000 > 100)
                l_system.moveIterator(1);
        }},
        {'!', [](L_system &l_system) {
            if (l_system.getNesting() >= 3)
                l_system.moveIterator(std::string("XXD[B-F][+B-F][|B-F][-B-F]").length());
        }}
};


#endif //L_SYSTEM_L_SYSTEM_H
