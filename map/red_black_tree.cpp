#include <iostream>

#define RED 	1
#define BLACK	2

template <typename _pair>
struct Node {
	public:
	_pair	value;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		red_black;
	
	// const static Node	*nil = new Node();

	Node(_pair pair) : value(pair), parent(NULL), left(NULL), right(NULL), red_black(RED) //일반 insert때의 노드 생성
	{}

	Node() : parent(NULL), left(NULL), right(NULL), red_black(BLACK)//leaf node(nil_node) 생성
	{}
	
};

template<typename _pair, typename Compare = std::less<_pair> >
class RB_tree{
	private:

	public:
	typedef	_pair		value_type;
	typedef	_pair&		reference;
	typedef	Node<_pair>	node_type;
	typedef	node_type*	node_pointer;
	
	Node<_pair>	*root;
	Node<_pair>	*insert_temp;
	Node<_pair>	*nil;

	RB_tree() : root(NULL), insert_temp(NULL)
	{
		nil = new Node<_pair>;
	}

	Node<_pair>* create_new_node(_pair pair)
	{
		Node<_pair>	*ret = new Node<_pair>(pair);
		ret->left = nil;
		ret->right = nil;
		return (ret);
	}

	void	insert_node(_pair pair)
	{
		if (root == NULL) //root node 설정. (지금은 안쓰이는 형태..)
		{
			root = create_new_node(pair);
			root->red_black = BLACK;
			insert_temp = root;
		}
		else if (pair.first < insert_temp->value.first)
		{
			if (insert_temp->left == nil)
			{
				insert_temp->left = create_new_node(pair);
				insert_temp->left->parent = insert_temp;
				red_black_check(insert_temp->left);
				insert_temp = root;
			}
			else
			{
				insert_temp = insert_temp->left;
				insert_node(pair);
			}
		}
		else if (pair.first > insert_temp->value.first)
		{
			if (insert_temp->right == nil)
			{
				insert_temp->right = create_new_node(pair);
				insert_temp->right->parent = insert_temp;
				red_black_check(insert_temp->right);
				insert_temp = root;
			}
			else
			{
				insert_temp = insert_temp->right;
				insert_node(pair);
			}
		}
		else
			insert_temp = root;
	}

	void	inored_node(Node<_pair> *root)
	{
		if (root == NULL || root == nil)
			return ;
		inored_node(root->left);
		std::cout << root->value.second << std::endl;
		inored_node(root->right);
	}

	void	left_rotate(Node<_pair> *node)
	{
		Node<_pair>	*temp_parent;
		Node<_pair>	*node_left;

		node_left = node->left;  //node->left save
		temp_parent = node->parent->parent; //parent->parent save
		node->parent->right = node_left; //현재 노드의 부모노드의 오른쪽 노드를 현재 노드의 왼쪽으로 변경 
		node->left = node->parent; // 현재 노드의 왼쪽이 부모노드를 가리키도록 변경
		node->left->parent = node; // 원래 부모노드가 현재노드의 왼쪽으로 변경되었으므로, 원래 부모노드의 부모노드를 현재노드로 변경
		node->parent = temp_parent; // 현재노드의 부모노드를 원래의 부모의 부모노드로 변경


		if (node->parent == NULL) //root node일 때
			root = node;
		else
		{
			if (node->parent->right == node->left)
				node->parent->right = node;
			else
				node->parent->left = node;
		}
	}

	void	right_rotate(Node<_pair> *node)
	{
		Node<_pair>	*temp_parent;
		Node<_pair>	*node_right;


		node_right = node->right; // 현재노드의 오른쪽 저장
		temp_parent = node->parent->parent; // 현재부모노드의 부모노드(조부모노드)를 저장

		node->parent->left = node_right; // 부모노드의 왼쪽노드(현재노드임)를 현재노드의 오른쪽으로 변경
		node->right = node->parent; // 현재 노드의 오른쪽이 부모노드를 가리키도록 변경
		node->right->parent = node;
		node->parent = temp_parent;


		if (node->parent == NULL)
			root = node;
		else
		{
			if (node->parent->right == node->right) //parent의 좌우 노드 재설정
				node->parent->right = node;
			else
				node->parent->left = node;
		}
	}

	void	red_black_check(Node<_pair> *node)
	{
		if (node->parent == NULL) //node is root
		{
			node->red_black = BLACK;
			return ;
		}
		else if (node->parent->red_black == BLACK) // 부모가 black 이면 새로 붙여진게 red여도 ok
			return ;
		else
		{
			if (node->parent == node->parent->parent->left) //현재노드가 부모의 왼쪽기준일 때
			{
				Node<_pair>	*node_parent = node->parent;
				Node<_pair>	*node_grand_parent = node->parent->parent;

				if (node_parent->red_black == RED && node_grand_parent->right->red_black == RED)// 부모, 자식, 삼촌노드도 red 일 때.
				{
					node_parent->red_black = BLACK;
					node_grand_parent->right->red_black = BLACK;
					node_grand_parent->red_black = RED;
					red_black_check(node_grand_parent);
				}
				else if (node_grand_parent->right->red_black == BLACK && node == node_parent->right) //삼촌노드가 블랙이고, 자식이 부모의 오른쪽일때
				{
					left_rotate(node_parent);
					red_black_check(node->left);
				}
				else
				{
					node_parent->red_black = BLACK;
					node_grand_parent->red_black = RED;
					right_rotate(node_parent);
				}

			}
			else //현재 노드가 부모의 오른쪽기준일 때
			{
				Node<_pair>	*node_parent = node->parent;
				Node<_pair>	*node_grand_parent = node->parent->parent;

				if (node_parent->red_black == RED && node_grand_parent->left->red_black == RED)// 부모, 자식, 삼촌노드도 red 일 때.
				{
					node_parent->red_black = BLACK;
					node_grand_parent->left->red_black = BLACK;
					node_grand_parent->red_black = RED;
					red_black_check(node_grand_parent);
				}
				else if (node_grand_parent->left->red_black == BLACK && node == node_parent->left) //삼촌노드가 블랙이고, 자식이 부모의 오른쪽일때
				{
					right_rotate(node_parent);
					red_black_check(node->right);
				}
				else
				{
					node_parent->red_black = BLACK;
					node_grand_parent->red_black = RED;
					left_rotate(node_parent);
				}
			}	
		}
	}

	
	

};

int	main(void)
{
	RB_tree<std::pair<int, std::string> >	rb_tree;

	rb_tree.insert_node(make_pair(1, (std::string)"1"));
	rb_tree.insert_node(make_pair(2, (std::string)"2"));
	rb_tree.insert_node(make_pair(5, (std::string)"5"));

	// std::cout << rb_tree.root->red_black << std::endl;
	// std::cout << rb_tree.root->left->red_black << std::endl;
	// std::cout << rb_tree.root->right->red_black << std::endl;

	// std::cout << rb_tree.root->value.second << std::endl;
	// std::cout << rb_tree.root->value.second << std::endl;

	rb_tree.insert_node(make_pair(4, (std::string)"4"));
	rb_tree.insert_node(make_pair(3, (std::string)"3"));
	rb_tree.insert_node(make_pair(3, (std::string)"3"));
	rb_tree.insert_node(make_pair(6, (std::string)"6"));
	rb_tree.insert_node(make_pair(8, (std::string)"8"));
	rb_tree.insert_node(make_pair(7, (std::string)"7"));
	rb_tree.insert_node(make_pair(10, (std::string)"10"));
	rb_tree.insert_node(make_pair(11, (std::string)"11"));

	// std::cout << rb_tree.root->value.second << std::endl;
	// std::cout << rb_tree.root->right->value.second << std::endl;
	// std::cout << rb_tree.root->right->left->value.second << std::endl;
	// std::cout << rb_tree.root->right->value.second << std::endl;
	
	
	// std::cout << rb_tree.root->left->value.second << std::endl;
	// std::cout << rb_tree.root->right->value.second << std::endl;
	rb_tree.inored_node(rb_tree.root);
	// system("leaks a.out");
}