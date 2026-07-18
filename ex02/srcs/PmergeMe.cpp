#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const std::vector<int>& values)
    : vec_(values), list_(values.begin(), values.end())
{
}

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

const std::list<int>& PmergeMe::getList()const{
    return(list_);
}

const std::vector<int>& PmergeMe::getVector()const{
    return(vec_);
}