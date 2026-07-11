#include "../includes/RPN.hpp"
#include <stdexcept> //TODO mv to .hpp
#include <limits.h> //same

RPN::RPN(){
    size_of_input_ = 0;
    size_of_stock_ = 0;
}

RPN::RPN(char argv[]){
    int i = 0;
    while(argv[i] != '\0'){
        std::cout<<"i = "<<i<<std::endl;
        i++;
    }
    size_of_input_ = i;
    while(i >= 0){
        std::cout<<"i = "<<i<<std::endl;
        input_.push(argv[i]);
        i--;
    }
    size_of_stock_ = 0;
}

RPN::RPN(const RPN& other){
    (void) other;
}

RPN& RPN::operator= (const RPN& other){
    (void) other;
    return(*this);
}

RPN::~RPN(){

}

void RPN::getRPN(){
    std::stack<char> buff = input_;
    int size_buff = size_of_input_;
    while(size_buff != 0){
        std::cout<<buff.top();
        buff.pop();
        size_buff--;
    }
    std::cout<<std::endl;
}

void RPN::getSizeOfInput(){
    std::cout<<size_of_input_<<std::endl;
}



static bool isSpace(char c){
    return(c == ' ');
}

static bool isNum(char c){
    //std::cout<<"debug isNum c = "<<c<<" = "<<(c>='0' && c <= '9')<<std::endl;
    return(c >= '0' && c <= '9');
}
//+ - / *
static bool isValidToken(char c){
    return(c == '+' || c == '-' || c == '/' || c == '*');
}

static void getToNextChar(std::stack<char>& input_, int& size_of_input){
    input_.pop();
    size_of_input--;
    if(size_of_input != 0){
        if(!isSpace(input_.top()))
            throw std::invalid_argument("TODL !isspace gettonextchar");
        input_.pop();
        size_of_input--;
    }

}

static void overflowDetector(int operator_case, int a, int x){
    switch(operator_case){
        case MULT_OVERF_CASE:
            if ((a == -1 && x == INT_MIN )  || 
                (x == -1 && a == INT_MIN )  || 
                (x != 0 && a > INT_MAX / x) || 
                (x != 0 && a < INT_MIN / x))
                    throw std::invalid_argument("");
            break;
        case ADDITION_OVERF_CASE:
            if ((x > 0 && a > INT_MAX - x) || (x < 0 && a < INT_MIN - x))
                throw std::invalid_argument("");
            break;
        case SUBTRACTION_OVERF_CASE:
            if ((x < 0 && a > INT_MAX + x) || (x > 0 && a < INT_MIN + x))
                throw std::invalid_argument("");
            break;
        case DIVISION_OVERF_CASE:
            if ((a == INT_MIN && x == -1))
                throw std::invalid_argument("");
            break;
    }
}

static void expression(std::stack<int>& buff_stack, char active_token, int& size_of_stack){
    int variable_x = 0;
    int variable_y = 0;
    
    variable_y  = buff_stack.top();
    buff_stack.pop();
    size_of_stack--;
    variable_x = buff_stack.top();
    buff_stack.pop();
    size_of_stack--;
    std::cout<<"active_token = "<<active_token<<std::endl; //TODL

    std::cout<<"we are doing "<<variable_x<<" "<<active_token<<" "<<variable_y<<std::endl;
    switch(active_token){
            case '+':
                overflowDetector(ADDITION_OVERF_CASE, variable_x, variable_y);
                buff_stack.push(variable_x + variable_y);
                size_of_stack++;
                break;
            case '-':
                overflowDetector(SUBTRACTION_OVERF_CASE, variable_x, variable_y);
                buff_stack.push(variable_x - variable_y);
                size_of_stack++;
                break;
            case '/':
                overflowDetector(DIVISION_OVERF_CASE, variable_x, variable_y);
                if(variable_y == 0)
                    throw std::invalid_argument("");
                size_of_stack++;
                buff_stack.push(variable_x / variable_y);
                break;
            case '*':
                overflowDetector(MULT_OVERF_CASE, variable_x, variable_y);
                buff_stack.push(variable_x * variable_y);
                size_of_stack++;
                break;
            default:
                throw std::invalid_argument("");
        }   
}

void RPN::calculusTreatment(){
    char buff_one;

    while(size_of_input_ != 0){
        buff_one = input_.top();
        
        getToNextChar(input_, size_of_input_);
        if(isNum(buff_one)){
            stock_.push(buff_one - '0');
            size_of_stock_++;
        }
        else if(isValidToken(buff_one)){
            if(size_of_stock_ < 2)
                throw std::invalid_argument("");
            else
                expression(stock_, buff_one, size_of_stock_);
        }
        else
            throw std::invalid_argument("");
    }
    if(size_of_stock_ != 1){
        throw std::invalid_argument("");
    }
    int result = stock_.top();
    std::cout<<"result is = "<<result<<std::endl;
}