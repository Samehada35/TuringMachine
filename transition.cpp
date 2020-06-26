#include "transition.h"
#include<string>

Transition::Transition(string currentState, char currentSymbol, string nextState, char nextSymbol, Direction direction) : currentState(currentState), currentSymbol(currentSymbol), nextState(nextState), nextSymbol(nextSymbol), direction(direction){
    // TODO Auto-generated constructor stub
}

const string Transition::getCurrentState() const {
    return currentState;
}

void Transition::setCurrentState(const string &currentState) {
    this->currentState = currentState;
}

char Transition::getCurrentSymbol() const {
    return currentSymbol;
}

void Transition::setCurrentSymbol(char currentSymbol) {
    this->currentSymbol = currentSymbol;
}

Direction Transition::getDirection() const {
    return direction;
}

void Transition::setDirection(Direction direction) {
    this->direction = direction;
}

const string Transition::getNextState() const {
    return nextState;
}

void Transition::setNextState(const string &nextState) {
    this->nextState = nextState;
}

char Transition::getNextSymbol() const {
    return nextSymbol;
}

void Transition::setNextSymbol(char nextSymbol) {
    this->nextSymbol = nextSymbol;
}

string Transition::toString(){
    return "(" + this->getCurrentState() +", "+this->getCurrentSymbol()+") -> ("+this->getNextState()+", "+this->getNextSymbol()+", "+ (this->getDirection()==Direction::RIGHT ? "R" : "L")+")"+"\n";

}


Transition::~Transition() {
    // TODO Auto-generated destructor stub
}


