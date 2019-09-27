#include<iostream>
#include<conio.h>

using namespace std;

struct tree
{
	int key;
	int balance;
	tree* right = NULL;
	tree* left = NULL;
};

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

int set_balance(tree* root)
{
	if (root == NULL) return 0;
	int hl = set_balance(root->left);
	int hr = set_balance(root->right);
	root->balance = hl - hr;
	return (max(hl, hr) + 1);
}

tree* balance(tree* root)
{
	set_balance(root);
	if (root->balance > 1 && root->left->balance >= 0)
	{
		tree* help = root->left;
		root->left = help->right;
		help->right = root;
		return help;
	}
	else if (root->balance < -1 && root->right->balance <= 0)
	{
		tree* help = root->right;
		root->right = help->left;
		help->left = root;
		return help;
	}
	else if (root->balance > 1 && root->left->balance < 0)
	{
		tree* help1 = root->left;
		tree* help2 = root->left->right;
		help1->right = help2->left;
		help2->left = help1;
		root->left = help2->right;
		help2->right = root;
		return help2;
	}
	else if (root->balance < -1 && root->right->balance > 0)
	{
		tree* help1 = root->right;
		tree* help2 = root->right->left;
		help1->left = help2->right;
		help2->right = help1;
		root->right = help2->left;
		help2->left = root;
		return help2;
	}
	else return root;
}

tree* add(tree* root, int key)
{
	if (root == NULL)
	{
		root = new tree;
		root->key = key;
		root->balance = 0;
		return root;
	}
	else if (key == root->key)
	{
		cout << "Такой элемент уже существует.";
		return root;
	}
	else if (key > root->key)
	{
		root->right = add(root->right, key);
		return balance(root);
	}
	else if (key < root->key, key)
	{
		root->left = add(root->left, key);
		return balance(root);
	}
}

tree* creat_tree(tree* root)
{
	int key = 1;
	while(1)
	{
		cout << "Введите значение нового элемента дерева, для остановки введите 0: ";
		cin >> key;
		if (key == 0)break;
		root=add(root, key);
	}
	return root;
}

tree* print(tree* root) // префиксный обход
{
	if (root == NULL) return root;
	cout << root->key << " ";
	print(root->left);
	print(root->right);
	return root;
}

tree* del(tree* root, int key)
{
	if (root == NULL)
	{
		cout << "Элемент не найден.";
		return root;
	}
	else if (key > root->key)
	{
		root->right = del(root->right, key);
		root=balance(root);
	}
	else if (key < root->key)
	{
		root->left = del(root->left, key);
		root=balance(root);
	}
	else if (root->left != NULL && root->right != NULL)
	{
		tree* help = root->right;
		while (help->left != NULL) help = help->left;
		root->key = help->key;
		root->right = del(root->right, root->key);
	}
	else
	{
		if (root->left != NULL) root = root->left;
		else root = root->right;
	}
	return root;
}

struct rbtree
{
	int key;
	bool color;
	rbtree* left = NULL;
	rbtree* right = NULL;
};

rbtree* rbbalance(rbtree* root)
{
	if ((root->left != NULL && root->left->left != NULL && root->right != 0 && root->left->color==0 && root->left->left->color == 0 && root->right->color == 0) || 
		(root->left != NULL && root->left->right != NULL && root->right != NULL && root->left->color == 0 && root->left->right->color == 0 && root->right->color == 0) ||
		(root->right != NULL && root->right->left!= NULL && root->left != NULL && root->right->color == 0 && root->right->left->color == 0 && root->left->color == 0) ||
		(root->right != NULL && root->right->right != NULL && root->left!= NULL && root->right->color == 0 && root->right->right->color == 0 && root->left->color == 0))
	{
		root->color = 0;
		root->left->color = 1;
		root->right->color = 1;
		return root;
	}
	else if ((root->left != NULL && root->left->left != NULL && root->left->color == 0 && root->left->left->color == 0 && root->right == NULL)|| (root->left != NULL && root->left->left != NULL && root->left->color == 0 && root->left->left->color == 0 && root->right->color == 1))
	{
		root->color = 0;
		root->left->color = 1;
		rbtree* help = root->left;
		root->left = help->right;
		help->right = root;
		return help;
	}
	else if ((root->right != NULL && root->right->right != NULL && root->right->color == 0 && root->right->right->color == 0 && root->left == NULL)|| (root->right != NULL && root->right->right != NULL && root->right->color == 0 && root->right->right->color == 0 && root->left->color == 1))
	{
		root->color = 0;
		root->right->color = 1;
		rbtree* help = root->right;
		root->right = help->left;
		help->left = root;
		return help;
	}
	else if ((root->left != NULL && root->left->right != NULL && root->left->color == 0 && root->left->right->color == 0 && root->right == NULL)|| (root->left != NULL && root->left->right != NULL && root->left->color == 0 && root->left->right->color == 0 && root->right->color == 1))
	{
		root->color = 0;
		root->left->right->color = 1;
		rbtree* help1 = root->left;
		rbtree* help2 = root->left->right;
		help1->right = help2->left;
		help2->left = help1;
		root->left = help2->right;
		help2->right = root;
		return help2;
	}
	else if ((root->right != NULL && root->right->left != NULL && root->right->color == 0 && root->right->left->color == 0 && root->left == NULL)|| (root->right != NULL && root->right->left != NULL && root->right->color == 0 && root->right->left->color == 0 && root->left->color == 1))
	{
		root->color = 0;
		root->right->left->color = 1;
		rbtree* help1 = root->right;
		rbtree* help2 = root->right->left;
		help1->left = help2->right;
		help2->right = help1;
		root->right = help2->left;
		help2->left = root;
		return help2;
	}
	else return root;
}

rbtree* rbadd(rbtree* root, int key)
{
	if (root == NULL)
	{
		root = new rbtree;
		root->key = key;
		root->color = 0;
		return root;
	}
	else if (key == root->key)
	{
		cout << "Такой элемент уже существует.";
		return root;
	}
	else if (key > root->key)
	{
		root->right = rbadd(root->right, key);
		return rbbalance(root);
	}
	else if (key < root->key, key)
	{
		root->left = rbadd(root->left, key);
		return rbbalance(root);
	}
}

rbtree* rbcreat_tree(rbtree* root)
{
	int key = 1;
	while (1)
	{
		cout << "Введите значение нового элемента дерева, для остановки введите 0: ";
		cin >> key;
		if (key == 0)break;
		root = rbadd(root, key);
		root->color = 1;
	}
	return root;
}

rbtree* rbprint(rbtree* root) // префиксный обход
{
	if (root == NULL) return root;
	cout << root->key<<root->color<<" ";
	rbprint(root->left);
	rbprint(root->right);
	return root;
}

rbtree* rbdelbalance(rbtree* root, int* &bflag)
{
	if (*bflag == 1 && root != NULL && root->color == 0 && (root->left == NULL || root->left->color == 1) && root->right != NULL && root->right->color == 1 &&
		(root->right->right == NULL || root->right->right->color == 1) && (root->right->left == NULL || root->right->left->color == 1))
	{
		root->color = 1;
		root->right->color = 0;
		*bflag = 0;
		return root;
	}
	else if (*bflag == -1 && root != NULL && root->color == 0 && (root->right == NULL || root->right->color == 1) && root->left != NULL && root->left->color == 1 &&
		(root->left->left == NULL || root->left->left->color == 1) && (root->left->right == NULL || root->left->right->color == 1))
	{
		root->color = 1;
		root->left->color = 0;
		*bflag = 0;
		return root;
	}
	else if (*bflag == 1 && root != NULL && (root->left == NULL || root->left->color == 1) && root->right != NULL && root->right->color == 1 &&
		root->right->right != NULL && root->right->right->color == 0)
	{
		root->right->right->color = 1;
		root->right->color = root->color;
		root->color = 1;
		rbtree* help = root->right;
		root->right = help->left;
		help->left = root;
		*bflag = 0;
		return help;
	}
	else if (*bflag == -1 && root != NULL && (root->right == NULL || root->right->color == 1) && root->left != NULL && root->left->color == 1 &&
		root->left->left != NULL && root->left->left->color == 0)
	{
		root->left->left->color = 1;
		root->left->color = root->color;
		root->color = 1;
		rbtree* help = root->left;
		root->left = help->right;
		help->right = root;
		*bflag = 0;
		return help;
	}
	else if (*bflag == 1 && root != NULL && (root->left == NULL || root->left->color == 1) && root->right != NULL && root->right->color == 1 &&
		(root->right->right == NULL || root->right->right->color == 1) && root->right->left != NULL && root->right->left->color == 0)
	{
		root->right->left->color = 1;
		root->right->color = 0;
		rbtree* help = root->right;
		rbtree* help1 = root->right->left;
		help->left = help1->right;
		help1->right = help;
		root->right = help1;
		*bflag = 1;
		root=rbdelbalance(root, bflag);
		return root;
	}
	else if (*bflag == -1 && root != NULL && (root->right == NULL || root->right->color == 1) && root->left != NULL && root->left->color == 1 &&
		(root->left->left == NULL || root->left->left->color == 1) && root->left->right != NULL && root->left->right->color == 0)
	{
		root->left->right->color = 1;
		root->left->color = 0;
		rbtree* help = root->left;
		rbtree* help1 = root->left->right;
		help->right = help1->left;
		help1->left = help;
		root->left = help1;
		*bflag = -1;
		root=rbdelbalance(root, bflag);
		return root;
	}
	else if (*bflag == 1 && root != NULL && root->color == 1 && (root->left == NULL || root->left->color == 1) && root->right != NULL && root->right->color == 0 &&
		(root->right->right == NULL || root->right->right->color == 1) && (root->right->left == NULL || root->right->left->color == 1))
	{
		root->right->color = 1;
		root->color = 0;
		rbtree* help = root->right;
		root->right = help->left;
		help->left = root;
		*bflag = 1;
		root=rbdelbalance(root, bflag);
		return help;
	}
	else if (*bflag == -1 && root != NULL && root->color == 1 && (root->right == NULL || root->right->color == 1) && root->left != NULL && root->left->color == 0 &&
		(root->left->left == NULL || root->left->left->color == 1) && (root->left->right == NULL || root->left->right->color == 1))
	{
		root->left->color = 1;
		root->color = 0;
		rbtree* help = root->left;
		root->left = help->right;
		help->right = root;
		*bflag = -1;
		root=rbdelbalance(root, bflag);
		return help;
	}
	else if (*bflag == 1 && root != NULL && root->color == 1 && (root->left == NULL || root->left->color == 1) && root->right != NULL && root->right->color == 1 &&
		(root->right->right == NULL || root->right->right->color == 1) && (root->right->left == NULL || root->right->left->color == 1))
	{
		root->right->color = 0;
		*bflag = 1;
		return root;
	}
	else if (*bflag == -1 && root != NULL && root->color == 1 && (root->right == NULL || root->right->color == 1) && root->left != NULL && root->left->color == 1 &&
		(root->left->left == NULL || root->left->left->color == 1) && (root->left->right == NULL || root->left->right->color == 1))
	{
		root->left->color = 0;
		*bflag = 1;
		return root;
	}
}

rbtree* rbdel(rbtree* root, int key, bool* &flag)
{
	if (root == NULL)
	{
		cout << "Элемент не найден.";
		*flag = 0;
		return root;
	}
	else if (key > root->key)
	{
		root->right = rbdel(root->right, key, flag);
		if (*flag == 1)
		{
			int help = -1;
			int* bflag = &help;
			root = rbdelbalance(root, bflag);
			if (*bflag == 1 || *bflag == -1) *flag = 1;
			else *flag = 0;
		}
	}
	else if (key < root->key)
	{
		root->left = rbdel(root->left, key, flag);
		if (*flag == 1)
		{
			int help = 1;
			int* bflag = &help;
			root = rbdelbalance(root, bflag);
			if (*bflag == 1 || *bflag == -1) *flag = 1;
			else *flag = 0;
		}
	}
	else if (root->left != NULL && root->right != NULL)
	{
		rbtree* help = root->right;
		while (help->left != NULL) help = help->left;
		root->key = help->key;
		root->right = rbdel(root->right, root->key, flag);
		if (*flag == 1)
		{
			int help = -1;
			int* bflag = &help;
			root = rbdelbalance(root, bflag);
			if (*bflag == 1 || *bflag == -1) *flag = 1;
			else *flag = 0;
		}
		return root;
	}
	else if (root->left != NULL)
	{
		if (root->color == 0)
		{
			root = root->left;
			*flag = 0;
		}
		else if (root->color == 1 && root->left->color == 0)
		{
			root = root->left;
			root->color = 1;
			*flag = 0;
		}
		else if (root->color == 1 && root->left->color == 1)
		{
			root = root->left;
			*flag = 1;
		}
	}
	else if (root->right != NULL)
	{
		if (root->color == 0)
		{
			root = root->right;
			*flag = 0;
		}
		else if (root->color == 1 && root->right->color == 0)
		{
			root = root->right;
			root->color = 1;
			*flag = 0;
		}
		else if (root->color == 1 && root->right->color == 1)
		{
			root = root->right;
			*flag = 1;
		}
	}
	else
	{
		if (root->color==1)*flag = 1;
		else *flag = 0;
		return NULL;
	}
	return root;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "АВЛ\n";
	tree* root = NULL;
	root = creat_tree(root);
	root = print(root);
	int key = 0;
	cout << "\nВведите элемент, который нужно удалить: ";
	cin >> key;
	root = del(root, key);
	root = print(root);
	cout << "\n";
	cout << "Красно-черное\n";
	rbtree* rbroot = NULL;
	rbroot = rbcreat_tree(rbroot);
	rbroot = rbprint(rbroot);
	key = 0;
	cout << "\nВведите элемент, который нужно удалить: ";
	cin >> key;
	bool help = 0;
	bool* flag = &help;
	rbroot = rbdel(rbroot, key, flag);
	rbroot->color = 1;
	rbroot = rbprint(rbroot);
	_getch();
}