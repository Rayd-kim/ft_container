#ifndef	MAP_HPP
#define	MAP_HPP

#include <iostream>

namespace ft{

template< typename Key, typename T, typename Compare = std::less<Key>,
typename Allocator = std::allocator<std::pair<const Key, T>> >
class map{
	private:

	public:
	typedef	Key									key_type;
	typedef	T									mapped_type;
	typedef	std::pair<const Key, T>				value_type;
	typedef	Compare								key_compare;
	typedef	Allocator							allocator_type;
	typedef	value_type&							reference;
	typedef	const value_type&					const_reference;
	typedef	typename Allocator::pointer			pointer;
	typedef	typename Allocator::const_pointer	const_pointer;
	typedef	typename Allocator::size_type		size_type;
	typedef	typename Allocator::difference_type	difference_type;



};



};




#endif