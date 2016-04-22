#include<iostream>
using namespace std;

template<class K, class V>
struct BSTNode
{
	K _key;
	V _value;
	BSTNode* _left;
	BSTNode* _right;

	BSTNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
public:

	BSTree()
		:_root(NULL)
	{}

	//·ÇµÝ¹é
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		return true;
	}

	//µÝ¹é
	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}

	Node* Find(const K& key)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}
		return cur;
	}

	//·ÇµÝ¹é
	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		if (_root->_left == NULL && _root->_right == NULL)
		{
			delete _root;
			_root = NULL;
			return true;
		}

		Node *parent = _root;
		Node *del = _root;
		while (del)
		{
			if (key < del->_key)
			{
				parent = del;
				del = del->_left;
			}
			else if (key > del->_key)
			{
				parent = del;
				del = del->_right;
			}
			else
			{
				break;
			}
		}
		if (del == NULL)
		{
			return false;
		}

		if (del->_left == NULL)
		{
			if (del == _root)
			{
				_root = del->_right;
			}
			else
			{
				if (parent->_left == del)
				{
					parent->_left = del->_right;
				}
				else
				{
					parent->_right = del->_right;
				}
			}
		}
		else if (del->_right == NULL)
		{
			if (del == _root)
			{
				_root = del->_left;
			}
			else
			{
				if (parent->_left == del)
				{
					parent->_left = del->_left;
				}
				else
				{
					parent->_right = del->_left;
				}
			}
		}
		else
		{
			Node* sub = del;
			Node* First = del->_right;
			while (First->_left)
			{
				sub = First;
				First = First->_left;
			}
			swap(del->_key, First->_key);
			swap(del->_value, First->_value);
			del = First;
			if (del->_left == NULL)
			{
				if (sub->_left == del)
				{
					sub->_left = del->_right;
				}
				else
				{
					sub->_right = del->_right;
				}
			}
			else if (del->_right == NULL)
			{
				if (sub->_left == del)
				{
					sub->_left = del->_left;
				}
				else
				{
					sub->_left = del->_left;
				}
			}
		}
		delete del;
		del = NULL;
		return true;
	}

	//µÝ¹é
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

protected:

	bool _Insert_R(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		if (key < root->_key)
		{
			return _Insert_R(root->_left, key, value);
		}
		else if (key > root->_key)
		{
			return _Insert_R(root->_right, key, value);
		}
		else
		{
			return false;
		}
	}

	bool _Remove_R(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (key < root->_key)
		{
			return _Remove_R(root->_left, key);
		}
		else if (key > root->_key)
		{
			return _Remove_R(root->_right, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* First = root->_right;
				while (First->_left)
				{
					First = First->_left;
				}
				swap(del->_key, First->_key);
				swap(del->_value, First->_value);
				return _Remove_R(root->_right, key);
			}
			delete del;
			del = NULL;
			return true;
		}
	
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

private:
	BSTNode<K, V>* _root;
};

int main()
{
	int a[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> bst;
	for (int i = 0; i < 10; i++)
	{
		bst.Insert_R(a[i], a[i]);
	}
	bst.InOrder();
	bst.Find(7);
	for (int i = 9; i >= 0; i--)
	{
		bst.Remove(i);
		bst.InOrder();
	}
	return 0;
}