#include <iostream>
#include <memory>

class test
{
// private:
public:
	int	num1;
	char	*str;
	static int num2;

	test(){
		std::cout << num1 << " constructor" << std::endl;
	}
	test(int n): num1(n){
		str = new char [2];
		str[0] = 'a';
		std::cout << num1 << " int constructor" << std::endl;
	}
	~test(){
		std::cout << num1 << " destructor" << std::endl;
	}
};

int	test::num2 = 1234;

int	main()
{
	int	*a = new int [4];

	// test *a = new test [4];
	std::allocator<int>	alloc;

	// test *b = alloc.allocate(4);
	// alloc.construct(&b[0], 1);
	// alloc.construct(&b[1], 2);
	// b[2].num1 = 3;

	// // alloc.destroy(b);
	// // alloc.destroy(&b[1]);
	// // alloc.destroy(&b[2]);
	// // alloc.destroy(&b[3]);

	// std::cout << "---deallocate---" << std::endl;
	// // alloc.deallocate(b, 4);

	// std::cout << (b[0].num1) << std::endl;
	// std::cout << (b[0].num2) << std::endl;
	// std::cout << (b[1].num1) << std::endl;
	// std::cout << (b[1].num2) << std::endl;
	// std::cout << (b[2].num1) << std::endl;
	// std::cout << (b[2].num2) << std::endl;

	// system("leaks a.out");
	// delete[] a;

	a = alloc.allocate(4);
	alloc.construct(&a[0]);
	alloc.construct(&a[1]);
	alloc.construct(&a[2], 2);

	std::cout << a[0] << std::endl;
	std::cout << a[1] << std::endl;
	std::cout << a[2] << std::endl;

}