
#include "dict.h"

Dict::Dict(){
  
    root = new dicthelp('\0');
}

Dict::~Dict(){

    delete root;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){

    vector<string> meow = convert_to_vector(sentence);
    for(int i = 0 ; i<meow.size() ; i++){
        insert_help(meow[i] , root);
    }
    return;
}

int Dict::get_word_count(string word){

    return count_helper(word , root);
}

void Dict::dump_dictionary(string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Unable to open the file." << endl;
        return;
    }
    dump_help(root, "", outFile);
    outFile.close();
}