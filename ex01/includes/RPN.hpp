#include <iostream>
#include <stack>

#define ADDITION_OVERF_CASE 1
#define SUBTRACTION_OVERF_CASE 2
#define DIVISION_OVERF_CASE 3
#define MULT_OVERF_CASE 4


//TODO class error?
class RPN{
    public:
        RPN();
        RPN(char argv[]);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        void getRPN();
        void getSizeOfInput();
        void calculusTreatment();
        void printResult();
        //todo? function to transfer argument to the input_
    
    private:
        std::stack<char> input_;
        int size_of_input_;
        std::stack<int> stock_;
        int size_of_stock_;


    
};