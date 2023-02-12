#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include <type_traits>
#include "../ft_library.hpp"

namespace ft
{
	template < typename T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef	T 												value_type;
			typedef	Alloc 											allocator_type;
			typedef	T&												reference;
			typedef	typename std::allocator<T>::pointer				pointer;
			typedef typename std::allocator<T>::const_pointer		const_pointer;
			typedef	typename std::allocator<T>::difference_type		difference_type;
			typedef	typename std::allocator<T>::size_type			size_type;
			typedef	const value_type&								const_reference;
			typedef	typename Alloc::pointer							iterator;
			typedef typename Alloc::const_pointer					const_iterator;

		private:
			T* 			_data;
			size_type	_length;
			size_type	_capacity;
			Alloc		alloc;

		public:

			explicit vector(): _length(0), _capacity(0)
			{
				_data = nullptr;
			}
			// n 만큼의 v를 가지는 벡터. n 만 들어오면 v는 기본값 T()가 된다. 속도향상을 위해 T의 복사생성자로 붙여넣기.
			explicit vector(size_type n, const T& v = T()): _length(n), _capacity(n)
			{
				_data = alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_data[i] = T(v);
			}
			vector(const vector &other): _length(other._length), _capacity(other._capacity)
			{
				this->_data = alloc.allocate(_capacity);
				for (size_type i = 0; i < _length; i++)
					alloc.construct(&_data[i], other._data[i]);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: _length(0), _capacity(0)
			{
				_data = alloc.allocate(_capacity);
				for (; first != last; first++)
					this->push_back(*first);
			}
			~vector()
			{
				if (_data != nullptr)
				{
					for (size_type i = 0; i < _length; i++)
						alloc.destroy(&_data[i]);
					// alloc.destroy(_data);
					alloc.deallocate(_data, _capacity);
				}
			}

			vector&	operator=(const vector& other)
			{
				if (_capacity < other.capacity())
				{
					clear();
					reserve(other.capacity());
				}				
				this->assign(other.begin(), other.end());
				return (*this);
			}

			void	assign(size_type count, const T& value)
			{
				clear();
				for (size_type i = 0; i < count; i++)
					push_back(value);
			}

			template<class InputIt>
			void	assign(InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				clear();
				for (; first != last; first++)
					push_back(*first);
			}
			// allocator_type	get_allocator() const
			// {	return (Alloc);	}
			void	push_back(const T& element)
			{
				if (_capacity <= _length)
				{
					if (_capacity == 0) // 기본생성자로 생성시, capacity가 0이기 때문에 예외처리
					{
						_capacity += 1;
						T *temp = alloc.allocate(_capacity);
						_data = temp;
					}
					else
					{
						//이 과정 = reserve랑 같다..?
						T *temp = alloc.allocate(_capacity * 2);
						// alloc.construct(&temp[0], _data[0]); //_data 는  맨앞을 가리키고 있으니까 오류를 피하기위해 0은 따로.
						for (size_type i = 0; i < _length; i++)
						{
							alloc.construct(&temp[i], _data[i]);
							alloc.destroy(&_data[i]);
						}
						// alloc.destroy(_data);
						alloc.deallocate(_data, _capacity);
						_data = temp;
						_capacity *= 2;
					}
				}
				alloc.construct(&_data[_length], element);
				_length++;
			}
			void	pop_back()
			{
				alloc.destroy(&_data[_length - 1]);
				_length--;
			}

			T&	at(size_type index)
			{
				if (index >= _length)
				{
					throw (std::out_of_range("vector"));
				}
				return _data[index];
			}			
			const_reference at(size_type index) const
			{
				if (index >= _length)
				{
					throw (std::out_of_range("vector"));
				}
				return _data[index];
			}

			T& operator[](size_type index) //index 번째 원소에 접근
			{	return _data[index];	}
			const T& operator[](size_type index) const
			{return _data[index];}

			//front back 함수는 비어있을 경우 segmentation fault 떠야한다.. cppreference에서 c.front() = *c.begin() 이다.
			// iterator를 반환하도록 만들어야하나..?
			T&	front()
			{	return (_data[0]);	}
			const_reference	front() const
			{return (_data[0]);}
			T&	back()
			{	return (_data[_length - 1]);	}
			const_reference	back() const
			{return (_data[_length - 1]);}
			T*	data()
			{
				if (_length == 0)
					return (nullptr);
				return (_data);
			}
			const_reference	data() const
			{
				if (_length == 0)
					return (nullptr);
				return (_data);
			}
			
			size_type	size() const //vector의 크기 (vector에 할당된 크기가 아닌 데이터가 저장된 크기)
			{	return _length;	}
			size_type	capacity() const
			{	return _capacity;	}
			size_type	max_size() const
			{	return (std::numeric_limits<size_type>::max() / sizeof(value_type));	}
			bool	empty() const
			{
				if (_length == 0)
					return (true);
				else
					return (false);
			}

			void	reserve(size_type new_cap)
			{
				if (new_cap > max_size())
					throw(std::length_error("vector"));
				if (new_cap > _capacity)
				{
					T*	temp;
					temp = alloc.allocate(new_cap);
					for (size_type i = 0; i < _length; i++)
					{
						alloc.construct(&temp[i], _data[i]);
						alloc.destroy(&_data[i]);
					}
					alloc.deallocate(_data, _capacity);
					_data = temp;
					_capacity = new_cap;
				}
			}
			void	clear()
			{
				for (; _length > 0; _length--)
					alloc.destroy(&_data[_length - 1]);
			}

			/*
			class	iterator{
			private:
				vector<T>*	_vec;
				T*			_vec_data;
				size_type	_index;

			public:
				typedef	std::random_access_iterator_tag	iterator_category;
				typedef	typename Alloc::value_type		value_type;
				typedef	typename Alloc::reference		reference;
				typedef	typename Alloc::pointer			pointer;
				typedef	typename Alloc::difference_type	difference_type;

				iterator();
				iterator(vector<T>* vec, T* vec_data, size_type index);
				~iterator();

				bool		operator==(const iterator& iter) const;
				bool		operator!=(const iterator& iter) const;
				bool		operator<(const iterator& iter) const;
				bool		operator>(const iterator& iter) const;
				bool		operator<=(const iterator& iter) const;
				bool		operator>=(const iterator& iter) const;

				iterator&	operator=(const iterator& iter);
				iterator&	operator++();
				iterator	operator++(int);
				iterator&	operator--();
				iterator	operator--(int);
				iterator&	operator+=(size_type index);
				iterator&	operator-=(size_type index);
				iterator	operator+(size_type	index) const;
				iterator	operator-(size_type	index) const;

				difference_type	operator-(iterator& iter) const;
				reference	operator*() const;
				pointer		operator->() const;	
				reference	operator[](size_type index) const;
			};
			*/

			iterator	begin()
			{
				return &_data[0];
			}
			iterator	end()
			{
				return &_data[_length];
			}
			const_iterator	begin() const
			{
				return &_data[0];
			}
			const_iterator	end() const
			{
				return &_data[_length];
			}
			

			iterator	insert(const_iterator pos, const T& value) //pos 값 이상할 때 체크하기
			{
				size_type	pos_index = pos - begin();
				insert(pos, 1, value);
				return (begin() + pos_index);
			}
			void	insert(const_iterator pos, size_type count, const T& value)
			{
				size_type	pos_index = pos - begin();
				if (_length + count > _capacity)
					reserve((_length + count) * 2);

				for (size_type i = 1; i <= _length - pos_index; i++)
					_data[_length - i + count] = _data[_length - i];
				for (size_type i = 0; i < count; i++)
					alloc.construct(&_data[pos_index + i], value);
				_length += count;
			}
			template<class InputIt>
			void	insert(const_iterator pos, InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_type	pos_index = pos - begin();

				size_type	count = 0;
				InputIt	temp = first;
				for (; temp != last; temp++)
					count++;
				if (_length + count > _capacity)
					reserve((_length + count) * 2);
				for (size_type i = 1; i <= _length - pos_index; i++)
					_data[_length - i + count] = _data[_length - i];
				for (size_type i = 0; i < count; i++)
				{
					_data[pos_index + i] = *first;
					first++;
				}
				_length += count;
			}
			void	resize(size_type count, T value = T() )
			{
				size_type	temp = _length;

				if (count > _length)
				{
					for (size_type i = 0; i < count - temp; i++)
						push_back(value);
				}
				else
				{
					for (size_type i = 0; i < temp - count; i++)
						pop_back();
				}
			}

			iterator	erase(iterator pos)
			{
				size_type	pos_index = pos - begin();
				
				alloc.destroy(&_data[pos_index]);
				for (size_type i = pos_index ; i < _length - 1; i++)
				{
					alloc.construct(&_data[i], _data[i + 1]);
					alloc.destroy(&_data[i + 1]);
				}
				_length--;
				return (&_data[pos_index]);
			}
			iterator	erase(iterator first, iterator last)
			{
				size_type	first_index = first - begin();
				size_type	last_index = last - begin();
				size_type	ret = first_index;
				size_type	count = 0;

				for (; first != last; first++)
				{
					alloc.destroy(first);
					count++;
				}
				while(last_index != _length)
				{
					alloc.construct(&_data[first_index], _data[last_index]);
					alloc.destroy(&_data[last_index]);
					first_index++;
					last_index++;
				}
				_length -= count;
				return (&_data[ret]);
			}

			void	swap(vector& other)
			{
				ft::swap(alloc, other.alloc);
				ft::swap(_capacity, other._capacity);
				ft::swap(_data, other._data);
				ft::swap(_length, other._length);
			}
	};
};


// template <typename T, typename Alloc>
// bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {
// 	if (lhs)
// 	return();	}
// template <typename T, typename Alloc>
// bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {	return !(lhs == rhs);	}
// template <typename T, typename Alloc>
// bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {

// }
// template <typename T, typename Alloc>
// bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {

// }
// template <typename T, typename Alloc>
// bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {

// }
// template <typename T, typename Alloc>
// bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {

// }
template <typename T, typename Alloc>
void	swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}

//iterator define
/*
template <typename T, typename U>
ft::vector<T, U>::iterator::iterator() : _vec(nullptr), _vec_data(nullptr), _index(0)
{}

template <typename T, typename U>
ft::vector<T, U>::iterator::iterator(vector<T>* vec, T* vec_data, size_type index)
:_vec(vec), _vec_data(vec_data), _index(index)
{}

template <typename T, typename U>
ft::vector<T, U>::iterator::~iterator()
{}

template <typename T, typename U>
bool ft::vector<T, U>::iterator::operator!=(const iterator& iter) const
{	return (this->_vec_data[this->_index] != iter._vec_data[iter._index]);	}

template <typename T, typename U>
bool ft::vector<T, U>::iterator::operator==(const iterator& iter) const
{	return (this->_vec_data[this->_index] == iter._vec_data[iter._index]);	}

template <typename T, typename U>
bool ft::vector<T, U>::iterator::operator<(const iterator& iter) const
{
	if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] < 0)
		return true;
	else
		return false;
}

template <typename T, typename U>
bool ft::vector<T, U>::iterator::operator>(const iterator& iter) const
{
	if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] > 0)
		return true;
	else
		return false;
}

template <typename T, typename U>
bool ft::vector<T, U>::iterator::operator<=(const iterator& iter) const
{
	if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] <= 0)
		return true;
	else
		return false;
}

template <typename T, typename U>
bool ft::vector<T, U>::iterator::operator>=(const iterator& iter) const
{
	if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] >= 0)
		return true;
	else
		return false;
}

template <typename T, typename U> //deep copy  할수 있게 바꿔야될수도
typename ft::vector<T, U>::iterator&	ft::vector<T, U>::iterator::operator=(const iterator& iter)
{
	this->_vec = iter._vec;
	this->_vec_data = iter._vec_data;
	this->_index = iter._index;
	return (*this);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator&	ft::vector<T, U>::iterator::operator++()
{
	this->_vec_data += 1;
	return (*this);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator	ft::vector<T, U>::iterator::operator++(int)
{
	iterator	temp;

	temp = *this;
	this->_vec_data += 1;
	return (temp);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator&	ft::vector<T, U>::iterator::operator--()
{
	this->_vec_data -= 1;
	return (*this);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator	ft::vector<T, U>::iterator::operator--(int)
{
	iterator	temp;

	temp = *this;
	this->_vec_data -= 1;
	return (temp);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator&	ft::vector<T, U>::iterator::operator+=(size_type index)
{
	_index += index;
	return (*this);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator&	ft::vector<T, U>::iterator::operator-=(size_type index)
{
	_index -= index;
	return (*this);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator	ft::vector<T, U>::iterator::operator+(size_type index) const
{
	iterator	temp;

	temp._vec = this->_vec;
	temp._vec_data = this->_vec_data;
	temp._index = this->_index + index;
	return (temp);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator	ft::vector<T, U>::iterator::operator-(size_type index) const
{
	iterator	temp;

	temp._vec = this->_vec;
	temp._vec_data = this->_vec_data;
	temp._index = this->_index - index;
	return (temp);
}

template <typename T, typename U>
typename ft::vector<T, U>::iterator::reference ft::vector<T, U>::iterator::operator*() const
{	return (_vec_data[_index]);	}

template <typename T, typename U>
typename ft::vector<T, U>::iterator::pointer ft::vector<T, U>::iterator::operator->() const
{	return (&_vec_data[_index]);	}

template <typename T, typename U>
typename ft::vector<T, U>::iterator::difference_type	ft::vector<T, U>::iterator::operator-(iterator& iter) const
{	return (this->_vec_data[this->_index] - iter._vec_data[iter._index]);	}

template <typename T, typename U>
typename ft::vector<T, U>::iterator::reference	ft::vector<T, U>::iterator::operator[](size_type index) const
{	return (this->_vec_data[index]);	}

template <typename T, typename U>
typename ft::vector<T, U>::iterator ft::vector<T, U>::begin()
{	return iterator(this, _data, 0);	}

template <typename T, typename U>
typename ft::vector<T, U>::iterator ft::vector<T, U>::end()
{	return iterator(this, _data, _length);	}
*/
#endif
