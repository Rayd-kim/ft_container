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

    std::vector<int>    std_v;
    std::vector<int>    sw;

    test1.push_back(5);
    test1.push_back(4);
    test1.push_back(3);
    test1.push_back(2);
    test1.push_back(1);

    std_v.push_back(5);
    std_v.push_back(4);
    std_v.push_back(3);
    std_v.push_back(2);
    std_v.push_back(1);   

    sw.push_back(111);
    sw.push_back(111);
    sw.push_back(111);


    // ft::vector<int>::iterator   iter = test1.begin();
    // std::cout << "size: " << test1.size() << "  capacity: " << test1.capacity() << std::endl;
   
    // std::cout << "test1: " << *(test1.erase(test1.begin(), test1.begin())) << std::endl;
    // std::cout << "std_v: " << *(std_v.erase(std_v.begin(), std_v.begin())) << std::endl;

    
    // std::cout << "insert " << *(test1.insert(test1.begin(), 100)) << std::endl;
    std::cout << "size: " << std_v.size() << "  capacity: " << std_v.capacity() << std::endl;
    std::cout << "size: " << sw.size() << "  capacity: " << sw.capacity() << std::endl;
    std_v.swap(sw); 
    std::cout << "size: " << std_v.size() << "  capacity: " << std_v.capacity() << std::endl;
    std::cout << "size: " << sw.size() << "  capacity: " << sw.capacity() << std::endl;
    // std::for_each(test1.begin(), test1.end(), Print());
    std::for_each(std_v.begin(), std_v.end(), Print());
    std::for_each(sw.begin(), sw.end(), Print());
    

    //  *citer = 12345;


}