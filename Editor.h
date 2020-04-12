#pragma once
#include "Document.h"

class Editor {
    public:
        Editor();
        ~Editor();
        void loop();
        void writeAndExit(ofstream & myfile , string & output);
    private:
        Document * doc;
};