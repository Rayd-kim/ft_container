#include <iostream>


template <typename T>
class vector {
	private:
		T* data;
		int	length;
		int	capacity;

	public:
		vector(int n = 1) : data(new T[n]), length(0), capacity(n) {}

		void	push_back(T element) //새로운 원소 추가
		{
			if (capacity <= length)
			{
				T *temp = new T[capacity * 2];
				for (int i = 0; i < length; i++)
					temp[i] = data[i];
				delete[] data;
				data = temp;
				capacity *= 2;
			}
			data[length] = element;
			length++;
		}

		void	remove(int index) //index번째 위치한 원소를 제거
		{
			for (int i = index + 1; i < length; i++)
				data[i - 1] = data[i];
			length--;
		}

		int	size() //vector의 크기 (vector에 할당된 크기가 아닌 데이터가 저장된 크기)
		{
			return length;
		}

		T operator[](int index) //index 번째 원소에 접근
		{
			return data[i];
		}

		~vector()
		{
			if (data != nullptr)
				delete[] data;
		}
};
