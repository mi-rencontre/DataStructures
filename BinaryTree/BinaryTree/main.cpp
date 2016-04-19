#include <iostream>
using namespace std;
#include <queue>
#include<stack>

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreatTree(a, size, index);
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}

	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		if (_root != t._root)
		{
			this->_delete(_root);
			_root = _Copy(t._root);
		}
		return *this;
	}

	BinaryTreeNode<T>* find(const T& x)
	{
		return _find(_root, x);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	void PrevOrder_NOR()
	{
		_PrevOrder_NOR(_root);
	}

	void InOrder_NOR()
	{
		_InOrder_NOR(_root);
	}

	void PostOrder_NOR()
	{
		_PostOrder_NOR(_root);
	}

	void LevelOrder()
	{
		_LevelOrder(_root);
		cout << endl;
	}

	int depth()
	{
		return _depth(_root);
	}

	int size()
	{
		return _size(_root);
	}

	~BinaryTree()
	{
		if (_root != NULL)
		{
			_delete(_root);
		}
	}
protected:
	BinaryTreeNode<T>* _CreatTree(const T* a, size_t size, size_t& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size)
		{
			if ('#' != a[index])
			{
				root = new BinaryTreeNode<T>(a[index]);
				root->_left = _CreatTree(a, size, ++index);
				root->_right = _CreatTree(a, size, ++index);
			}
		}
		return root;
	}

	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		BinaryTreeNode<T>* _root = new BinaryTreeNode<T>(root->_data);
		if (root->_left != NULL)
		{
			_root->_left = _Copy(root->_left);
		}
		if (root->_right != NULL)
		{
			_root->_right = _Copy(root->_right);
		}
		return _root;
	}

	BinaryTreeNode<T>* _find(BinaryTreeNode<T>* root, const T& x)
	{
		BinaryTreeNode<T>* bt = NULL;
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_data == x)
		{
			return root;
		}
		if (root->_left != NULL)
		{
			bt = _find(root->_left, x);
			if (bt != NULL)
			{
				return bt;
			}
		}
		if (root->_right != NULL)
		{
			bt = _find(root->_right, x);
			if (bt != NULL)
			{
				return bt;
			}
		}
		return NULL;
	}

	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _PrevOrder_NOR(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> s;
		s.push(root);
		while (!s.empty())
		{
			BinaryTreeNode<T>* ret = s.top();
			s.pop();
			cout << ret->_data << " ";
			if (ret->_right != NULL)
			{
				s.push(ret->_right);
			}
			if (ret->_left != NULL)
			{
				s.push(ret->_left);
			}
		}
		cout << endl;
	}

	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _InOrder_NOR(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* ret = root;
		while (ret || !s.empty())
		{
			while (ret)
			{
				s.push(ret);
				ret = ret->_left;
			}
			if (!s.empty())
			{
				ret = s.top();
				cout << ret->_data << " ";
				s.pop();
				ret = ret->_right;
			}
		}
		cout << endl;
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	void _PostOrder_NOR(BinaryTreeNode<T> *root)
	{
		if (root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T> *cur = root;
		BinaryTreeNode<T> *prevVisited = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode<T>* top = s.top();

			if (top->_right == NULL || top->_right == prevVisited)
			{
				cout << top->_data << " ";
				prevVisited = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}

	void _LevelOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		queue<BinaryTreeNode<T>*> q1;
		q1.push(root);
		while (!q1.empty())
		{
			BinaryTreeNode<T>* b1 = q1.front();
			q1.pop();
			cout << b1->_data << " ";
			if (b1->_left != NULL)
			{
				q1.push(b1->_left);
			}
			if (b1->_right != NULL)
			{
				q1.push(b1->_right);
			}
		}
	}

	int _size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		return _size(root->_left) + _size(root->_right) + 1;
	} 

	int _depth(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int ldepth = _depth(root->_left);
		int rdepth = _depth(root->_right);
		return ldepth > rdepth ? ldepth+1 :rdepth + 1;
	}

	void _delete(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}	
		_delete(root->_left);
		_delete(root->_right);
		delete root;
		root = NULL;
	}

private:
	BinaryTreeNode<T>* _root;
};

int main()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t1(a, 10);
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	BinaryTree<int> t2(t1);
	t2 = t1;
	cout<<t1.size()<<endl;
	cout << t1.depth() << endl;
	cout << t1.find(4)->_data << endl; 
	t1.PrevOrder_NOR();
	t1.InOrder_NOR(); 
	t1.PostOrder_NOR();
	return 0;
}