#include<iostream>
#include "convert.hpp"

int main(){
    std::string str;
    std::cout << "ENTER: ";
    std::getline(std::cin, str);
    
    removeSpace(str);
    Token t[100];
    float num[100];
    float coeff[100];
    char var[100];

    tokenize(t, num, coeff, var, str);

    int i = 0;
    while(t[i] != END)
        printTok(t[i++]);
    
}