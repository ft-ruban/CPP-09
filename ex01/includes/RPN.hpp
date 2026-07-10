#include <iostream>
#include <stack>


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
        //int result_;

    
};