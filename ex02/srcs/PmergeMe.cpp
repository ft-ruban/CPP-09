#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other){
    this->vec_ = other.vec_;
    this->list_ = other.list_;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other){
    if(this != &other){
        this->vec_ = other.vec_;
        this->list_ = other.list_;
    }
    return(*this);
}

PmergeMe::~PmergeMe(){

}