#ifndef	MAP_HPP
#define	MAP_HPP

#include "RB_tree.hpp"

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
		RB_tree	_tree;

	public:

	//constructor & destructor
	map() : _tree() {};
	explicit map(const Compare& comp, const Allocator& alloc = Allocator() );
	
	template<class InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() );

	map(const map& other) : _tree(other._tree) {}
	~map();
	
	map& operator=(const map& other);

	//member function
	allocator_type	get_allocator() const; //Returns the allocator associated with the container
	T& at(const Key& key) //if no such element exists, an exception of type std::out_of_range is thrown.
	{	return _tree.at();	}
	const T& at(const Key& key) const
	{	return _tree.at();	}
	T& operator[](const Key& key)
	{
		typename RB_tree::node_pointer	node;
		node = _tree.search_key(key);
		if (node == RB_tree::nil)
		{
			_tree.insert_node(std::make_pair(key, 0));
			return &(_tree.search_key(key).second);
		}
		return &node.second;
	}

	bool empty() const // checks if the container has no elements, i.e. whether begin() == end()
	{
		if (_tree.size() == 0)
			return true;
		return false;
	}
	size_type size() const // Returns the number of elements in the container, i.e. std::distance(begin(), end())
	{	return _tree.size();	}
	size_type max_size() const // Key, T 가 아니라 rb_tree에서 노드갯수로?
	{	return _tree.max_size();	}
	void clear(); //vector 랑 다르게 capacity는 없으니까, size만 0으로

	std::pair<iterator, bool> insert(const value_type& value);
	iterator insert(iterator pos, const value_type& value);
	
	template<class InputIt>
	void insert(InputIt first, InputIt last);

	iterator erase(itertor pos);
	iterator erase(iterator first, iterator last);
	size_type erase(const Key& key); // Removes the element(if one exists) with the key equivalent to key.

	void swap(map& other)
	{	ft::swap(_tree, other._tree);	}	
	size_type count(const Key& key) const //key에 해당하는 값이 몇개있는지. 0 or 1 중 하나임(중복을 허용하지 않기 때문에)
	{
		typename RB_tree::node_type	node;
		node = RB_tree::search_key(key);
		if (node == RB_tree::nil)
			return (0);
		return (1);
	}
	
	iterator find(const Key& key);
	const_iterator find(const Key& key) const;
	
	std::pair<iterator, iterator> equal_range(const Key& key);
	std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

	iterator lower_bound(const Key& key);
	const_iterator lower_bound(const Key& key) const;
	iterator upper_bound(const Key& key);
	const_iterator upper_bound(const Key& key) const;
	
	class value_compare{
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:		
			bool operator()(const value_type& lhs, const value_type& rhs) const{
				return comp(lhs.first, rhs.first);
			}
	};

		class	iterator{
		public:
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef	typename Alloc::value_type		value_type;
		typedef	typename Alloc::reference		reference;
		typedef	typename Alloc::pointer			pointer;
		typedef	typename Alloc::difference_type	difference_type;

		private:
		value_type	

		public:
		iterator();
		~iterator();
		
		bool		operator==(const iterator& other) const;
		bool		operator!=(const iterator& other) const;
		bool		operator<(const iterator& other) const;
		bool		operator<=(const iterator& other) const;
		bool		operator>(const iterator& other) const;
		bool		operator>=(const iterator& other) const;
		iterator&	operator=(const iterator& other);
		iterator&	operator++();
		iterator	operator++(int);
		iterator&	operator--();
		iterator	operator--(int);
		reference	operator*() const;
		pointer		operator->() const;


	};

};



};




#endif