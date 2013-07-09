#include "infixExpression.h"
#include <string>
#include <vector>
using namespace std;
string calculator::infixToPostfix(const string &infixExpression) {
    vector<string> operators;
    string parament, postfixExpression;
    for (int i = 0; ; i++)
        switch (infixExpression[i]) {
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
            case '.':
                parament += infixExpression[i];
                break;
            default:
                if (parament != "")
                    postfixExpression += parament + ':';
                parament = "";
                switch (infixExpression[i]) {
                    case '+':
                    case '-':
                        while (!operators.empty() && operators.back() != "(") {
                            postfixExpression += operators.back() + ':';
                            operators.pop_back();
                        }
                        operators.push_back(string("") + infixExpression[i]);
                        break;
                    case '(':
                        operators.push_back("(");
                        break;
                    case '*':
                    case '/':
                        while (!operators.empty() && operators.back() != "(" && operators.back() != "+" && operators.back() != "-") {
                            postfixExpression += operators.back() + ':';
                            operators.pop_back();
                        }
                        operators.push_back(string("") + infixExpression[i]);
                        break;
                    case ')':
                        while (operators.back() != "(") {
                            postfixExpression += operators.back() + ':';
                            operators.pop_back();
                        }
                        operators.pop_back();
                        break;
                    case '\0':
                        while (!operators.empty()) {
                            postfixExpression += operators.back() + ':';
                            operators.pop_back();
                        }
                        return postfixExpression;
                }
        }
}
