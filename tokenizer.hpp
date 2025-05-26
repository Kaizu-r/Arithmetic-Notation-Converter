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
    END
}Token_t;

typedef enum{
    TOK_ERR,
    SYNTAX_ERR,
    EVAL_ERR,
}Error;

typedef struct tok{
    Token_t t;
    float val;
} Token;

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

int precedence(Token_t t){
    switch(t){
        case ADD:
        case SUBTRACT:
            return 1;
        case MULTIPLY:
        case DIVIDE:
            return 2;
        case POW:
            return 3;
        default:
            return 0;
    }
}

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

Token_t toOperator(char c){
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
void tokenize(Token *t, std::string str){
    int token_top = -1;

    int i = 0;
    while(i < str.length() && str.at(i) != '\n'){
        if(isDigit(str.at(i))){
            int begin = i;
            int end = i;
            while(i+1<str.length() && isDigit(str.at(i+1)))
                end = ++i;
            float num = toInt(str, begin, end); 
            t[++token_top].t = DIGIT;
            t[token_top].val = num;
                

        }
        else if(isOperator(str.at(i)))
            t[++token_top].t = toOperator(str.at(i));
        else if(str.at(i) == '(')
            t[++token_top].t = LEFT_P;
        else if(str.at(i) == ')')
            t[++token_top].t = RIGHT_P;
        i++;
    }
    t[++token_top].t = END;
}

void printTok(Token_t t){
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
        case END:
            std::cout << "END";
            break;
    }
    std::cout << ' ';
}

void printTokLiteral(Token t){
    switch(t.t){
        case DIGIT:
            std::cout << (int) t.val;
            break;
        case ADD:
            std::cout << '+';
            break;
        case SUBTRACT:
            std::cout << '-';
            break;
        case DIVIDE:
            std::cout << '/';
            break;
        case MULTIPLY:
            std::cout << '*';
            break;
        case POW:
            std::cout << '^';
            break;
        case MOD:
            std::cout << '%';
            break;
        case LEFT_P:
            std::cout << '(';
            break;
        case RIGHT_P:
            std::cout << ')';
            break;
        case END:
            std::cout << "END";
            break;
    }
    std::cout << ' ';
}

#endif