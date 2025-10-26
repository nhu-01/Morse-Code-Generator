#ifndef NODE_H
#define NODE_H

// DO NOT MODIFY THIS FILE

template<typename Type>
class Node
{
public:
    Type data;
    Node* left;
    Node* right;

    Node(Type value) : data(value), left(nullptr), right(nullptr) {}
};

#endif

