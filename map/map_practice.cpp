#include <iostream>
#include "map.hpp"
#include <map>

int	main()
{
	ft::map<int, int>	m;
	std::map<int, int>	test;

	m._tree.insert_node(std::make_pair(1, 1));
	m._tree.insert_node(std::make_pair(2, 2));
	m._tree.insert_node(std::make_pair(3, 3));
	m._tree.insert_node(std::make_pair(4, 4));

	test.insert(std::make_pair(1, 1));
	test.insert(std::make_pair(2, 2));
	test.insert(std::make_pair(3, 3));
	test.insert(std::make_pair(4, 4));


	ft::map<int, int>::iterator	iter1 = m.begin();
	ft::map<int, int>::iterator	iter2 = m.end();

	std::map<int, int>::iterator	test_iter1 = test.begin();
	std::map<int, int>::iterator	test_iter2 = test.end();

	printf("==\n");
	std::cout << (iter1 == iter2) << std::endl;
	std::cout << (test_iter1 == test_iter2) << std::endl;

	printf("!=\n");
	std::cout << (iter1 != iter2) << std::endl;
	std::cout << (test_iter1 != test_iter2) << std::endl;

	
}