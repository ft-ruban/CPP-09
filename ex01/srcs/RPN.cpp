#include "../includes/RPN.hpp"
#include <stdexcept> //TODO mv to .hpp

RPN::RPN(){

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
    std::cout<<"debug isNum c = "<<c<<" = "<<(c>='0' && c <= '9')<<std::endl;
    return(c >= '0' && c <= '9');
}
//+ - / *
static bool isValidToken(char c){
    return(c == '+' || c == '-' || c == '/' || c == '*');
}

static void getToNextChar(std::stack<char>& input_){
    input_.pop();
    if(!isSpace(input_.top()))
        throw std::invalid_argument("");
    input_.pop();
}
//+ - / *
// static int expression(int variable_x, int variable_y, char active_token){

//     switch(active_token){
//         case '+':
//             return(variable_x + variable_y);
//             break;
//         case '-':
//             return(variable_x - variable_y);
//             break;
//         case '/':
//             if(variable_x == 0 || variable_y == 0)
//                 throw std::invalid_argument("");
//             return(variable_x / variable_y);
//             break;
//         case '*':
//             return(variable_x * variable_y);
//         default:
//             throw std::invalid_argument("");
//     }
// }

static void expression(std::stack<int>& buff_stack, char active_token){
    int variable_x = 0;
    int variable_y = 0;
    
    variable_x  = buff_stack.top();
    buff_stack.pop();
    variable_y = buff_stack.top();
    buff_stack.pop();
    std::cout<<"test"<<std::endl; //TODL
    std::cout<<"active_token = "<<active_token<<std::endl; //TODL


    switch(active_token){
            case '+':
                buff_stack.push(variable_x + variable_y);
                break;
            case '-':
                buff_stack.push(variable_x - variable_y);
                break;
            case '/':
                if(variable_y == 0)
                    throw std::invalid_argument("");
                buff_stack.push(variable_x / variable_y);
                break;
            case '*':
                buff_stack.push(variable_x * variable_y);
                break;
            default:
                throw std::invalid_argument("");
        }   
}

//./bin/RPN "7 2 * 7 - 7"
//$> ./RPN "1 2 * 2 / 2 * 2 4 - +"    Pour ce cas specifique il faut faire gaffe. a la fin on a dans la pile [2] on add [2,2,4] et on fait 2-4 PAS 4-2
void RPN::calculusTreatment(){
    std::stack<int> buff_stack;
    int buff_stack_size = 0;
    char buff_one;
    char buff_two;
    char buff_three;

    // int variable_x = 0;
    // int variable_y = 0;
    char active_token;

//maybe there is a way without usin buff one two and such
    buff_one = input_.top();
    getToNextChar(input_);
    buff_two = input_.top();
    getToNextChar(input_);
    buff_three = input_.top();
    getToNextChar(input_);

    if(!isNum(buff_one) || !isNum(buff_two) || !isValidToken(buff_three)){
        throw std::invalid_argument("");
    }
    buff_stack.push(buff_one - '0');
    buff_stack_size++;
    buff_stack.push(buff_two - '0');
    buff_stack_size++;

    active_token = buff_three;

    expression(buff_stack, active_token);
    // std::cout<<"Variable_x = "<< variable_x<<std::endl;
    std::stack<int> buff = buff_stack;
    int size_buff = 1;
    while(size_buff != 0){
        std::cout<<buff.top();
        buff.pop();
        size_buff--;
    }
    std::cout<<std::endl;

    // std::cout<<"num_one is num? : "<< isNum(buff_one)<<"num_two is num? : "<<isNum(buff_two)<<std::endl;
}