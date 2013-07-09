#include "pretreatment.h"
#include "infixExpression.h"
#include "postfixExpression.h"
#include <iostream>
#include <string>
using namespace std;
using namespace calculator;
int main() {
    for (string infixExpression; getline(cin, infixExpression); ) {
        cout << "Original infixExpression: " << infixExpression << endl;
        while (expressionPretreatment(infixExpression));
        cout << "Modified infixExpression: " << infixExpression << endl;
        string postfixExpression = infixToPostfix(infixExpression);
        cout << "postfixExpression: " << postfixExpression << endl;
        double result = calculatePostfixExpression(postfixExpression);
        cout << "calculation result: " << result << endl;
        cout << "----------------------------------------" << endl;
    }
    return 0;
}
