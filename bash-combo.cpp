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
        {"-in", "-pre"}, {"-pre", "-in"},
        {"-pos", "-pre"}, {"-pre", "-pos"},
        {"-in", "-pos"}, {"-pos", "-in"}
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
    if (arg1 == "-in" && arg2 == "-pre" ) {
        cout << "[INFO] Using Infix and Prefix strategy\n";
        startInToTree(tok, &start, root);
        preorder(*root);
    } 

    else if (arg1 == "-pre" && arg2 == "-in") {
        cout << "[INFO] Using Prefix and Infix strategy\n";
        startPreToTree(tok, &start, root);
        inorder(*root);
        
    }
    
    else if (arg1 == "-pos" && arg2 == "-pre") {
        cout << "[INFO] Using Postfix and Prefix strategy\n";
        startPostToTree(tok, &start, root);
        preorder(*root);
    } 
    
    else if (arg1 == "-pre" && arg2 == "-pos") {
        cout << "[INFO] Using Prefix and Postfix strategy\n";
        startPreToTree(tok, &start, root);
        postorder(*root);
    } 
    
    else if (arg1 == "-in" && arg2 == "-pos")  {
        cout << "[INFO] Using Infix and Postfix strategy\n";
        startInToTree(tok, &start, root);
        postorder(*root);
    } 

    else if (arg1 == "-pos" && arg2 == "-in") {
        cout << "[INFO] Using Postfix and Infix strategy\n";
        startPostToTree(tok, &start, root);
        inorder(*root);
    } 
    
    else {
        cout << "[WARN] Unknown combination (should not happen if validated)\n";
    }
}

void printHelp() {
    cout << "\n╔══════════════════════════════════════════════════════╗\n";
    cout << "║              C++ Expression Parser Helper            ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n\n";
    cout << "USAGE:\n";
    cout << "  ./program <arg1> <arg2> <string> [-e]\n\n";
    cout << "DESCRIPTION:\n";
    cout << "  A C++ terminal tool that accepts two argument flags to\n";
    cout << "  determine a printing method for the input string.\n\n";
    cout << "REQUIRED ARGUMENTS:\n";
    cout << "  <arg1> and <arg2> combinations (order DOES matter):\n";
    cout << "    -in   -pre     → Infix and Prefix strategy\n";
    cout << "    -pre  -in      → Prefix and Infix strategy\n";
    cout << "    -pos  -pre     → Postfix and Prefix strategy\n";
    cout << "    -pre  -pos     → Prefix and Postfix strategy\n";
    cout << "    -in   -pos     → Infix and Postfix strategy\n";
    cout << "    -pos  -in      → Postfix and Infix strategy\n\n";
    cout << "  <string>         : The exression to be OPERATED.\n\n";
    cout << "OPTIONAL ARGUMENT:\n";
    cout << "  -e               : Emphasize output (convert to uppercase).\n\n";
    cout << "HELP:\n";
    cout << "  ./program -help  : Show this help message\n\n";
    cout << "════════════════════════════════════════════════════════\n";
}

int main(int argc, char* argv[]) {
    if (argc == 2 && string(argv[1]) == "-help") {
        printHelp();
        return 0;
    }

    if (argc < 4 || argc > 5) {
        cerr << "Invalid arguments. Use './program -help' for usage info.\n";
        return 1;
    }

    string arg1 = argv[1];
    string arg2 = argv[2];
    string inputStr = argv[3];
    bool emphasize = false;

    if (argc == 5) {
        string flag = argv[4];
        if (flag == "-e") {
            emphasize = true;
        } else {
            cerr << "Unknown flag: " << flag << endl;
            return 1;
        }
    }

    if (!isValidCombo(arg1, arg2)) {
        cerr << "Invalid argument combination: " << arg1 << ", " << arg2 << endl;
        return 1;
    }

    //METHOD FOR ARGS 1-4
    Error e = NO_ERR;
    Node* root = NULL;
    Token tok[inputStr.length()];
    tokenize(tok, inputStr, &e);
    if(e != NO_ERR){
        cout << "Error: Invalid symbols" <<endl;
        return 0;
    }

    int i = 0;
    if(!isValid(tok, &i, arg1)){
        cout<< "Invalid syntax of input string" << endl;
        return 0;
    }

    executeMethod(arg1, arg2, &root, tok);

    //WHERE TO PUT THE EVALUTE OPERATION WHEN THERE'S AN ARG 5
    if (emphasize) {
        cout <<endl<< "Evaluating expression:\n";
        float res = evaluate(root, &e);
        if(e != NO_ERR){
            cout << "Invalid Operation (Dividing by zero)" <<endl;
            return 0;
        }
        cout << "Result: " << res <<endl;
    }

    //cout << inputStr << endl;

    return 0;
}
