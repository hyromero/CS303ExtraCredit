//CS 303 Extra Credit
//Hiram Romero

#include "Evaluator.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <stack>

using namespace std;

// Main function that processes the expression
int Evaluator::eval(const string& expression) {
    // Validate the expression before processing
    if (!isValidExpression(expression)) {
        throw invalid_argument("Invalid expression");
    }

    stack<int> values;     // stack to store operands
    stack<string> ops;     // stack to store operators (now as strings)

    size_t i = 0;
    while (i < expression.size()) {
        char current = expression[i];

        // Skip whitespace
        if (isspace(current)) {
            ++i;
            continue;
        }

        // Check for invalid start of expression
        if (startsWithClosingParenthesis(expression)) {
            handleError("Expression can’t start with a closing parenthesis", i);
        }
        if (startsWithBinaryOperator(expression)) {
            handleError("Expression can’t start with a binary operator", i);
        }

        // Check for invalid consecutive binary operators
        if (twoBinaryOperatorsInARow(expression, i)) {
            handleError("Two binary operators in a row", i);
        }

        // Check for invalid consecutive operands
        if (twoOperandsInARow(expression, i)) {
            handleError("Two operands in a row", i);
        }

        // Check for unary operator followed by binary operator
        if (unaryOperandFollowedByBinaryOperator(expression, i)) {
            handleError("A unary operand can’t be followed by a binary operator", i);
        }

        // Handle division by zero
        if (divisionByZero(expression, i)) {
            handleError("Division by zero", i);
        }

        // If current character is a digit, read the full number
        if (isDigit(current)) {
            int value = 0;
            while (i < expression.size() && isDigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                ++i;
            }
            values.push(value);
        }
            // Handle unary operators like `++`, `--`, `!`, and `-`
        else if (current == '+' || current == '-' || current == '!' || current == '^') {
            string op(1, current);
            ops.push(op);
            ++i;
        }
            // Handle multi-character operators (e.g., "==", "&&")
        else if (current == '=' && i + 1 < expression.size() && expression[i + 1] == '=') {
            ops.push("==");
            i += 2;
        }
        else if (current == '&' && i + 1 < expression.size() && expression[i + 1] == '&') {
            ops.push("&&");
            i += 2;
        }
        else if (current == '|' && i + 1 < expression.size() && expression[i + 1] == '|') {
            ops.push("||");
            i += 2;
        }
            // Handle other operators and parentheses
        else if (isOperator(string(1, current))) {
            string op(1, current);
            while (!ops.empty() && precedence(ops.top()) >= precedence(op)) {
                string topOp = ops.top();
                ops.pop();
                int right = values.top();
                values.pop();
                int left = values.top();
                values.pop();
                values.push(applyOperator(left, right, topOp));
            }
            ops.push(op);
            ++i;
        }
            // Handle closing parentheses
        else if (current == ')') {
            while (!ops.empty() && ops.top() != "(") {
                string op = ops.top();
                ops.pop();
                int right = values.top();
                values.pop();
                int left = values.top();
                values.pop();
                values.push(applyOperator(left, right, op));
            }
            if (ops.empty() || ops.top() != "(") {
                handleError("Mismatched parentheses", i);
            }
            ops.pop(); // Pop the '('
            ++i;
        }
            // Handle opening parentheses
        else if (current == '(') {
            ops.push("(");
            ++i;
        }
        else {
            handleError("Invalid character", i);
        }
    }

    // Apply remaining operators
    while (!ops.empty()) {
        string op = ops.top();
        ops.pop();
        int right = values.top();
        values.pop();
        int left = values.top();
        values.pop();
        values.push(applyOperator(left, right, op));
    }

    return values.top();
}

// Helper functions to handle specific errors

// Check if expression starts with a closing parenthesis
bool Evaluator::startsWithClosingParenthesis(const string& expr) {
    return expr[0] == ')';
}

// Check if expression starts with a binary operator
bool Evaluator::startsWithBinaryOperator(const string& expr) {
    char firstChar = expr[0];
    return firstChar == '+' || firstChar == '-' || firstChar == '*' ||
           firstChar == '/' || firstChar == '%' || firstChar == '^' ||
           firstChar == '=' || firstChar == '>' || firstChar == '<' ||
           firstChar == '!' || firstChar == '&' || firstChar == '|';
}

// Check if two binary operators are in a row
bool Evaluator::twoBinaryOperatorsInARow(const string& expr, size_t pos) {
    if (pos + 1 < expr.size() && isOperator(string(1, expr[pos])) &&
        isOperator(string(1, expr[pos + 1]))) {
        return true;
    }
    return false;
}

// Check if there are two operands in a row
bool Evaluator::twoOperandsInARow(const string& expr, size_t pos) {
    if (pos + 1 < expr.size() && isDigit(expr[pos]) && isDigit(expr[pos + 1])) {
        return true;
    }
    return false;
}

// Check if a unary operator is followed by a binary operator
bool Evaluator::unaryOperandFollowedByBinaryOperator(const string& expr, size_t pos) {
    if (pos + 1 < expr.size() && (expr[pos] == '+' || expr[pos] == '-' || expr[pos] == '!' || expr[pos] == '^') &&
        isOperator(string(1, expr[pos + 1]))) {
        return true;
    }
    return false;
}

// Check for division by zero
bool Evaluator::divisionByZero(const string& expr, size_t pos) {
    if (expr[pos] == '/' && pos + 1 < expr.size() && expr[pos + 1] == '0') {
        return true;
    }
    return false;
}

// Apply operator on two operands
int Evaluator::applyOperator(int left, int right, const string& op) {
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
        if (right == 0) {
            throw runtime_error("Division by zero");
        }
        return left / right;
    }
    if (op == "%") return left % right;
    if (op == "^") return pow(left, right);
    if (op == "==") return left == right;
    if (op == "!=") return left != right;
    if (op == ">") return left > right;
    if (op == "<") return left < right;
    if (op == ">=") return left >= right;
    if (op == "<=") return left <= right;
    if (op == "&&") return left && right;
    if (op == "||") return left || right;
    throw invalid_argument("Unknown operator");
}

// Determine operator precedence
int Evaluator::precedence(const string& op) {
    if (op == "!" || op == "++" || op == "--" || op == "-") return 8; // unary
    if (op == "^") return 7;    // power
    if (op == "*" || op == "/" || op == "%") return 6;  // arithmetic
    if (op == "+" || op == "-") return 5;   // addition/subtraction
    if (op == ">" || op == "<" || op == ">=" || op == "<=") return 4;  // comparison
    if (op == "==" || op == "!=") return 3;  // equality
    if (op == "&&") return 2;   // logical AND
    if (op == "||") return 1;   // logical OR
    return 0;   // unknown operator
}

// Error handler
void Evaluator::handleError(const string& message, size_t pos) {
    throw runtime_error(message + " @ char: " + to_string(pos));
}

// Check if a string is an operator
bool Evaluator::isOperator(const string& op) {
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%" ||
           op == "^" || op == "==" || op == "!=" || op == ">" || op == "<" ||
           op == ">=" || op == "<=" || op == "&&" || op == "||" || op == "!";
}

// Check if a character is a digit
bool Evaluator::isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Check if expression is valid
bool Evaluator::isValidExpression(const string& expression) {
    return !expression.empty();
}
//
// Created by Hiram Romero on 12/6/24.
//
