#ifndef CONVERT_H
#define CONVERT_H

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
    RIGHT_p,
    END
}Token;


void removeSpace(std::string str){
    str.erase(remove(str.begin(), str.end(), isspace), str.end());
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
}
void tokenize(Token *t, float* nums, std::string str){
    int num_top = -1;
    int token_top = -1;

    int i = 0;
    while(i < str.length()){
        if(isDigit(str.at(i))){
            int begin = i;
            int end = i;
            while(i+1<str.length() && isDigit(str.at(i+1)))
                end = ++i;
            nums[++num_top] = toInt(str, begin, end); 
            t[++token_top] = DIGIT;

            //need to add float part here or maybe on different if
        }
        else if(isOperator(str.at(i)))
            t[++token_top] = toOperator(str.at(i));
        else if(str.at(i) == '(')
            t[++token_top] = LEFT_P;
        else if(str.at(i) == ')')
            t[++token_top] = RIGHT_p;
        i++;
    }
    t[++token_top] = END;
}




#endif