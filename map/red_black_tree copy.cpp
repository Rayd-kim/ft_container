#include <iostream>


#define red -1;
#define black -2;


template <typename T>
struct Node {
	T			*type;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;
	int			red_black;


	Node(){
		type = NULL;
		parent = NULL;
		left = NULL;
		right = NULL;
		red_black = red;
	}
};

//left_rotate
template <typename T>
void	left_rotate(Node<T> *node)
{
	Node<T>	*temp_parent;
	Node<T>	*node_left;

	node_left = node->left;  //node->left save
	temp_parent = node->parent->parent; //parent->parent save
	node->parent->right = node_left; //현재 노드의 부모노드의 오른쪽 노드를 현재 노드의 왼쪽으로 변경 
	node->left = node->parent; // 현재 노드의 왼쪽이 부모노드를 가리키도록 변경
	node->left->parent = node; // 원래 부모노드가 현재노드의 왼쪽으로 변경되었으므로, 원래 부모노드의 부모노드를 현재노드로 변경
	node->parent = temp_parent; // 현재노드의 부모노드를 원래의 부모의 부모노드로 변경
}

//right_rotate
template <typename T>
void	right_rotate(Node<T> *node)
{
	Node<T>	*temp_parent;
	Node<T>	*node_right;

	node_right = node->right; // 현재노드의 오른쪽 저장
	temp_parent = node->parent->parent; // 현재부모노드의 부모노드(조부모노드)를 저장
	node->parent->left = node_right; // 부모노드의 왼쪽노드(현재노드임)를 현재노드의 오른쪽으로 변경
	node->right = node->parent; // 현재 노드의 오른쪽이 부모노드를 가리키도록 변경
	node->right->parent = node;
	node->parent = temp_parent;
}

/*
template <typename T>
void	red_black_check(Node<T> *node)
{
	if (node->parent->red_black == black)
		return ;
	else
	{
		if (node->parent == node->parent->parent->left) //현재노드가 부모의 왼쪽기준일 때
		{
			if (node->parent->parent->right->red_black == red) // 부모, 자식, 삼촌노드도 red 일 때.
			{
				node->parent->red_black = black;
				node->parent->parent->right->red_black = black;
				node->parent->parent->red_black = red;
				red_black_check(node->parent->parent);
			}
			else if (node->parent->parent->right->red_black == black && )

		}
		else //현재 노드가 부모의 오른쪽기준일 때
		{

		}	
	}
}
*/


template <typename T>
void	insert_node(Node<T> *root, T *input)
{
	if (root == NULL)
	{
		root = new Node<T>;
		root->type = input;
		root->red_black = black;
	}
	else if (root != NULL && *input < *(root->type))
	{
		if (root->left == NULL)
		{
			root->left = new Node<T>;
			root->left->type = input;
			root->left->parent = root;
			// red_black_check(root->left);
		}
		else
			insert_node(root->left, input);
	}
	else if (root != NULL && *input > *(root->type))
	{
		if (root->right == NULL)
		{
			root->right = new Node<T>;
			root->right->type = input;
			root->right->parent = root;
			// red_black_check(root->right);
		}
		else
			insert_node(root->right, input);
	}
}

template <typename T>
void	inored_node(Node<T> *root)
{
	if (root == NULL)
		return ;
	inored_node(root->left);
	std::cout << (root->type) << std::endl;
	inored_node(root->right);
}

int	main(void)
{
	Node<std::string>	root;
	Node<int>			int_node;

	std::string a = "a";
	std::string b = "b";
	std::string c = "c";

	insert_node(&root, &a);
	insert_node(&root, &b);
	insert_node(&root, &c);

	int	one = 1;
	int two = 2;
	int three = 3;
	insert_node(&int_node, &one);
	insert_node(&int_node, &two);
	insert_node(&int_node, &three);

	inored_node(&root);
	inored_node(&int_node);

}