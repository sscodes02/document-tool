
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    struct dicthelp {
        char data;
        int isCount;
        bool isTerminal;
        dicthelp* qt[259];
        dicthelp(char ch){
            for(int i = 0 ; i<259 ; i++){
                qt[i] = NULL;
            } 
            isTerminal = false;
            isCount = 0;
            data = ch;
        }
    };
    dicthelp* root;

    vector<string> convert_to_vector(string sent) {
        string s;
        vector<string> vec;
        string separators = " ,.:!\"\'()?—[]“” ‘’;˙@";
        for (int i = 0; i < sent.length(); i++) {
            if (separators.find(sent[i]) != string::npos){
                if (!s.empty()) {
                    vec.push_back(s);
                    s = "";
                }
            } else {
                s += sent[i];
            }
        }

        if (!s.empty()) {
            vec.push_back(s);
        }
        
        return vec;
    }


void insert_help(string str, dicthelp* root) {
    if (str.empty()) {
        root->isTerminal = true;
        root->isCount++;
        return;
    }
    int index;
    if (isalpha(str[0])) {
        index = tolower(str[0]) - 'a' + 10;
    } 
    else if (isdigit(str[0])) {
        index = str[0] - '0';
    }
    else {
        index = str[0] + 3;
    }
    if (root->qt[index] != nullptr) {
        insert_help(str.substr(1), root->qt[index]);
    } else {
        dicthelp* child = new dicthelp(str[0]);
        root->qt[index] = child;
        insert_help(str.substr(1), child);
    }
}

    int count_helper(string str, dicthelp* root) {
        string separators = " ,.:!\"\'()?—[]“” ‘’;˙@";
        for (int i = 0; i < str.size(); i++) {
            if (separators.find(str[i]) != string::npos) {
                return 0;
            }
        }
        if (str.empty()) {
            return root->isCount;
        }
        int index;
        if (isalpha(str[0])) {
            index = tolower(str[0]) - 'a' + 10;
        }
        else if (isdigit(str[0])) {
            index = str[0] - '0';
        } 
        else {
            index = str[0] + 3;
        }

        if (root->qt[index] != nullptr) {
            return count_helper(str.substr(1), root->qt[index]);
        } else {
            return 0;
        }
    }
    
    void dump_help(dicthelp* node, string curr_word, ofstream& outFile) {
        if (node == nullptr) {
            return;
        }
        if (node->isTerminal) {
            string w = curr_word;
            outFile << w << ", " << node->isCount << endl;
        }

        for (int i = 0; i < 259; i++) {
            if (node->qt[i] != nullptr) {
                char nextChar;
                if (i >= 10 && i<36) {
                    nextChar = 'a' + (i - 10);
                } else if(i<10) {
                    nextChar = i + '0';
                }
                else{
                    nextChar = i-3;
                }
                dump_help(node->qt[i], curr_word + nextChar, outFile);
            }
        }
    }
    

public: 

    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);
};