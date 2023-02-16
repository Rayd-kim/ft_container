#include <iostream>
#include <map>


int	main()
{
	std::map<int, int>	test;

	test.insert(std::make_pair<int, int>(1, 1));
	// test.insert(std::make_pair<std::string, int>(2", 2));
	// test.insert(std::make_pair<std::string, int>(3, 3));
	// test.insert(std::make_pair<std::string, int>(5, 5));
	// test["aaaa"] = 4;
	// test["aa"] = 5;
	// test["aa"] = 6;
	std::map<int, int>::iterator	iter = test.end();
	std::cout << "end : " << iter->first << std::endl;
	// std::cout <<"end - 1: " << (--iter)->first << std::endl;
	++iter;
	--iter;
	std::cout << "end : " << iter->first << std::endl;
	// ++iter;
	// std::cout << "end : " << iter->first << std::endl;
	// std::cout << "end + 1 - 1: " << (--iter)->first << std::endl;
	

	
	
}