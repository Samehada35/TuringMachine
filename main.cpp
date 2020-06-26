
#include "turingmachine.h"
#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QtWidgets>


using namespace std;
static const string _step= "-steps";
static const string _state= "-state";
static const string _tape= "-tape";

string getFileName(string file){

    return file;
}

void Console()
{
    AllocConsole();
    FILE *pFileCon = NULL;
    pFileCon = freopen("CONOUT$", "w", stdout);

    COORD coordInfo;
    coordInfo.X = 130;
    coordInfo.Y = 9000;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),ENABLE_QUICK_EDIT_MODE| ENABLE_EXTENDED_FLAGS);
}

int main(int argc, char** argv){
    string gui ="-gui";
    if(!gui.compare(argv[argc-1])){
    QApplication::setStyle("fusion");
    QApplication app(argc, argv);

    MainWindow window;

    window.setWindowTitle("Turing Machine");
    window.show();
    return app.exec();
    }else{
        Console();
        if(argc<4){
            cerr << "Error : At least 3 parameters are required\nUsage : "<< getFileName(argv[0]) <<" {[-steps]|[-state]|[-tape]} machine.tm input" << endl;
            exit(1);
        }else{
            bool step = false;
            bool state = false;
            bool tape = false;
            string word = "";
            string path ="";

            word = string(argv[argc-1]);
            path = string(argv[argc-2]);

            for(int i=1;i<=argc-3;i++){
                if(string(argv[i])==_step) step=true;
                else if (string(argv[i])==_state) state=true;
                else if (string(argv[i])==_tape) tape=true;
            }

            if(!step && !state && !tape){
                cerr << "Error : You have to specify at least one of those parameters : -state -steps -tape\nUsage : "<< getFileName(argv[0]) <<" {[-steps]|[-state]|[-tape]} machine.tm input" << endl;
                exit(2);
            }

            try{
                TuringMachine* tm = TuringMachine::parseFile(path);

                if(tm){
                    string description = tm->describe();
                    cout << tm->describe();
                    string result = tm->run(word,step,state,tape);
                    cout << result;
                }
            }catch(string err){
                cerr << err;
            }

            return 0;
        }
    }
}
