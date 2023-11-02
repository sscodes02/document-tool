
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine {
private:
    int num_of_sentences;
    int get_num_of_sentences();
    vector<string>sentences;
    vector<Node*>nodes;
    int b_cd;
    int pr;
    int pagee;
    int offset;
public: 
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);
};