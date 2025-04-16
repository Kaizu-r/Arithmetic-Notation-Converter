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
    
    //reprint it
    i = 0;
    int j = 0, k = 0, l = 0;
    while(t[i] != END){
        if(t[i] == DIGIT){
            std::cout << num[j++] << ' ';
        }
        else if(t[i] == COEFFICIENT)
            std::cout << coeff[k++];
        else if(t[i] == VAR)
            std::cout << var[l++] << ' ';
        else
            printTok(t[i]);
        i++;
    }
    
}