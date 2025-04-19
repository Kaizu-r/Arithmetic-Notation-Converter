#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <stdlib.h>
#include "tokenizer.hpp"


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
    Token ops[100];
    Token temp_stack[100];
    int tempTop = -1;
    int rear = -1;
    int oTop = -1;
    
    while(t->t != END){
        if(t->t == DIGIT)
            temp_stack[++tempTop] = *t;
        else if(t->t == COEFFICIENT){
            temp_stack[++tempTop] = *(t++);
            temp_stack[++tempTop] = *t;
        }
        else if(isTokOperator(t->t)){
            Token op = *t;
            Token left[100];
            Token right[100];
            int left_top, right_top;
            left_top = right_top = -1;
            //get left and right operands
            if(temp_stack[tempTop].t == RIGHT_P){
                int flag = -1;
                do{
                    right[++right_top] = temp_stack[tempTop--];
                    if(temp_stack[tempTop].t == LEFT_P)
                        flag++;
                    else if(temp_stack[tempTop].t == RIGHT_P)
                        flag--;
                }while(flag != 0);
            }
            right[++right_top] = temp_stack[tempTop--];
            if(temp_stack[tempTop].t == RIGHT_P){
                int flag = -1;
                do{
                    left[++left_top] = temp_stack[tempTop--];
                    if(temp_stack[tempTop].t == LEFT_P)
                        flag++;
                    else if(temp_stack[tempTop].t == RIGHT_P)
                        flag--;
                }while(flag != 0);
            }
            left[++left_top] = temp_stack[tempTop--];

            //store expr in temp_stack
            temp_stack[++tempTop].t = LEFT_P;
            while(left_top > -1)
                temp_stack[++tempTop] = left[left_top--];
            temp_stack[++tempTop] = op;
            while(right_top > -1)
                temp_stack[++tempTop] = right[right_top--];
            temp_stack[++tempTop].t = RIGHT_P;
            
        }
        t++;
    }


    //copy the rest, skip first parenthesis
    for(int i = 1; i < tempTop; i++)
        queue[++rear] = temp_stack[i];
    queue[++rear].t = END;

}







#endif