#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include "tokenizer.hpp"

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

void inToPost(Token *t, float *nums, float *coeff, char *var, Token* queue){
    float numStack[100];
    float coeffStack[100];
    char varStack[100];

    int nums_top, coeff_top, var_top;
    nums_top = -1;
    coeff_top = -1;
    var_top = -1;

    while(*t != END){

    }
}



#endif