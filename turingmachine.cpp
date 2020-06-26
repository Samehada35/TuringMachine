#include "turingmachine.h"
#include <fstream>
#include <string>
#include <regex>

static int cpt=0;
static int cpt1=0;

TuringMachine::TuringMachine() {
    // TODO Auto-generated constructor stub
}


TuringMachine::~TuringMachine() {
    // TODO Auto-generated destructor stub
}



string TuringMachine::getFinalState(){
    return finalState;
}

void TuringMachine::setFinalState(string finalStatee){
    finalState = finalStatee;
}


void TuringMachine::setcurrentState(string current){
    currentState= current;

}
string TuringMachine::getcurrentState()const{
    return currentState;
}

vector<string> TuringMachine::getTapeHistory(){
    return tapeHistory;
}
vector<int> TuringMachine::getIndexHistory(){
    return indexHistory;
}
vector<Transition> TuringMachine::getTransitionsHistory(){
    return transitionsHistory;
}

void TuringMachine::setmachineSteps(string message){
    machineSteps +=message;
}

string TuringMachine::describe(){
    string description = "";
    description+="Turing Machine description : \n";
    description+="Initial State : " + this->initialState +"\n";
    description+="Blank Symbol : " + string(1,this->blankSymbol) +"\n";

    description+="\nSymbols :\n";

    for(pair<char,bool> symbol : this->symbols){
        description+=string(1,symbol.first) + "(" + (symbol.second==true ? "Input Vocabulary" : "Not Input Vocabulary") +")\n";
    }

    description+="\nStates : \n";

    for(pair<string,bool> state : this->states){
        description+=state.first + "(" + (state.second==true ? "Final State" : "Not Final State") + ")\n";
    }

    description+="\nTransitions : \n";

    for(Transition t : this->transitions){
        description+= "(" + t.getCurrentState() + "," + t.getCurrentSymbol() + ") => (" + t.getNextState() + "," + t.getNextSymbol() + "," + (t.getDirection()==Direction::RIGHT ? "R" : "L") + ")\n";
    }

    description+="\n\n";

    return description;
}


const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

int TuringMachine::treatmentOfOneTransition(Transition tr){
    while ((tr.getCurrentState() == getcurrentState())&&(tape.getCurrentSymbol() == tr.getCurrentSymbol()) && tape.getCurrentSymbol()==tr.getNextSymbol()){
        tapeHistory.push_back(blankSymbol+trim(tape.toString())+blankSymbol);
        transitionsHistory.push_back(tr);
        indexHistory.push_back(index);

        tr.getDirection() == Direction::RIGHT ? tape.moveRight() : tape.moveLeft();
        index+=tr.getDirection()==Direction::RIGHT ? 1 : -1;

        setcurrentState(tr.getNextState());
        setmachineSteps(tr.toString());

        if(cpt1==TAPE_SIZE)
            break;
        cpt1++;

        if(isAFinalState(tr.getNextState())){
            setFinalState(tr.getNextState());
            return -1;
        }


    }

        while ((tr.getCurrentState() == getcurrentState())&&(tape.getCurrentSymbol() == tr.getCurrentSymbol()) && tape.getCurrentSymbol() != tr.getNextSymbol()){
            tapeHistory.push_back(blankSymbol+trim(tape.toString())+blankSymbol);
            transitionsHistory.push_back(tr);
            indexHistory.push_back(index);

            tape.replaceCurrentSymbol(tr.getNextSymbol());
            tr.getDirection() == Direction::RIGHT ? tape.moveRight() : tape.moveLeft();
            index+=tr.getDirection()==Direction::RIGHT ? 1 : -1;

            setcurrentState(tr.getNextState());
            setmachineSteps(tr.toString());

            if(isAFinalState(tr.getNextState())){
                setFinalState(tr.getNextState());
                return -1;
            }

            cpt1++;
            if(cpt1==TAPE_SIZE)
                break;
        }


        return 0;

}

void TuringMachine::treatmentOfTransitions(){
    unsigned int i=0;
    int res=0;

    setcurrentState(initialState);

    while (i< transitions.size()){
        res = treatmentOfOneTransition(transitions[i]);

        if(res==-1)
            break;

        i++;

        if(i==transitions.size()){
            i=0;
            cpt++;
        }
        if(cpt1==TAPE_SIZE) break;
        if(cpt==TAPE_SIZE) break;
    }

    tapeHistory.push_back(blankSymbol+trim(tape.toString())+blankSymbol);
}



bool TuringMachine::isAFinalState(string state){
    for(std::pair<string,bool> var : states){
        if (state==var.first){
            return var.second;
        }

    }
    return false;
}




string TuringMachine::_tapes(){
    return tape.toString();
}

string TuringMachine::_state(){
    return getFinalState();
}

string TuringMachine::_steps(){
    return machineSteps;
}

void TuringMachine::addWord(string s){
    Tape t(s);
    this->tape=t;
}

TuringMachine* TuringMachine::parseFile(string path) throw(string){
    TuringMachine *tm = new TuringMachine();

    ifstream file(path);
    string l;
    regex r("\\(|\\)");
    int lineNumber=1;

if(file){
        while(getline(file,l)){
            size_t first = l.find_first_not_of(' ');
                if (string::npos != first){
                    size_t last = l.find_last_not_of(' ');
                    l = l.substr(first, (last - first + 1));
                }

            if(l.empty()){
                continue;
            }

            lineNumber++;
            cout.flush();
            if(l.at(l.size()-1) != ')'){
                throw string("Error : Missing ')' at line "+to_string(lineNumber)+"\n");
            }
            vector<string> tokens = {sregex_token_iterator(l.begin(), l.end(), r, -1), sregex_token_iterator()};

            if(tokens.size() <=1){
                throw string("Error : Missing '(' at line "+to_string(lineNumber)+"\n");
            }

            if(!tokens[0].compare("initial")){
                if(tokens[1].empty()){
                    throw string("Error : One parameter must be specified for initial() at line "+to_string(lineNumber)+"\n");
                }
                tm->initialState = tokens[1];
            }else if(!tokens[0].compare("blank")){
                if(tokens[1].empty()){
                    throw string("Error : One parameter must be specified for blank() at line "+to_string(lineNumber)+"\n");
                }
                tm->blankSymbol = tokens[1].c_str()[0];
            }else if(!tokens[0].compare("state")){
                stringstream tokenizer(tokens[1]);
                vector<string> instructionTokens;
                string s;

                while(getline(tokenizer,s,',')){
                    instructionTokens.push_back(s);
                }

                if(instructionTokens.size() != 2){
                    throw string("Error : Exactly 2 parameters must be specified for state() at line "+to_string(lineNumber)+"\n");
                }else if(instructionTokens[1].c_str()[0] != 'T' && instructionTokens[1].c_str()[0] != 'F'){
                    throw string("Error : Second parameter of state() has to be either 'T' or 'F' at line "+to_string(lineNumber)+"\n");
                }

                pair<string,bool> p;
                p.first = instructionTokens[0];
                p.second = instructionTokens[1].c_str()[0] == 'T' ? true : false;

                tm->states.push_back(p);
            }else if(!tokens[0].compare("symbol")){
                stringstream tokenizer(tokens[1]);
                vector<string> instructionTokens;
                string s;

                while(getline(tokenizer,s,',')){
                    instructionTokens.push_back(s);
                }

                if(instructionTokens.size() != 2){
                    throw string("Error : Exactly 2 parameters must be specified for symbol() at line "+to_string(lineNumber)+"\n");
                }else if(instructionTokens[1].c_str()[0] != 'T' && instructionTokens[1].c_str()[0] != 'F'){
                    throw string("Error : Second parameter of symbol() has to be either 'T' or 'F' at line "+to_string(lineNumber)+"\n");
                }

                pair<char,bool> p;
                p.first = instructionTokens[0].c_str()[0];
                p.second = instructionTokens[1].c_str()[0] == 'T' ? true : false;

                tm->symbols.push_back(p);
            }else if(!tokens[0].compare("transition")){
                stringstream tokenizer(tokens[1]);
                vector<string> instructionTokens;
                string s;

                while(getline(tokenizer,s,',')){
                    instructionTokens.push_back(s);
                }

                if(instructionTokens.size() != 5){
                    throw string("Error : Exactly 5 parameters must be specified for transition() at line "+to_string(lineNumber)+"\n");
                }else if(instructionTokens[4].c_str()[0] != 'R' && instructionTokens[4].c_str()[0] != 'L'){
                    throw string("Error : Fifth parameter of transition() has to be either 'R' or 'L' at line "+to_string(lineNumber)+"\n");
                }

                Transition tr(instructionTokens[0],
                              instructionTokens[1].c_str()[0],
                              instructionTokens[2],
                              instructionTokens[3].c_str()[0],
                              !instructionTokens[4].compare("R") ? Direction::RIGHT : Direction::LEFT);

                tm->transitions.push_back(tr);
            }else{
                throw string("Error : Unknown command "+tokens[0]+" at line "+to_string(lineNumber)+"\n");
            }

        }

    }else{
        throw string("Error : Could not open file "+path+"\n");
        return NULL;
    }

    return tm;
}

TuringMachine* TuringMachine::parseString(string input) throw(string){
    TuringMachine *tm = new TuringMachine();

    string l;
    istringstream str(input);
    regex r("\\(|\\)");
    int lineNumber=1;

if(str){
        while(getline(str,l)){
            size_t first = l.find_first_not_of(' ');
                if (string::npos != first){
                    size_t last = l.find_last_not_of(' ');
                    l = l.substr(first, (last - first + 1));
                }

            if(l.empty()){
                continue;
            }

            lineNumber++;
            cout.flush();
            if(l.at(l.size()-1) != ')'){
                throw string("Error : Missing ')' at line "+to_string(lineNumber)+"\n");
            }
            vector<string> tokens = {sregex_token_iterator(l.begin(), l.end(), r, -1), sregex_token_iterator()};

            if(tokens.size() <=1){
                throw string("Error : Missing '(' at line "+to_string(lineNumber)+"\n");
            }

            if(!tokens[0].compare("initial")){
                if(tokens[1].empty()){
                    throw string("Error : One parameter must be specified for initial() at line "+to_string(lineNumber)+"\n");
                }
                tm->initialState = tokens[1];
            }else if(!tokens[0].compare("blank")){
                if(tokens[1].empty()){
                    throw string("Error : One parameter must be specified for blank() at line "+to_string(lineNumber)+"\n");
                }
                tm->blankSymbol = tokens[1].c_str()[0];
            }else if(!tokens[0].compare("state")){
                stringstream tokenizer(tokens[1]);
                vector<string> instructionTokens;
                string s;

                while(getline(tokenizer,s,',')){
                    instructionTokens.push_back(s);
                }

                if(instructionTokens.size() != 2){
                    throw string("Error : Exactly 2 parameters must be specified for state() at line "+to_string(lineNumber)+"\n");
                }else if(instructionTokens[1].c_str()[0] != 'T' && instructionTokens[1].c_str()[0] != 'F'){
                    throw string("Error : Second parameter of state() has to be either 'T' or 'F' at line "+to_string(lineNumber)+"\n");
                }

                pair<string,bool> p;
                p.first = instructionTokens[0];
                p.second = instructionTokens[1].c_str()[0] == 'T' ? true : false;

                tm->states.push_back(p);
            }else if(!tokens[0].compare("symbol")){
                stringstream tokenizer(tokens[1]);
                vector<string> instructionTokens;
                string s;

                while(getline(tokenizer,s,',')){
                    instructionTokens.push_back(s);
                }

                if(instructionTokens.size() != 2){
                    throw string("Error : Exactly 2 parameters must be specified for symbol() at line "+to_string(lineNumber)+"\n");
                }else if(instructionTokens[1].c_str()[0] != 'T' && instructionTokens[1].c_str()[0] != 'F'){
                    throw string("Error : Second parameter of symbol() has to be either 'T' or 'F' at line "+to_string(lineNumber)+"\n");
                }

                pair<char,bool> p;
                p.first = instructionTokens[0].c_str()[0];
                p.second = instructionTokens[1].c_str()[0] == 'T' ? true : false;

                tm->symbols.push_back(p);
            }else if(!tokens[0].compare("transition")){
                stringstream tokenizer(tokens[1]);
                vector<string> instructionTokens;
                string s;

                while(getline(tokenizer,s,',')){
                    instructionTokens.push_back(s);
                }

                if(instructionTokens.size() != 5){
                    throw string("Error : Exactly 5 parameters must be specified for transition() at line "+to_string(lineNumber)+"\n");
                }else if(instructionTokens[4].c_str()[0] != 'R' && instructionTokens[4].c_str()[0] != 'L'){
                    throw string("Error : Fifth parameter of transition() has to be either 'R' or 'L' at line "+to_string(lineNumber)+"\n");
                }

                Transition tr(instructionTokens[0],
                              instructionTokens[1].c_str()[0],
                              instructionTokens[2],
                              instructionTokens[3].c_str()[0],
                              !instructionTokens[4].compare("R") ? Direction::RIGHT : Direction::LEFT);

                tm->transitions.push_back(tr);
            }else{
                throw string("Error : Unknown command "+tokens[0]+" at line "+to_string(lineNumber)+"\n");
            }

        }

    }else{
        throw string("Error : Uknown error while parsing machine description\n");
        return NULL;
    }

    return tm;
}

string TuringMachine::run(string input, bool step, bool state, bool tape){
    int index=0;
    string result = "";
    result += "Running with given input...\n";
    addWord(input);
    treatmentOfTransitions();

    if (step) {
        result += "\nPrinting steps : \n";
        result += _steps()+"\n";
    }
    if (state){
        result += "\nPrinting final state : \n";
        result += _state()+"\n";
    }
    if (tape){
        result += "\nPrinting content of tape : \n";
        result += _tapes()+"\n";
    }

    return result;
}


