#include <iostream>
#include <stack>
#include <stdexcept>
#include <limits.h>

enum operators{
	ADDITION_OVERF_CASE,
	SUBTRACTION_OVERF_CASE,
	DIVISION_OVERF_CASE,
    MULT_OVERF_CASE
};

class RPN{
    public:
        RPN();
        RPN(const char argv[]);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        void getInput()const;
        void getSizeOfInput()const;
        void getStock()const;
        void getSizeOfStock()const;

        void calculusTreatment();
        void printResult()const;
        void processExpression(const char& used_operator);
        void pushAndResizeStock(int value_to_push);
        char topPopAndResizeInput();
        int  topPopAndResizeStock();
    
    private:
        std::stack<char> input_;
        int size_of_input_;
        std::stack<int> stock_;
        int size_of_stock_;
};