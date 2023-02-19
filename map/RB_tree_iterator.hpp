#ifndef RB_TREE_ITERATOR_HPP
#define RB_TREE_ITERATOR_HPP

#include "RB_tree_compare_version.hpp"

template <typename _pair>
class	tree_iterator{
	public:
	typedef std::bidirectional_iterator_tag					iterator_category;
	typedef	_pair											value_type;
	typedef	value_type&										reference;
	typedef	value_type*										pointer;
	typedef	std::ptrdiff_t									difference_type;
	typedef	typename RB_tree<_pair>::node_pointer			node_pointer;

	private:
	node_pointer		_node;
	RB_tree<_pair>		__tree;

	public:
	tree_iterator() : _node(), __tree() {}
	tree_iterator(node_pointer node, RB_tree<_pair> _tree): _node(node), __tree(_tree) {}
	
	tree_iterator(const tree_iterator& other) : _node(other._node), __tree(other.__tree) {}
	~tree_iterator() {}
	
	tree_iterator&	operator=(const tree_iterator& other)
	{
		_node = other._node;
		__tree = other.__tree;
		return (*this);
	}
	tree_iterator&	operator++()
	{
		_node = __tree.next_node(_node);
		return *this;
	}
	tree_iterator	operator++(int)
	{
		tree_iterator	temp = *this;
		_node = __tree.next_node(_node);
		return temp;
	}
	tree_iterator&	operator--()
	{
		_node = __tree.prev_node(_node);
		return *this;
	}
	tree_iterator	operator--(int)
	{
		tree_iterator	temp = *this;
		_node = __tree.prev_node(_node);
		return temp;
	}
	reference	operator*() const
	{	return (_node->value);	}
	pointer		operator->() const
	{	return &(_node->value);	}

	bool	operator==(const tree_iterator& other) const
	{	return _node == other._node;	}
	bool	operator!=(const tree_iterator& other) const
	{	return !(*this == other);	}
};

#endif