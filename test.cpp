#include <iostream>
#include "vector_test.hpp"
#include <vector>
#include <algorithm>


class Print{
    public:
    void    operator()(int a){
        std::cout << a << std::endl;
    }
};

int main(void)
{
    ft::vector<int> test1;
    std::vector<int> test2;

    test1.push_back(999);
    test1.push_back(888);
    test1.push_back(777);

    test2.push_back(33);
    test2.push_back(22);
    test2.push_back(11);

    ft::vector<int> test_copy_construct(test1);
    ft::vector<int> test_iterator_construct(test1.begin(), test1.end());
    ft::vector<int> test_size_construct((ft::vector<int>::size_type)3, 100);
    
    // std::vector<int> test_size_construct(3, 1);
    // std::vector<int> test_copy_construct(test2);
    // std::vector<int> test_iterator_construct(test2.begin(), test2.end());

    // std::for_each(test2.begin(), test2.end(), Print());
    std::cout << "print1" << std::endl;
    std::for_each(test1.begin(), test1.end(), Print());
    std::cout << "print2" << std::endl;
    std::for_each(test_size_construct.begin(), test_size_construct.end(), Print());
    std::cout << "print3" << std::endl;
    std::for_each(test_copy_construct.begin(), test_copy_construct.end(), Print());
    std::cout << "print4" << std::endl;
    std::for_each(test_iterator_construct.begin(), test_iterator_construct.end(), Print());

}