# CS303ExtraCredit
Efficiency of Algorithms
1. eval() Function:
Time Complexity: O(n)
The eval() function processes each character in the expression exactly once. It iterates through the expression to identify operators and operands, performing stack operations (push and pop) in constant time. Since the expression is only processed once and each stack operation is O(1), the overall time complexity is linear, or O(n), where n is the length of the expression.
2. applyOperator() Function:
Time Complexity: O(1)
This function applies a given operator to two operands. It only involves comparing operator strings and performing the corresponding arithmetic operation, which is a constant-time task.
3. precedence() Function:
Time Complexity: O(1)
The precedence() function simply compares the precedence of operators. This is done using a series of if-else statements, which are all constant-time operations.
4. handleError() Function:
Time Complexity: O(1)
This function handles errors by throwing exceptions and formatting error messages. Both of these operations take constant time.
5. Helper Functions (e.g., isOperator(), isDigit(), etc.):
Time Complexity: O(1)
These functions perform basic checks (e.g., checking if a character is a digit or an operator), which is done in constant time.
Could the Algorithm be Improved?
The current algorithm is already optimal for this task. It uses a single pass through the expression (O(n) time complexity), and stack operations (push and pop) are constant time.

Improving the algorithm’s time complexity further is unlikely because we need to process each character in the expression to evaluate it. The algorithm works efficiently for this purpose.

That said, there could be room for improvements in memory usage or optimizations related to edge cases. For example, you could optimize how we manage operator precedence and parentheses to minimize memory overhead. But overall, the approach is already quite efficient.

