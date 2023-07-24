// Prefix Expression Evaluation with recursion

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>    // NAN
#include<ctype.h>   // isspace

#define xSTR(x) #x
#define STR(x) xSTR(x)


double eval_prefix(char* expression);
double _eval_prefix(const char ** _expr);

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("Usage: %s <prefix_expression>\n", argv[0]);
        return 1;
    }
    
    char *expression = argv[1];
    printf("Prefix Expression:\n");
    printf("'%s'\n", expression);
    
    double result = eval_prefix(expression);
    printf("\nResult:\n");
    printf("%lf\n", result);

    return 0;
}


// wrapper to enforce const and create new pointer to string,
// rather than modify callers pointer directly
double eval_prefix(char* expression) {
    const char * expr = expression;
    return _eval_prefix(&expr);
}


// recursive
// _expr: pointer to operation to parse (prefix expression)
double _eval_prefix(const char ** _expr) {
    if (!_expr || !*_expr || **_expr == '\0') {
        printf("ERROR: invalid _expression\n");
        return NAN;
    }
    
    // get the current leading character
    char c = *_expr[0];
    
    // ignore whitespace
    if (isspace(c)) {
        (*_expr)++;
        return _eval_prefix(_expr);
    }
    
    // test if number
    double value;
    int num_chars;
    int num_args = sscanf(*_expr, "%lf%n", &value, &num_chars);
    if (0 != num_args) {
        // advance past all digits of this number
        (*_expr) += num_chars;
        return value;
    }
    
    // should only have math operations left
    // if math_operation : get left and right values
    double left, right;
    switch(c) {
        case '+': case '-': case '*': case '/':
            (*_expr)++;
            left = _eval_prefix(_expr);
            right = _eval_prefix(_expr);
            break;
        
        default:
            printf("ERROR: invalid char '%c'\n", c);
            return NAN;
    }
    
    // actually perform math operation
    switch(c) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }

    printf("ERROR: should never reach bottom of function '%c'\n", c);
    return NAN;
}
