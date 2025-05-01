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
    printTokLiteral(n->tok);    ///print parent first
    preorder(n->left);
    preorder(n->right);
}





#endif