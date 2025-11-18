#include "morse_tree.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>
using namespace std;

// Default constructor
template<typename Type>
MorseTree<Type>::MorseTree() {
    root = new Node<Type>('\0');
}

// Build tree from file
template<typename Type>
MorseTree<Type>::MorseTree(const string& filename) : MorseTree() {
    ifstream file(filename);
    if (!file) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string letter_val, code;
        if (getline(ss, letter_val, ',') && getline(ss, code)) {
            Type letter = letter_val[0];
            insert(code, letter);
        }
    }
}

// Destructor
template<typename Type>
MorseTree<Type>::~MorseTree() {
    clear();
    delete root;
}

// Recursive insert
template<typename Type>
void MorseTree<Type>::insert(Node<Type>* node, const string& code, Type letter, size_t index) {
    if (index == code.size()) {
        node->data = letter;
        return;
    }
    if (code[index] == '.') {
        if (!node->left) node->left = new Node<Type>('\0');
        insert(node->left, code, letter, index + 1);
    } else if (code[index] == '-') {
        if (!node->right) node->right = new Node<Type>('\0');
        insert(node->right, code, letter, index + 1);
    }
}

// Insert wrapper
template<typename Type>
void MorseTree<Type>::insert(const string& code, Type letter) {
    insert(root, code, letter, 0);
}

// Recursive clear
template<typename Type>
void MorseTree<Type>::clear(Node<Type>* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Clear wrapper
template<typename Type>
void MorseTree<Type>::clear() {
    clear(root->left);
    clear(root->right);
    root->left = root->right = nullptr;
    root->data = '\0';
}

// Recursive encode
template<typename Type>
bool MorseTree<Type>::encodeLetter(Node<Type>* node, Type letter, string code, string& result) const {
    if (!node) return false;
    if (node->data == letter) {
        result = code;
        return true;
    }
    if (encodeLetter(node->left, letter, code + ".", result)) return true;
    if (encodeLetter(node->right, letter, code + "-", result)) return true;
    return false;
}

// Encode text
template<typename Type>
string MorseTree<Type>::encodeText(const string& text) const {
    string morse_code = "";
    for (char ch : text) {
        if (ch == ' ') {
            morse_code += "/ ";
        } else {
            string code;
            if (!encodeLetter(root, toupper(ch), "", code)) {
                code = "?"; // unknown character
            }
            morse_code += code + " ";
        }
    }
    return morse_code;
}

// Decode single letter
template<typename Type>
Type MorseTree<Type>::decodeLetter(const string& code) const {
    Node<Type>* current = root;
    for (char ch : code) {
        if (ch == '.') current = current->left;
        else if (ch == '-') current = current->right;
        else return '?';
        if (!current) return '?';
    }
    if (!current || current->data == '\0') return '?';
    return current->data;
}

// Decode text
template<typename Type>
string MorseTree<Type>::decodeText(const string& code) const {
    string result = "";
    string token = "";

    for (size_t i = 0; i < code.size(); ++i) {
        char ch = code[i];

        if (ch == '.' || ch == '-') {
            token += ch; // build Morse letter
        } else if (ch == ' ') {
            if (!token.empty()) {
                result += decodeLetter(token);
                token = "";
            }
        } else if (ch == '/') {
            if (!token.empty()) {
                result += decodeLetter(token);
                token = "";
            }
            result += " "; // word separator
        } else {
            // ignore invalid characters
        }
    }

    if (!token.empty()) {
        result += decodeLetter(token);
    }

    return result;
}

// Explicit template instantiation
template class MorseTree<char>;
