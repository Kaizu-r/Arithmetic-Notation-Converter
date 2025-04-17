#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <stdlib.h>
#include "tokenizer.hpp"

typedef struct node{
    Token t;
    struct node* left;
    struct node* right;
}Node;

int precedence(Token t){
    switch(t){
        case ADD:
        case SUBTRACT:
            return 1;
        case MULTIPLY:
        case DIVIDE:
        case MOD:
            return 2;
        default:
            return 3;
    }
}

int isTokOperator(Token t){
    switch(t){
        case ADD:
        case SUBTRACT:
        case DIVIDE:
        case MULTIPLY:
        case POW:
        case MOD:
            return 1;
    }
    return 0;
}

void inToPost(Token *t, float *nums, float *coeff, Token* queue){

    Token tokStack[100];

    int negative_flag = 1;

    int rear, tok_top, nums_curr, coeff_curr;
    nums_curr = -1;
    coeff_curr = -1;
    tok_top = -1;
    rear = -1;

    while(*t != END){
        if(*t == DIGIT || *t == COEFFICIENT){
            if(*t == DIGIT){    //push first digit
                nums[++nums_curr]*= negative_flag; 
                queue[++rear] = DIGIT;
                t++;
            }
            else{
                coeff[++coeff_curr] *= negative_flag;
                queue[++rear] = COEFFICIENT;
                queue[++rear] = VAR;
                t+=2;
            }
            negative_flag = 1;
        }
        else if(isTokOperator(*t)){
            if(*t == SUBTRACT && rear > -1 && *(t-1) != VAR && *(t-1) != DIGIT ){   //previous token is not a number, therefore subtract is negative sign
                negative_flag = -1;
            }
            else{
                while(tok_top > -1 && tokStack[tok_top] != LEFT_P && (precedence(tokStack[tok_top]) >= precedence(*t)) && *t != POW){
                    queue[++rear] = tokStack[tok_top--];    //pop and push everythign to queue
                }
                tokStack[++tok_top] = *t;
                t++;
            }
        }
        else if(*t == LEFT_P){
            tokStack[++tok_top] = LEFT_P;
            t++;
        }
        else if(*t == RIGHT_P){
            while(tok_top > -1 && tokStack[tok_top] != LEFT_P){
                queue[++rear] = tokStack[tok_top--]; //pop everything to queue
            }
            if(tok_top != -1)
                tok_top--;
            t++;
        }
    }
    while(tok_top > -1)
        queue[++rear] = tokStack[tok_top--];    //pop the rest of it
    queue[++rear] = END;
}

void freeTree(Node **r){
    if(*r == NULL)
        return;
    freeTree(&(*r)->left);
    freeTree(&(*r)->right);
}

Node* createNode(Token t){

}

#endif