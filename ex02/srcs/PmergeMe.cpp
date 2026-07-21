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

void PmergeMe::sortVector()
{
    fordJohnsonSort(vec_, 1);
}

void PmergeMe::sortList()
{
    fordJohnsonSort(list_, 1);
}

// 11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7
template <typename Container>
void PmergeMe::fordJohnsonSort(Container& c, int pair_depth){
    // typedef typename Container::iterator Iterator;
    
    int num_pair = c.size() / pair_depth;
    std::cout<<"pair_un_nbr = " << num_pair <<std::endl; //TODL
    if(num_pair < 2)
        return;
    bool is_it_odd = num_pair % 2 == 1;
    // 2 * 1    2 * 2   2 * 4  2 * 8


    fordJohnsonSort(c, pair_depth * 2);
}