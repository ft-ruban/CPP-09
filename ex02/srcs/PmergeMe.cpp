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


template <typename Container>
void PmergeMe::fordJohnsonSort(Container& c, int pair_level){
    typedef typename Container::iterator iterator;

    int pair_units_nbr = c.size() / pair_level;
    if (pair_units_nbr < 2)
        return;

    bool is_odd = pair_units_nbr % 2 == 1;

    iterator start = c.begin();
    iterator last = next(c.begin(), pair_level * (pair_units_nbr));
    iterator end = next(last, -(is_odd * pair_level));

    int jump = 2 * pair_level;
    for(iterator it = start; it != end; std::advance(it, jump)){
        iterator this_pair = next(it, pair_level - 1);
        iterator next_pair = next(it, pair_level * 2 - 1);
        //if()
    }
    fordJohnsonSort(c, pair_level * 2);
    
}