
#include "transition.h"
#include "tape.h"
#include <utility>


#ifndef TURINGMACHINE_H_
#define TURINGMACHINE_H_
#define TAPE_SIZE 1000


using namespace std;

class TuringMachine {
private:
    Tape tape;
    vector<Transition> transitions;
    vector<pair<string,bool>> states;
    vector<pair<char,bool>> symbols;
    string machineSteps;
    string finalState;
    string initialState;
    string currentState;
    char blankSymbol;
    int index;
    vector<string> tapeHistory;
    vector<int> indexHistory;
    vector<Transition> transitionsHistory;
    bool isAFinalState(string state);

public:
    TuringMachine();
    virtual ~TuringMachine();
    static TuringMachine* parseFile(string path) throw(string);
    static TuringMachine* parseString(string input) throw(string);
    string run(string input, bool step, bool state, bool tape);
    string describe();
    string getFinalState();
    void setFinalState(string finalStatee);
    void setcurrentState(string current);
    string getcurrentState()const;
    void setmachineSteps(string message);
    string _tapes();
    string _steps();
    string _state();
    void addWord(string s);
    void treatmentOfTransitions();
    int treatmentOfOneTransition(Transition tr);
    vector<string> getTapeHistory();
    vector<int> getIndexHistory();
    vector<Transition> getTransitionsHistory();
};

#endif /* TURINGMACHINE_H_ */
