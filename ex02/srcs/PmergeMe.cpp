#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other){
    this->bar_ = other.bar_;
    this->foo_ = other.foo_;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other){
    if(this != &other){
        this->bar_ = other.bar_;
        this->foo_ = other.foo_;
    }
    return(*this);
}

PmergeMe::~PmergeMe(){

}