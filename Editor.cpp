#include "Editor.h"
#include <iostream>
#include <fstream>

using namespace std;

Editor::Editor() : doc(new Document()) {}

Editor::~Editor(){
    this->doc->~Document();
}

void Editor::loop(){
    string input;
    string output = "";
    ofstream myfile;
    myfile.open ("output.txt");
    myfile.clear();
    while(getline(cin , input)){
        if(input.at(0) == 'Q') {
            writeAndExit(myfile , output);
        }
        else{
            this->doc->execution(input , output);
        }
    }
}

void Editor::writeAndExit(ofstream & myfile , string & output){
    myfile << output;
    myfile.close();
    exit(0);
}