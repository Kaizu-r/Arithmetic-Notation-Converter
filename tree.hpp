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

Node* createNode(Token tok){
    Node *n = (Node*) malloc(sizeof(Node));
    n->tok = tok;
    n->left = nullptr;
    n->right = nullptr;

    return n;
}


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

void postorder(Node* n){
    if(n == nullptr)
        return;
    postorder(n->left); //exhaust left first
    postorder(n->right);    //exhaust right
    printTokLiteral(n->tok);
}

//populate the tree based on operation
void preToTree(Token *t, int *curr, Node** root){
    if(t[*curr].t == END)
        return;
    if(t[*curr].t == DIGIT || t[*curr].t == VAR){
        *root = createNode(t[*curr]);
        (*curr)++;
        return;
    }
    *root = createNode(t[*curr]);
    (*curr)++;
    preToTree(t, curr, &((*root)->left));
    preToTree(t, curr, &((*root)->right));

}

void postToTree(Token *t, int *curr, Node **root){
    if(t[*curr].t == END)
        return;
    if(t[*curr].t == DIGIT || t[*curr].t == VAR){
        *root = createNode(t[*curr]);
        (*curr)++;
        return;
    }
    *root = createNode(t[*curr]);   //initialize root with temporary token
    (*curr)++;
    postToTree(t, curr, &((*root)->left));
    postToTree(t, curr, &((*root)->right));
    (*root)->tok = t[*curr];    //reassign with new token


}

#endif