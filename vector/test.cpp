#include <iostream>
#include "vector.hpp"
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

    test1.push_back(5);
    test1.push_back(4);
    test1.push_back(3);
    test1.push_back(2);
    test1.push_back(1);

    test2.push_back(5);
    test2.push_back(4);
    test2.push_back(3);
    test2.push_back(2);
    test2.push_back(1);

    ft::vector<int>::iterator   iter = test1.begin();
    std::vector<int>::iterator  std_iter = test2.begin();
    std::cout << "insert " << *(test2.insert(std_iter + 2, 100)) << std::endl;
    
    std::cout << "insert " << *(test1.insert(iter + 2, 100)) << std::endl;
    
    std::for_each(test1.begin(), test1.end(), Print());
    
    std::for_each(test2.begin(), test2.end(), Print());

    //  *citer = 12345;


}