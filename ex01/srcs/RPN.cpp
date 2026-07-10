#include "../includes/RPN.hpp"

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

static bool isNum(char c){
    return(c >= '0' && c <= '9');
}

void RPN::calculusTreatment(){
    char buff_one;
    char buff_two;

    buff_one = input_.top();
    input_.pop();
    input_.pop();
    buff_two = input_.top();
    input_.pop();
    std::cout<<"num_one = "<<buff_one<<" num_2 = "<<buff_two<<std::endl;
    std::cout<<"num_one is num? : "<< isNum(buff_one)<<"num_two is num? : "<<isNum(buff_two)<<std::endl;
}