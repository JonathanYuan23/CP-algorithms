#include<bits/stdc++.h>
using namespace std;

struct Node {
    bool isLeafNode = 1;
    string value = "";
    Node *children[26];
};

int numberOfWords;

void insert(Node *root, string &word) {
    Node *cur = root;
    for(char &c: word) {
        // as the current node has at least one child, it is not a leaf node
        cur -> isLeafNode = 0;
        // check for upper case characters
        c = (char) tolower(c);
        int pos = c - 'a';
        if(cur -> children[pos] == nullptr) {
            cur -> children[pos] = new Node();
            cur -> children[pos] -> value = c;
        }
        cur = cur -> children[pos];
    }
}

void remove(Node *node) {
    if(!node) return;
    for(auto &c: node -> children) remove(c);
    // delete the data the pointer points to
    delete node;
    // make the pointer point nowhere
    node = nullptr;
}

void printTrie(Node *node, string word) {
    if(!node) return;
    word += node -> value;
    if(node -> isLeafNode) cout << word << '\n';
    for(auto &c: node -> children) printTrie(c, word);
}

int main() {
    Node *root = new Node();
    cout << "How many words do you want in your trie:\n";
    cin >> numberOfWords;
    for(int i=1; i<=numberOfWords; i++) {
        string word; 
        cout << "\nEnter word " << i << ":\n";
        cin >> word;
        insert(root, word);
    }
    cout << "\nThese are the words in your trie:\n";
    printTrie(root, "");
    // free memory
    remove(root);
}