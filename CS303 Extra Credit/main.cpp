//CS 303 Extra Credit
//Hiram Romero

#include <iostream>
#include "Evaluator.h"

using namespace std;

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    Evaluator eval;

    try {
        int result = eval.eval(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
