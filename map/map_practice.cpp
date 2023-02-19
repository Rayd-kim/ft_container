#include <iostream>
#include "map.hpp"
#include <map>

int	main()
{
	ft::map<int, int>	m;
	std::map<int, int>	test;

	m[1] = 1;
	m[2] = 2;
	m[3] = 3;
	m[4] = 4;

	m._tree.print_tree();
	std::cout << m[1] << std::endl;
	std::cout << m[2] << std::endl;
	std::cout << m[3] << std::endl;
	std::cout << m[4] << std::endl;
	// m._tree.insert_node(std::make_pair(1, 1));
	// m._tree.insert_node(std::make_pair(2, 2));
	// m._tree.insert_node(std::make_pair(3, 3));
	// m._tree.insert_node(std::make_pair(4, 4));

	// test.insert(std::make_pair(1, 1));
	// test.insert(std::make_pair(2, 2));
	// test.insert(std::make_pair(3, 3));



	// ft::map<int, int>::const_iterator	iter1 = m.begin();
	// ft::map<int, int>::const_iterator	iter2 = m.end();

	// std::map<int, int>::const_iterator	test_iter1 = test.begin();
	// std::map<int, int>::iterator	test_iter2 = test.end();


	// printf("---second modi\n");
	// std::cout << (*iter1).second << std::endl;
	// (*iter1).second = 4;
	// iter1->second = 5;
	// std::cout << iter1->second << std::endl;
	// test_iter1->second = 4;


}