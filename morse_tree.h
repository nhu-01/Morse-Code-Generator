#ifndef MORSE_TREE_H
#define MORSE_TREE_H

#include <string>
#include "node.h"
using namespace std;

template<typename Type>
class MorseTree
{
private:
    Node<Type>* root;

    void insert(Node<Type>* node, const string& code, Type letter, size_t index);
    void clear(Node<Type>* node);
    bool encodeLetter(Node<Type>* node, Type letter, string code, string& result) const;
    Type decodeLetter(const string& code) const;

public:
    MorseTree();
    MorseTree(const string& filename);
    ~MorseTree();

    void insert(const string& code, Type letter);
    void clear();
    string encodeText(const string& text) const;
    string decodeText(const string& code) const;
};

#include "morse_tree.cpp"
#endif
