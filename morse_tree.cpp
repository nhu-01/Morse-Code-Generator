#include "morse_tree.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>
#include "morse_tree.h"
using namespace std;

// place your code here
//initial/default constructor
template<typename Type> //placeholder for char datatupe
MorseTree<Type>::MorseTree(){
    root = new Node<Type>('\0'); //initialize
}

//build constructor from file
template<typename Type>
MorseTree<Type>::MorseTree(const string& filename) :MorseTree(){
    ifstream file(filename); //read the file name
    if (!file) return; //exit if file failed to open

    string line;

    //read each line
    while (getline(file, line)){
        stringstream ss(line); //treat as input stream
        string letter_val;
        string code;
        if (getline(ss, letter_val, ',') && getline(ss, code)){
            Type letter = letter_val[0];
            insert(code, letter);
        }
    }
}

// Destructor
template<typename Type>
MorseTree<Type>::~MorseTree(){
    clear(); //clear child nodes
    delete root;// clear root node
}

//recursive insert
template<typename Type>
void MorseTree<Type>::insert(Node<Type>* node, const string& code, Type letter, size_t index){
    if (index == code.size()){
        node ->data = letter;
        return;
    }

    //move left when dot
    if (code[index] == '.') {
        if (!node->left) node->left = new Node<Type>('\0');
        insert(node->left, code, letter, index + 1);
    }   else if (code[index] == '-') {
            if (!node->right) node->right = new Node<Type>('\0');
            insert(node->right, code, letter, index + 1);
        }

    }

//insert
template<typename Type>
void MorseTree<Type>::insert(const string& code, Type letter){
    insert(root, code, letter, 0);
}

//recursive clear
template<typename Type>
void MorseTree<Type>::clear(Node<Type>*node){
    if (!node) return;
    //clear child nodes
    clear(node->left);
    clear(node->right);
    delete node;
}

//clear
template<typename Type>
void MorseTree<Type>::clear(){
    clear(root->left);
    clear(root->right);
    root->left = root->right = nullptr; //null
    root->data = '\0';
}

//recursive encodeLetter
template<typename Type>
bool MorseTree<Type>::encodeLetter(Node<Type>* node, Type letter, string code, string& result) const { 
    //base case
    //if node doesn't exist
    if (!node) return false;
    if (node->data == letter){
        result = code;
        return true;
    }

    //dot
    if (encodeLetter(node->left, letter, code + ".", result)) return true;
    //dash
    if (encodeLetter(node->right, letter, code + "-", result)) return true;

    return false;

}

//encodeText
template<typename Type>
string MorseTree<Type>::encodeText(const string& text) const{
    string morse_code = "";
    
    for (char ch : text){
        //convert space
        if (ch == ' '){
            morse_code += " / ";
        } else {
            string code;
            if (!encodeLetter(root, toupper(ch), "", code)) code = ""; //convert lowercase to uppercase
            morse_code += code + " ";
        }
    }
    return morse_code;
}

//decodeLetter
template<typename Type>
Type MorseTree<Type>::decodeLetter(const string& code) const{
    Node<Type>* current = root;
    for (char ch: code){
        if (!current) return '?'; //no . or -
        if (ch == '.') current = current->left;
        else if (ch == '-') current = current->right;
        else return '?';
    }
    if (!current || current->data == '\0') return '?'; //empty
    return current->data;
}

//decodeText
template<typename Type>
string MorseTree<Type>::decodeText(const string& code) const {
    string result = ""; //initialize result
    stringstream ss(code);
    string token;
    while (ss >> token) {
        if (token == "/") result += " ";//add space
        else result += decodeLetter(token);
    }

    return result;
}
// explicit template instantiation
template class MorseTree<char>;
