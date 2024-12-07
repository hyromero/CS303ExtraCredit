//CS 303 Extra Credit
//Hiram Romero

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

class Evaluator {
public:
    // Function to evaluate the expression
    int eval(const string& expression);

private:
    // Function to determine operator precedence
    int precedence(const string& op);

    // Function to apply operators to operands
    int applyOperator(int left, int right, const string& op);

    // Function to apply unary operators
    int applyUnaryOperator(int operand, const string& op);

    // Function to check if a string is an operator
    bool isOperator(const string& op);

    // Function to check if a character is a digit
    bool isDigit(char c);

    // Function to handle errors in the expression
    void handleError(const string& message, size_t pos);

    // Function to validate the expression
    bool isValidExpression(const string& expression);

    // Helper functions to check specific errors
    bool startsWithClosingParenthesis(const string& expr);
    bool startsWithBinaryOperator(const string& expr);
    bool twoBinaryOperatorsInARow(const string& expr, size_t pos);
    bool twoOperandsInARow(const string& expr, size_t pos);
    bool unaryOperandFollowedByBinaryOperator(const string& expr, size_t pos);
    bool divisionByZero(const string& expr, size_t pos);
};

#endif // EVALUATOR_H
