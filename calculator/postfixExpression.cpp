#include "postfixExpression.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
static const std::string avaibleOperator[] = { "+", "-", "*", "/" };
static const int avaibleOperatorNum = sizeof(avaibleOperator) / sizeof(*avaibleOperator);
static bool isOperator(const string &s) {
    for (int i = 0; i < avaibleOperatorNum; i++)
        if (s == avaibleOperator[i])
            return true;
    return false;
}
static double calculateNumber(const double &a, const std::string &op, const double &b) {
    switch (op[0]) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}
double calculator::calculatePostfixExpression(const string &postfixExpression) {
    stringstream ss(postfixExpression);
    vector<double> numbers;
    for (string parament; getline(ss, parament, ':'); )
        if (isOperator(parament)) {
            numbers[numbers.size() - 2] = calculateNumber(numbers[numbers.size() - 2], parament, numbers[numbers.size() - 1]);
            numbers.pop_back();
        } else
            numbers.push_back(atof(parament.c_str()));
    return numbers[0];
}
