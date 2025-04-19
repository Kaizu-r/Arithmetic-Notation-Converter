#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <stdlib.h>
#include "tokenizer.hpp"

typedef struct node{
    Token_t t;
    struct node* left;
    struct node* right;
}Node;

int precedence(Token_t t){
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

int isTokOperator(Token_t t){
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

void inToPost(Token *t, Token* queue){

    Token tokStack[100];

    int negative_flag = 1;

    int rear, tok_top; 

    tok_top = -1;
    rear = -1;

    while(t->t != END){
        if(t->t == DIGIT || t->t == COEFFICIENT){
            if(t->t == DIGIT){    //push first digit
                queue[++rear].t = DIGIT;
                queue[rear].val = negative_flag * t->val; 
                
                t++;
            }
            else{
                queue[++rear].t = COEFFICIENT;
                queue[rear].val = negative_flag * t->val;

                t++;
                queue[++rear].t = VAR;
                queue[rear].val = t->val;

                t++;
            }
            negative_flag = 1;
        }
        else if(isTokOperator(t->t)){
            if(t->t == SUBTRACT && rear > -1 && (t-1)->t != VAR && (t-1)->t != DIGIT ){   //previous token is not a number, therefore subtract is negative sign
                negative_flag = -1;
            }
            else{
                while(tok_top > -1 && tokStack[tok_top].t != LEFT_P && (precedence(tokStack[tok_top].t) >= precedence(t->t)) && t->t != POW){
                    queue[++rear] = tokStack[tok_top--];    //pop and push everythign to queue
                }
                tokStack[++tok_top] = *t;
                t++;
            }
        }
        else if(t->t == LEFT_P){
            tokStack[++tok_top].t = LEFT_P;
            t++;
        }
        else if(t->t == RIGHT_P){
            while(tok_top > -1 && tokStack[tok_top].t != LEFT_P){
                queue[++rear] = tokStack[tok_top--]; //pop everything to queue
            }
            if(tok_top != -1)
                tok_top--;
            t++;
        }
    }
    while(tok_top > -1)
        queue[++rear] = tokStack[tok_top--];    //pop the rest of it
    queue[++rear].t = END;
}

void postToIn(Token *t,  Token* queue){
    Token digits[100];
    Token ops[100];
    Token temp_stack[100];
    int tempTop = -1;    
    int dTop, oTop, qRear;


    dTop= oTop = qRear = -1;

    while(t->t != END){
        if(t->t == DIGIT || t->t == COEFFICIENT){
            if(t->t == COEFFICIENT){
                digits[++dTop] = *t;
                t++;
            }
            digits[++dTop] = *t;
            t++;
        }
        else if(isTokOperator(t->t)){
            Token op = *t;
            if(oTop > -1 && (precedence(op.t) > precedence(ops[oTop].t))){
                temp_stack[++tempTop].t = RIGHT_P;
                //while(oTop >-1 && precedence(op.t) > precedence(ops[oTop].t)){
                    if(digits[dTop].t == VAR){
                        temp_stack[++tempTop] = digits[dTop--];
                    }
                    temp_stack[++tempTop] = digits[dTop--];
                    temp_stack[++tempTop] = ops[oTop--];
                //}
                if(digits[dTop].t == VAR){
                    temp_stack[++tempTop] = digits[dTop--];
                }
                temp_stack[++tempTop] = digits[dTop--];
                temp_stack[++tempTop].t = LEFT_P;
                temp_stack[++tempTop] = op;


            }
            else
                ops[++oTop] = op;
    
            t++;
        }
    }
    //copy remaining
    while(dTop > 0){
        if(digits[dTop].t == VAR){
            temp_stack[++tempTop] = digits[dTop--];
        }
        temp_stack[++tempTop] = digits[dTop--];
        if(oTop > -1){
            Token op = ops[oTop];
            while(oTop > 0 && precedence(op.t) < precedence(ops[oTop-1].t)){
                temp_stack[++tempTop] = ops[--oTop];
                if(digits[dTop].t == VAR){
                    temp_stack[++tempTop] = digits[dTop--];
                }
                temp_stack[++tempTop] = digits[dTop--];
            }
            temp_stack[++tempTop] = op;
            oTop--;
        }
    }
    if(dTop > -1)
        temp_stack[++tempTop] = digits[dTop];
    

    //push temp_stack to queue
    while(tempTop > -1)
        queue[++qRear] = temp_stack[tempTop--];
    queue[++qRear].t = END;
}

void freeTree(Node **r){
    if(*r == NULL)
        return;
    freeTree(&(*r)->left);
    freeTree(&(*r)->right);
}





#endif