#include<iostream>
#include "tokenizer.hpp"
#include "tree.hpp"

int main(){
    std::string str;
    std::cout << "ENTER: ";
    std::getline(std::cin, str);

    //removeSpace(str);
    Token *t;
    
    tokenize(t, str);
    int i = 0;
    while(t[i].t != END)
        printTok(t[i++].t);
    Node *root = NULL;
    i = 0;
    
    startIntToTree(t, &i, &root);

    std::cout << std::endl;
    preorder(root);
    std::cout << std::endl;
    inorder(root);
    std::cout << std::endl;
    postorder(root);

    //inorder(root);


    
}