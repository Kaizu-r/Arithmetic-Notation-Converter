#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "tokenizer.hpp"
#include "tree.hpp"
#include "parser.hpp"

using namespace std;

bool isValidCombo(const string& arg1, const string& arg2) {
    vector<pair<string, string>> validCombos = {
        {"infix", "prefix"}, {"prefix", "infix"},
        {"postfix", "prefix"}, {"prefix", "postfix"},
        {"infix", "postfix"}, {"postfix", "infix"}
    };

    for (const auto& combo : validCombos) {
        if ((arg1 == combo.first && arg2 == combo.second) ||
            (arg1 == combo.second && arg2 == combo.first)) {
            return true;
        }
    }
    return false;
}

void executeMethod(const string& arg1, const string& arg2, Node **root, Token *tok) {
    int start = 0;
    if (arg1 == "infix" && arg2 == "prefix" ) {
        cout << "[INFO] Using Infix and Prefix strategy\n";
        startInToTree(tok, &start, root);
        preorder(*root);
    } 

    else if (arg1 == "prefix" && arg2 == "infix") {
        cout << "[INFO] Using Prefix and Infix strategy\n";
        startPreToTree(tok, &start, root);
        inorder(*root);
        
    }
    
    else if (arg1 == "postfix" && arg2 == "prefix") {
        cout << "[INFO] Using Postfix and Prefix strategy\n";
        startPostToTree(tok, &start, root);
        preorder(*root);
    } 
    
    else if (arg1 == "prefix" && arg2 == "postfix") {
        cout << "[INFO] Using Prefix and Postfix strategy\n";
        startPreToTree(tok, &start, root);
        postorder(*root);
    } 
    
    else if (arg1 == "infix" && arg2 == "postfix")  {
        cout << "[INFO] Using Infix and Postfix strategy\n";
        startInToTree(tok, &start, root);
        postorder(*root);
    } 

    else if (arg1 == "postfix" && arg2 == "infix") {
        cout << "[INFO] Using Postfix and Infix strategy\n";
        startPostToTree(tok, &start, root);
        inorder(*root);
    } 
    
    else {
        cout << "[WARN] Unknown combination (should not happen if validated)\n";
    }
}

void printHelp() {
    cout << "\n/=====================================================\\\n";
    cout << "|              C++ Expression Parser Helper           |\n";
    cout << "\\=====================================================/\n\n";
    cout << "USAGE:\n";
    cout << "  ./program --from <arg1> --to <arg2> <string> [-e]\n\n";
    cout << "DESCRIPTION:\n";
    cout << "  A C++ terminal tool that accepts two argument flags to\n";
    cout << "  determine a printing method for the input string.\n\n";
    cout << "REQUIRED ARGUMENTS:\n";
    cout << "  <arg1> and <arg2> combinations (order DOES matter):\n";
    cout << "    infix    prefix    : Infix and Prefix strategy\n";
    cout << "    prefix   infix     : Prefix and Infix strategy\n";
    cout << "    postfix  prefix    : Postfix and Prefix strategy\n";
    cout << "    prefix   postfix   : Prefix and Postfix strategy\n";
    cout << "    infix    postfix   : Infix and Postfix strategy\n";
    cout << "    postfix  infix     : Postfix and Infix strategy\n\n";
    cout << "  <string>               : The exression to be OPERATED.\n\n";
    cout << "OPTIONAL ARGUMENT:\n";
    cout << "  -e                     : Emphasize output (convert to uppercase).\n\n";
    cout << "HELP:\n";
    cout << "  ./program -help        : Show this help message\n\n";
    cout << "=======================================================\n";
}

int main(int argc, char* argv[]) {
    //help
    if(argc == 1 || (argc == 2 && string(argv[1]) == "--help" || string(argv[1]) == "-h")) {
        printHelp();
        return 0;
    }

    //too many or too few arguments
    if (argc < 6){
        cerr << "[Error]: Too few arguments. Use ./converter --help for usage info" <<endl;
        return 1;
    }
    if(argc > 7){
        cerr << "[Error]: Too many arguments. Use ./converter --help for usage info" << endl;
    }

    //checks presence of "--from" and "--to"
    if(string(argv[1]) != "--from"){
        cerr << "[Error]: Missing --from argument. Use ./converter --help for usage info" <<endl;
        return 1;
    }
    if(string(argv[3]) != "--to"){
        cerr << "[Error]: Missing --to argument. Use ./converter --help for usage info" <<endl;
        return 1;
    }
    //store arguments
    string arg1 = argv[2];
    string arg2 = argv[4];
    string inputStr = argv[5];
    bool emphasize = false;
    

    //check if evaluation is emphasized
    if (argc == 7) {
        string flag = argv[6];
        if (flag == "-e") {
            emphasize = true;
        } else {
            cerr << "[Error]: Unknown flag: " << flag << "Use ./converter --help to check for valid flags" <<endl;
            return 1;
        }
    }

    //check if argument combinations are valid
    if (!isValidCombo(arg1, arg2)) {
        cerr << "[Error]: Invalid argument combination: " << arg1 << ", " << arg2 << endl;
        return 1;
    }

    //METHOD FOR ARGS 1-4
    Error e = NO_ERR;
    Node* root = NULL;
    Token tok[inputStr.length()];
    tokenize(tok, inputStr, &e);
    if(e != NO_ERR){
        cout << "[Error]: Invalid symbols. Use ./converter --guide for more information" <<endl;
        return 0;
    }

    int i = 0;
    if(!isValid(tok, &i, arg1)){
        cout<< "[Error]: Invalid syntax of input string" << endl;
        return 0;
    }

    executeMethod(arg1, arg2, &root, tok);

    //WHERE TO PUT THE EVALUTE OPERATION WHEN THERE'S AN ARG 5
    if (emphasize) {
        cout <<endl<< "Evaluating expression:\n";
        float res = evaluate(root, &e);
        if(e != NO_ERR){
            cout << "[Error]: Invalid Operation (Dividing by zero)" <<endl;
            return 0;
        }
        cout << "Result: " << res <<endl;
    }

    //cout << inputStr << endl;

    return 0;
}
