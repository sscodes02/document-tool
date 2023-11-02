// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    // Implement your function here  
    num_of_sentences=0;
    offset = -1;
    b_cd = -1;
    pr = -1;
    pagee = -1;
    
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
    for (auto &node : nodes) {
        delete node;
    }
    nodes.clear();
}


void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    num_of_sentences++;
    Node* n = new Node(book_code , page , paragraph , sentence_no , offset);
    sentences.push_back(sentence);
    nodes.push_back(n);
    return;
}

int SearchEngine::get_num_of_sentences(){
    return num_of_sentences;
}

Node* SearchEngine::search(string pattern, int& n_matches) {
    // Implement your function here 
    int sen_no = get_num_of_sentences();
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int h = 0; h < sen_no; h++) {
        string sen = sentences[h];

        int badchar[256];
        for (int i = 0; i < 256; i++) {
            badchar[i] = pattern.length();
        }
        for (int r = 0; r < pattern.length(); r++) {
            badchar[pattern[r]] = pattern.length() - 1 - r;
        }
        int p = 0;
        while (p <= sen.length() - pattern.length()) {
            int j = pattern.length() - 1;
            while (p + j >= 0 && j >= 0 && p + j < sen.length() && tolower(pattern[j]) == tolower(sen[p + j])) {
                j--;
            }
            if (j < 0) {
                nodes[h]->offset = p;
                Node* newnode = nodes[h];
                if (head == nullptr) {
                    head = newnode;
                    tail = newnode;
                } else {
                    newnode->left = tail;
                    tail->right = newnode;
                    tail = newnode;
                }
            }
            if (p + j < sen.length()) {
                p += max(1, badchar[tolower(sen[p + j])]);
            } 
            else {
                break;
            }

        }
    }

    n_matches = 0;
    Node* curr = head;
    while (curr != nullptr) {
        n_matches++;
        curr = curr->right;
    }
    return head;
}
