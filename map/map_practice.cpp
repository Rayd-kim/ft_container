#include <iostream>
#include <map>


int	main()
{
	std::map<std::string, int>	test;

	test.insert(std::make_pair<std::string, int>("acc", 1));
	test.insert(std::make_pair<std::string, int>("abb", 2));
	test.insert(std::make_pair<std::string, int>("aaa", 3));
	test.insert(std::make_pair<std::string, int>("aaa", 5));
	test["aaaa"] = 4;
	test["aa"] = 5;
	test["aa"] = 6;

	std::cout <<"map size: " << test.size() << std::endl;
	// std::cout <<"map max_size: " << test.max_size() << std::endl;
	// std::cout <<"map empty: " << test.empty() << std::endl;

	std::map<std::string, int>::iterator	iter = test.begin();
	for (; iter != test.end(); iter++)
		std::cout << (*iter).first << " " << (*iter).second << std::endl;

	std::cout << "operator[]: " << test["aaa"] << std::endl;
	
}