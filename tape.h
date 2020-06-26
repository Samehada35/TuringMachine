#include<vector>
#include<deque>
#include<iostream>


using namespace std;

#ifndef TAPE_H_
#define TAPE_H_

class Tape {
private:
    deque<char> tape;
    int position;
    int cptL;
    int cptR;

public:
    Tape();
    Tape(string word);
    virtual ~Tape();
    int getsize();
    void moveLeft();
    void moveRight();
    void replaceCurrentSymbol(char newSymbol);
    int getCurrentPosition()const;
    char getCurrentSymbol() const;
    string toString();
};

#endif /* TAPE_H_ */
