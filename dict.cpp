// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here  
    root = new dicthelp('\0');
}

Dict::~Dict(){
    // Implement your function here 
    delete root;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    vector<string> meow = convert_to_vector(sentence);
    for(int i = 0 ; i<meow.size() ; i++){
        insert_help(meow[i] , root);
    }
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here  
    // return case_insensitive(word);
    return count_helper(word , root);
}

void Dict::dump_dictionary(string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Unable to open the file." << endl; // Print an error message
        return;
    }
    dump_help(root, "", outFile);
    outFile.close();
}