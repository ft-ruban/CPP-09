#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>

class PmergeMe{
    public:
        PmergeMe();
        PmergeMe(const std::vector<int>& values);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        const std::vector<int>& getVector()const;
        const std::list<int>& getList()const;

        void sortVector();
        void sortList();

        template <typename Container>
        void fordJohnsonSort(Container& c, int pair_depth);

    private:
        std::vector<int> vec_;
        std::list<int> list_;
};

#endif