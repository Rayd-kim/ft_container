#ifndef FT_LIBRARY_HPP
#define	FT_LIBRARY_HPP

namespace ft{
	template <typename Iter>
	struct	iterator_traits{
		typedef typename	Iter::difference_type	difference_type;
		typedef typename	Iter::value_type		value_type;
		typedef typename	Iter::pointer			pointer;
		typedef typename	Iter::reference			reference;
		typedef typename	Iter::iterator_category	iterator_category;
		
	};

	template <typename T>
	struct iterator_traits<T*>{
		typedef	typename	std::ptrdiff_t					difference_type;
		typedef	T											value_type;
		typedef	T*											pointer;
		typedef	T&											reference;
		typedef typename	std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>{
		typedef typename	std::ptrdiff_t					difference_type;
		typedef	T											value_type;
		typedef	const T*									pointer;
		typedef	const T&									reference;
		typedef typename	std::random_access_iterator_tag	iterator_category;
	};

	template <typename Iter>
	struct	reverse_iterator{
		typedef	Iter														iterator_type;
		typedef typename	ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename	ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename	ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename	ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename	ft::iterator_traits<Iter>::reference			reference;



	};

	struct	enable_if{};

	struct	is_integral{};

	struct	equl{};
	
	struct	pair{};
	struct	make_pair{};


	template<typename T>
	void	swap(T& a, T& b)
	{
		T	temp = a;
		a = b;
		b = temp;
	}
};


#endif