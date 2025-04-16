#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<iostream>
#include<algorithm>

typedef enum {
    DIGIT,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    POW,
    MOD,
    LEFT_P,
    RIGHT_P,
    VAR,
    COEFFICIENT,
    END
}Token;


void removeSpace(std::string str){
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

int isDigit(char c){
    switch(c){
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return 1;
    }
    return 0;
}

int toInt(std::string str, int start, int end){
    int n = 0;
    for(int i = 0, factor = 1; i <= end - start; i++, factor*=10){
        n += factor * (str.at(start + i) - 48);
    }
    return n;
}

int isOperator(char c){
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            return 1;
    }
    return 0;
}

Token toOperator(char c){
    switch(c){
        case '+':
            return ADD;
        case '-':
            return SUBTRACT;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        case '^':
            return POW;
        case '%':
            return MOD;
    }
    return END;
}

int isVar(char c){
    if(c >= 65 && c <= 90)  //BIG LETTER
        return 1;
    if(c >= 97 && c <= 122) //small letter
        return 1;
    return 0;
}
void tokenize(Token *t, float* nums, float* coeff, char *var,  std::string str){
    int num_top = -1;
    int token_top = -1;
    int var_top = -1;
    int coeff_top = -1;

    int i = 0;
    while(i < str.length()){
        if(isDigit(str.at(i))){
            int begin = i;
            int end = i;
            while(i+1<str.length() && isDigit(str.at(i+1)))
                end = ++i;
            int num = toInt(str, begin, end); 

            //need to add float part here or maybe on different if

            if(i + 1 < str.length() && isVar(str.at(i+1))){
                coeff[++coeff_top] = num;
                var[++var_top] = str.at(++i);
                t[++token_top] = COEFFICIENT;
                t[++token_top] = VAR;
            }
            else{
                t[++token_top] = DIGIT;
                nums[++num_top] = num; 
            }
                

        }
        else if(isVar(str.at(i))){
            coeff[++coeff_top] = 1;
            var[++var_top] = str.at(i);
            t[++token_top] = COEFFICIENT;
            t[++token_top] = VAR;
        }
        else if(isOperator(str.at(i)))
            t[++token_top] = toOperator(str.at(i));
        else if(str.at(i) == '(')
            t[++token_top] = LEFT_P;
        else if(str.at(i) == ')')
            t[++token_top] = RIGHT_P;
        i++;
    }
    t[++token_top] = END;
}

void printTok(Token t){
    switch(t){
        case DIGIT:
            std::cout << "DIGIT";
            break;
        case ADD:
            std::cout << "ADD";
            break;
        case SUBTRACT:
            std::cout << "SUBTRACT";
            break;
        case DIVIDE:
            std::cout << "DIVIDE";
            break;
        case MULTIPLY:
            std::cout << "MULTIPLY";
            break;
        case POW:
            std::cout << "POW";
            break;
        case MOD:
            std::cout << "MOD";
            break;
        case LEFT_P:
            std::cout << "LEFT_P";
            break;
        case RIGHT_P:
            std::cout << "RIGHT_P";
            break;
        case VAR:
            std::cout << "VAR";
            break;
        case COEFFICIENT:
            std::cout << "COEFFICIENT";
            break;
        case END:
            std::cout << "END";
            break;
    }
    std::cout << ' ';
}



#endif