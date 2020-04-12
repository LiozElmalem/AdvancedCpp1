#pragma once
#include <vector>
#include <string> 

using namespace std;

class Document {

    public:
        Document();
        ~Document();
        void execution(string word , string & output);
    private:
        vector<string> store;
        int row;
};

istream& operator >> (istream & is,vector<string>& f);
bool boolReplace(std::string& str, const std::string& from, const std::string& to);
void split(std::string const &str, const char delim,std::vector<std::string> &out);
bool is_number(const std::string& s);