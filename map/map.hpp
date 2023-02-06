#ifndef	MAP_HPP
#define	MAP_HPP

#include <iostream>


namespace ft{

template< typename Key, typename T, typename Compare = std::less<Key>,
typename Allocator = std::allocator<std::pair<const Key, T> > >
class map{

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

	private:
		// rb_tree	tree;

	public:

	//constructor & destructor
	map();
	explicit map(const Compare& comp, const Allocator& alloc = Allocator() );
	
	template<class InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() );

	map(const map& other);
	~map();
	
	map& operator=(const map& other);

	//member function
	allocator_type	get_allocator() const; //Returns the allocator associated with the container
	T& at(const Key& key); //if no such element exists, an exception of type std::out_of_range is thrown.
	const T& at(const Key& key) const;
	T& operator[](const Key& key);

	bool empty() const; // checks if the container has no elements, i.e. whether begin() == end()
	size_type size() const; // Returns the number of elements in the container, i.e. std::distance(begin(), end())
	size_type max_size() const; // Key, T 가 아니라 rb_tree에서 노드갯수로?

	void clear(); //vector 랑 다르게 capacity는 없으니까, size만 0으로

	std::pair<iterator, bool> insert(const value_type& value);
	iterator insert(iterator pos, const value_type& value);
	
	template<class InputIt>
	void insert(InputIt first, InputIt last);

	iterator erase(itertor pos);
	iterator erase(iterator first, iterator last);
	size_type erase(const Key7 key); // Removes the element(if one exists) with the key equivalent to key.

	void swap(map& other);	
	size_type count(const Key& key) const; //key에 해당하는 값이 몇개있는지. 0 or 1 중 하나임(중복을 허용하지 않기 때문에)
	
	iterator find(const Key& key);
	const_iterator find(const Key& key) const;
	
	std::pair<iterator, iterator> equal_range(const Key& key);
	std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

	iterator lower_bound(const Key& key);
	const_iterator lower_bound(const Key& key) const;
	iterator upper_bound(const Key& key);
	const_iterator upper_bound(const Key& key) const;
	
	class value_compare{
		public:
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:		
			bool operator()(const value_type& lhs, const value_type& rhs) const{
				return comp(lhs.first, rhs.first);
			}
	};

};



};




#endif