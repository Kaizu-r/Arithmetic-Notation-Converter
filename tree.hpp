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
    if(n== nullptr){
        return;
    }
    if(n->left != nullptr && isTokOperator(n->left->tok.t)){
        printf("( ");
        inorder(n->left);   //exhaust left first
        printf(") ");
    }
    else
        inorder(n->left);
    printTokLiteral(n->tok);
    if(n->right != nullptr && isTokOperator(n->right->tok.t)){
        printf("( ");
        inorder(n->right);
        printf(") ");
    }
    else
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
    Node* stack[100];
    int top = -1;

    while(t[*curr].t != END){
        if(t[*curr].t == DIGIT || t[*curr].t == VAR)
            stack[++top] = createNode(t[*curr]);
        else{   //operator
            Node *n = createNode(t[*curr]);
            if(top > -1)
                n->right = stack[top--];
            if(top > -1)
                n->left = stack[top--];
            
            stack[++top] = n;

        }
        (*curr)++;
    }
    if(top == 0)
        *root = stack[top];
}

//similar to shunting yard
void inToTree(Token *t, int *curr, Node **root){
    Token op[100];
    Token temp[100];
    int op_top = -1;
    int temp_top = -1;
    *root = createNode(t[*curr]);   //temporary contents

    while(t[*curr].t != END){
        if(t[*curr].t == DIGIT || t[*curr].t == VAR)
            temp[++temp_top] = t[*curr]; //put to stack
        else if(isTokOperator(t[*curr].t)){
            while(op_top > -1 && op[op_top].t != LEFT_P && precedence(op[op_top].t) >= precedence(t[*curr].t)){
                temp[++temp_top] = op[op_top--];
            }
            op[++op_top] = t[*curr];
        }
        else if(t[*curr].t == LEFT_P){
            op[++op_top] = t[*curr];
        }
        else if(t[*curr].t == RIGHT_P){
            while(op_top > -1 && op[op_top].t != LEFT_P)
                temp[++temp_top] = op[op_top--];
            if(op_top > -1)
                op_top--;   //removes left_p
        }
        (*curr)++;
    }
    while(op_top > -1){
        if(op[op_top].t != LEFT_P)
            temp[++temp_top] = op[op_top--];
        else
            op_top--;
    }
    temp[++temp_top].t = END;

    postToTree(temp, 0, root);


    


}
//calls the preToTree
void startPreToTree(Token *t, int *curr, Node **root){
    preToTree(t, curr, root);
}

//starts the inToTree
void startIntToTree(Token *t, int *curr, Node **root){
    inToTree(t, curr, root);
}

//starts the postToTree
void startPostToTree(Token *t, int *curr, Node **root){
    postToTree(t, curr, root);  
}

#endif