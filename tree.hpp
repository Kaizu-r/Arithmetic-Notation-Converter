#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<stdlib.h>
#include "tokenizer.hpp"


typedef struct node{
    Token tok;
    struct node* left;
    struct node* right;
}Node;

void preorder(Node *n){
    if(n == nullptr)
        return;
    printTokLiteral(n->tok);    ///print parent first
    preorder(n->left);
    preorder(n->right);
}

void inorder(Node* n){
    if(n== nullptr)
        return;
    inorder(n->left);   //exhaust left first
    printTokLiteral(n->tok);
    inorder(n->right);
}




#endif