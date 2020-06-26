
#include <iostream>

using namespace std;

#ifndef TRANSITION_H_
#define TRANSITION_H_

enum Direction{
    LEFT, RIGHT
};

class Transition {
private:
    string currentState;
    char currentSymbol;
    string nextState;
    char nextSymbol;
    Direction direction;

public:
    Transition(string currentState, char currentSymbol, string nextState, char nextSymbol,Direction direction);
    virtual ~Transition();
    const string getCurrentState() const;
    void setCurrentState(const string &currentState);
    char getCurrentSymbol() const;
    void setCurrentSymbol(char currentSymbol);
    Direction getDirection() const;
    void setDirection(Direction direction);
    const string getNextState() const;
    void setNextState(const string &nextState);
    char getNextSymbol() const;
    void setNextSymbol(char nextSymbol);
    string toString();
};

#endif /* TRANSITION_H_ */

