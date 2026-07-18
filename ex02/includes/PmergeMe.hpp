#include <vector>
#include <list>

class PmergeMe{
    public:
        PmergeMe();
        PmergeMe(const std::vector<int>& values);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        const std::vector<int>& getVector()const;
        const std::list<int>& getList()const;

    private:
        std::vector<int> vec_;
        std::list<int> list_;
};