#include <iostream>
#include <memory>

class temp
{
	public:
		int num;
		temp(int n): num(n){
			printf("constructor\n");
		}
		~temp(){
			printf("destructor\n");
		}
};

int	main()
{
	std::allocator<temp>	a;

	temp	*arr = a.allocate(2);

	// a.construct(&arr[0], 1);
	// a.construct(&arr[1], 2);
	arr[0].num = 1;
	arr[1].num = 2;

	printf("1 %d\n", arr[0].num);
	printf("2 %d\n", arr[1].num);
	
	a.destroy(arr);
	a.destroy(arr + 1);
	a.deallocate(arr, 2);

	// system("leaks a.out");
}