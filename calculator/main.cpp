#include "pretreatment.h"
#include "infixExpression.h"
#include "postfixExpression.h"
#include <iostream>
#include <string>
using namespace std;
using namespace calculator;
int main() {
    for (string infixExpression; getline(cin, infixExpression); ) {
        while (expressionPretreatment(infixExpression));
        cout << infixExpression << endl;
        string postfixExpression = infixToPostfix(infixExpression);
        cout << postfixExpression << endl;
        double result = calculatePostfixExpression(postfixExpression);
        cout << result << endl;
    }
    return 0;
}
