#include "tape.h"

Tape::Tape() {
    // TODO Auto-generated constructor stub

}

Tape::~Tape() {
    // TODO Auto-generated destructor stub
}



Tape::Tape(string word) {
    // TODO Auto-generated constructor stub
    position=0;

    for(unsigned int i=0; i< word.length();i++){
            if (word.at(i)==' '){
                 tape.push_back('B');
            }
            tape.push_back(word.at(i));
    }


}

string Tape::toString(){
    string s="";

    for(char var : tape){
        var=='B' ? s+=' ' : s+= var;
    }

    return s;
}

void Tape::moveRight(){
    if(position+1 < tape.size()){
        position++;
    }else{
        tape.emplace_back('B');
        position++;
    }
}


int Tape::getsize(){
    return tape.size();
}

void Tape::moveLeft(){
   if (position-1 >= 0){
       position--;
   }else{
       tape.emplace_front('B');
       position=0;
   }
}


int Tape::getCurrentPosition()const{
    return position;
}

char Tape::getCurrentSymbol()const{
    return tape.at(position);
}


void Tape::replaceCurrentSymbol(char newSymbol){
        tape[position]=newSymbol;
}

