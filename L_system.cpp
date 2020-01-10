//
// Created by Gentoo Huentoo on 2019-04-18.
//

#include "L_system.h"
#include "Mode.h"

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
#ifdef TREE_1
            turtle.rotateDirection(-25.7); // tree1 setup
#elif defined(TREE_2)
            turtle.rotateDirection(-22.5); // tree2 setup
#else
            turtle.rotateDirection(26.565051177077986f);
#endif
        }},
        {'/',  [](Turtle &turtle) {
#ifdef TREE_1
            turtle.rotateDirection(25.7);// tree1 setup
#elif defined(TREE_2)
            turtle.rotateDirection(22.5); // tree 2 setup
#else
            turtle.rotateDirection(63.43494882292201f);
#endif
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
#ifdef SIERPINSKI_TRIANGLE
        {'F', "F+F-F-F+F"} // sierpinski triangle
#elif defined(TREE_2)
        {'F', "FF/[/F\\F\\F]\\[\\F/F/F]"} // tree 2 setup
#elif defined(TREE_1)
        {'F', "F[/F]F[\\F]F"} // tree 1 setup
#else
        {'F', "[DDD+F-F-ff-F-F-ff+F-F-FF-F-F-ff+F-F-ff-F-F-ff-f|FF|\\TFt/+FF|f+f]f"}
#endif
//        {'X',"/X"},
//        {'F',"B!XXD[B-F][+B-F][|B-F][-B-F]"},
//        {'f',"DDifII"},
//        {'A', "B/A/B"},
//        {'B', "A\\B\\A"}
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
