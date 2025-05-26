#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <stdlib.h>
#include "tokenizer.hpp"

/*
production rules
arith -> term arith_pos
arith_pos -> + term arith_pos | - term arith_pos | e
term -> factor term_pos
term_pos -> * factor term_pos | / factor term_pos | e
factor -> digit | (arith) | - digit
*/
bool arith(Token* q, int *curr);
bool arith_pos(Token* q, int* curr);
bool term(Token* q, int* curr);
bool term_pos(Token* q, int* curr);
bool factor(Token* q, int *curr);
bool posexpr(Token* q, int *curr);
bool posexpr_pos(Token* q, int *curr);

bool isValid(Token* q, int* curr, std::string arg);

bool arith(Token* q, int *curr){
    if(term(q, curr)){
        if(arith_pos(q, curr))
            return true;
        return false;
    }
    return false;
}

bool arith_pos(Token* q, int* curr){
    if(q[*curr].t == ADD || q[*curr].t == SUBTRACT){
        (*curr)++;
        if(term(q,curr)){
            if(arith_pos(q, curr))
                return true;
            return false;
        }
        return false;
    }
    return true;
}

bool term(Token* q, int* curr){
    if(factor(q, curr)){
        if(term_pos(q, curr))
            return true;
        return false;
    }
    return false;
}

bool term_pos(Token* q, int* curr){
    if(q[*curr].t == MULTIPLY || q[*curr].t == DIVIDE){
        (*curr)++;
        if(factor(q, curr)){
            if(term_pos(q, curr))
                return true;
            return false;
        }
        return false;
    }
    return true;

}


bool factor(Token* q, int *curr){
    if(q[*curr].t == SUBTRACT){
        (*curr)++;
        if(q[*curr].t == DIGIT){
            (*curr)++;
            return true;
        }
        return false;
    }
    else if(q[*curr].t == DIGIT){
        (*curr)++;
        return true;
    }
    else if(q[*curr].t == LEFT_P){
        (*curr)++;
        if(arith(q, curr)){
            if(q[*curr].t == RIGHT_P){
                (*curr)++;
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

/*
posexpr-> digit posexpr_pos
posexpr_pos -> posexpr ops | e
*/

bool posexpr(Token*q, int *curr){
    if(q[*curr].t == DIGIT){
        (*curr)++;
        if(posexpr_pos(q, curr))
            return true;
        return false;
    }
    return false;
}

bool posexpr_pos(Token *q, int *curr){
    if(posexpr(q, curr)){
        if(isTokOperator(q[*curr].t)){
            (*curr)++;
            return true;
        }
        return false;
    }
    return true;
}



#endif