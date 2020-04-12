#include "Document.h"
#include <string>
#include <iostream>
#include <iterator>
#include <cctype>
#include <fstream>
#include <sstream> 
#include <algorithm>

using namespace std;

Document::~Document(){
   this->store.~vector();
}
Document::Document() : row(0) , store(vector<string>()) {}
ostream& operator<<(ostream& os, const vector<string>& vec){
    for (auto it = vec.begin(); it != vec.end(); ++it){
        if(it == vec.end()-1){
            cout <<  *it;
        } 
        else{
            cout <<  *it << endl;        
        } 
    }
    return os;
}

void Document::execution(string word ,string & output) {
    
    // "%p"
    if(word.find("%p") != string::npos) {
        for (auto it = this->store.begin(); it != this->store.end(); ++it){
            if(it == this->store.end()-1){
                cout <<  *it;
            } 
         else{
            cout <<  *it << endl;        
        } 
     }
        for(auto i : this->store){
            output += i + "\n";
        }
        this->row = this->store.size() - 1;
    }    
    // "?text"
    else if (word.find("?") != string::npos){
        string str = word.substr(1 , word.length());
        bool flag = false;
        for (size_t i = this->row; i > 0  ; i--) {
            if(this->store.at(i).find(str) != string::npos) {
                cout << this->store.at(i) + "\n";
                output += this->store.at(i) + "\n";
                this->row = i;
                flag = true;
                break;
            }
        }  
        if(!flag)
            this->row = 0;   
    }
    // s/old/new/ - replace only
    else if(word.substr(0,2).compare("s/") == 0 && word.at(word.length() - 1) == '/'){
        vector<string> vec;
        split(word , '/' , vec);
        string oldSTR = vec.at(1);
        string newSTR = vec.at(2);
        string strTemp =  *(this->store.begin() + this->row);
        (this->store.begin() + this->row) -> replace(strTemp.find(oldSTR) , oldSTR.length() , newSTR);
    }
    // "/text" - find text forward and print the line of the text
    else if (word.at(0) == '/') {
        string str = word.substr(1 , word.length());
        bool flag = false;
        for (size_t i = this->row ; i < this->store.size() ; i++) {
            if(this->store.at(i).find(str) != string::npos){
                cout << this->store.at(i) + "\n";
                output += this->store.at(i) + "\n";
                this->row = i;
                flag = true;
                break;
            }
        }  
        if(!flag) 
            this->row = this->store.size() - 1;    
    }
    // a
    else if(word.compare("a") == 0) {
        string input;
        vector<string> temp;
        while(getline(cin, input) && input.compare(".") != 0) {
            temp.push_back(input);
        }
        if(this->row != this->store.size() - 1)
            this->store.insert(this->store.begin() + this->row , temp.begin() , temp.end());
        else
            this->store.insert(this->store.end() , temp.begin() , temp.end());
    }
    // i
    else if(word.compare("i") == 0){
        string input;
        vector<string> temp;
        while(getline(cin, input) && input.compare(".") != 0) {
            temp.push_back(input);
        }
        this->store.insert(this->store.begin() + this->row - 1, temp.begin() , temp.end());
    }
    // c
    else if(word.compare("c") == 0){
        auto position = this->store.begin() + this->row;
        string input;
        vector<string> temp;
        this->store.erase(this->store.begin() + this->row);
        while(getline(cin, input) && input.compare(".") != 0) {
            temp.push_back(input);
        }
        this->store.insert(this->store.begin() + this->row , temp.begin() , temp.end());
    }
    // 3,4j
    else if(word.find(",")  != string::npos && word.find("j")  != string::npos){
        vector<string> vec;
        split(word , ',' , vec);
        int a = stoi(vec.at(0));
        int b = stoi(vec.at(1).substr(0 , vec.at(1).find('j')));
        (this->store.begin() + a - 1)->append(" " + *(this->store.begin() + b - 1));
        this->store.erase(this->store.begin() + b - 1);
        this->row = a - 1;
    }
    // "3n"
    else if(word.find("n") != string::npos && is_number(word.substr(0,word.find("n")))) {
        int x = stoi(word.substr(0 , word.find("n")));
        output += to_string(x) + "	"  +  *(this->store.begin() + x - 1) + "\n";
        cout << x << "  " << *(this->store.begin() + x - 1) << endl;
        this->row = x;
    }
    // "3d"
    else if(word.find("d") != string::npos && is_number(word.substr(0,word.find("d")))) {
        int x = stoi(word.substr(0 , word.find('d')));
        this->store.erase((this->store.begin() + x - 1));
        this->row = x;
    }
}


bool boolReplace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void split(std::string const &str, const char delim,std::vector<std::string> &out){
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
