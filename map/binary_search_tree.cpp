#include <iostream>


struct Node {
	int	num;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;

	Node(){
		num = -1;
		parent = NULL;
		left = NULL;
		right = NULL;
	}
};

void	insert_node(Node *root, int n)
{
	Node	*temp;

	temp = root;
	if (n < root->num)
	{
		if (temp->left == NULL)
		{
			temp->left = new Node;
			temp->left->num = n;
			temp->left->parent = temp;
		}
		else
			insert_node(temp->left, n);
	}
	else if (n > root->num)
	{
		if (temp->right == NULL)
		{
			temp->right = new Node;
			temp->right->num = n;
			temp->right->parent = temp;
		}
		else
			insert_node(temp->right, n);
	}
	else
		;
}

// void	remove_node(Node *root)
// {

// }

void	inored_node(Node *root)
{
	if (root == NULL)
		return ;
	
	inored_node(root->left);
	printf("%d ", root->num);
	inored_node(root->right);
}

int	main(void)
{

	Node	root;

	root.num = 50;
	insert_node(&root, 70);
	insert_node(&root, 60);
	insert_node(&root, 40);
	insert_node(&root, 30);
	insert_node(&root, 20);
	insert_node(&root, 10);

	inored_node(&root);
}