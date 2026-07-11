#include "../includes/RPN.hpp"

RPN::RPN() : size_of_input_(0), size_of_stock_(0){}

RPN::RPN(const char argv[]){
    int i = 0;
    size_of_stock_ = 0;

    while(argv[i] != '\0')
        i++;
    size_of_input_ = i;
    while(i >= 0){
        input_.push(argv[i]);
        i--;
    }
 
}

RPN::RPN(const RPN& other) : input_(other.input_),
                             size_of_input_(other.size_of_input_),
                             stock_(other.stock_),
                             size_of_stock_(other.size_of_stock_){}

RPN& RPN::operator= (const RPN& other){
    if(this != &other){
        this->input_ = other.input_;
        this->size_of_input_ = other.size_of_input_;
        this->stock_ = other.stock_;
        this->size_of_stock_ = other.size_of_stock_;
    }
    return(*this);
}

RPN::~RPN(){}

void RPN::getInput() const{
    std::stack<char> buff = input_;
    int size_buff = size_of_input_;

    while(size_buff != 0){
        std::cout<<buff.top();
        buff.pop();
        size_buff--;
    }
    std::cout<<std::endl;
}

void RPN::getSizeOfInput() const{
    std::cout<<size_of_input_<<std::endl;
}

void RPN::getStock() const{
    std::stack<int> buff = stock_;
    int size_buff = size_of_stock_;

    while(size_buff != 0){
        std::cout<<buff.top();
        buff.pop();
        size_buff--;
    }
    std::cout<<std::endl;
}

void RPN::getSizeOfStock() const{
    std::cout<<size_of_stock_<<std::endl;
}

static bool isSpace(const char& c){
    return(c == ' ');
}

static bool isNum(const char& c){
    return(c >= '0' && c <= '9');
}

static bool isValidToken(const char& c){
    return(c == '+' || c == '-' || c == '/' || c == '*');
}

static void overflowDetector(const int& operator_case, const int& a, const int& x){
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

void RPN::calculusTreatment(){
    while(size_of_input_ != 0){
        char to_treat = topPopAndResizeInput();
        if(isNum(to_treat))
            pushAndResizeStock(to_treat - '0');
        else if(isValidToken(to_treat)){
            if(size_of_stock_ < 2)
                throw std::invalid_argument("");
            else
                processExpression(to_treat);
        }
        else
            throw std::invalid_argument("");
    }
}

void RPN::printResult()const{
    if(size_of_stock_ != 1){
        throw std::invalid_argument("");
    }
    std::cout<<stock_.top()<<std::endl;
}

void RPN::processExpression(const char& used_operator){
    int operand_y = topPopAndResizeStock();
    int operand_x = topPopAndResizeStock();

    switch(used_operator){
            case '+':
                overflowDetector(ADDITION_OVERF_CASE, operand_x, operand_y);
                pushAndResizeStock(operand_x + operand_y);
                break;
            case '-':
                overflowDetector(SUBTRACTION_OVERF_CASE, operand_x, operand_y);
                pushAndResizeStock(operand_x - operand_y);
                break;
            case '/':
                overflowDetector(DIVISION_OVERF_CASE, operand_x, operand_y);
                if(operand_y == 0)
                    throw std::invalid_argument("");
                pushAndResizeStock(operand_x / operand_y);
                break;
            case '*':
                overflowDetector(MULT_OVERF_CASE, operand_x, operand_y);
                pushAndResizeStock(operand_x * operand_y);
                break;
            default:
                throw std::invalid_argument("");
        }
}

void RPN::pushAndResizeStock(int value_to_push){
    stock_.push(value_to_push);
    size_of_stock_++;
}

char RPN::topPopAndResizeInput(){
    char return_value = input_.top();
    input_.pop();
    size_of_input_--;
    if(size_of_input_ != 0){
        if(!isSpace(input_.top()))
            throw std::invalid_argument("");
        input_.pop();
        size_of_input_--;
    }
    return(return_value);
}

int RPN::topPopAndResizeStock(){
    int return_value = stock_.top();

    stock_.pop();
    size_of_stock_--;
    return(return_value);
}