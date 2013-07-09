#include "pretreatment.h"
#include <string>
using namespace std;
static string cleanBlanks(const string &s) {
    string result = "";
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] != ' ')
            result += s[i];
    return result;
}
bool calculator::expressionPretreatment(string &expression) {
    string result = "(" + cleanBlanks(expression);
    for (int i = 1; result[i] != '\0'; i++)
        switch (result[i - 1]) {
            case '(':
                switch (result[i]) {
                    case ')':
                        result[i - 1] = ' ';
                    case '+':
                        result[i] = ' ';
                        break;
                    case '-':
                        result.insert(i, "0");
                        break;
                }
                break;
            case '+':
            case '-':
                switch (result[i]) {
                    case '+':
                    case '-':
                        result[i] = (result[i - 1] == result[i] ? '+' : '-');
                        result[i - 1] = ' ';
                        break;
                }
                break;
        }
    result = cleanBlanks(result);
    int deleteNum = 0;
    for (int i = 0; result[i] != '\0'; i++)
        switch (result[i]) {
            case '(':
                deleteNum++;
                break;
            case ')':
                deleteNum--;
                break;
        }
    while (deleteNum > 0)
        result[--deleteNum] = ' ';
    result = cleanBlanks(result);
    bool change = result != expression;
    expression = result;
    return change;
}
