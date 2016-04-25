#include<iostream>
using namespace std;

#include<stack> 

enum PointerTag 
{ 
	THREAD, 
	LINK 
};

template <class T>
struct BinaryTreeNode_Thd
{
	T _data;                         // 数据
	BinaryTreeNode_Thd<T >* _left;   // 左孩子
	BinaryTreeNode_Thd<T >* _right;  // 右孩子
	PointerTag   _leftTag;          // 左孩子线索标志
	PointerTag   _rightTag;         // 右孩子线索标志

	BinaryTreeNode_Thd(const T &data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

template<class T>
class BinaryTree_Thd
{
public:
	BinaryTree_Thd()
		:_root(NULL)
	{}

	BinaryTree_Thd(const T* a,size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(a, size ,index);
	}
	void PrevOrder_Thread()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_PrevOrder_Thread(_root, prev);
	}

	void InOrder_Thread()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_InOrder_Thread(_root, prev);
	}

	void PostOrder_Thread()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_PostOrder_Thread(_root, prev);
	}

	void Prev_Thd()
	{
		if (_root == NULL)
		{
			return;
		}
		BinaryTreeNode_Thd<T>* cur = _root;

		while (cur)
		{
			while (cur && cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			cur = cur->_right;

			/*	while(cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}

			if(cur->_leftTag == LINK)
			    cur = cur->_left;
			else
			    cur = cur->_right;*/
		}

		cout << endl;
	}

	void InOrder_Thd()
	{
		if (_root == NULL)
		{
			return;
		}
		BinaryTreeNode_Thd<T>* cur = _root;
		while (cur)
		{
			while (cur != NULL && cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
		cout << endl;
	}

	void PostOrder_Thd()
	{
		if (_root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode_Thd<T>*> s;
		BinaryTreeNode_Thd<T>* cur = _root;
		while (cur)
		{
			while (cur && cur->_rightTag == LINK)
			{
				s.push(cur);
				cur = cur->_right;
			}
			s.push(cur);
			cur = cur->_left;
		}
		while (!s.empty())
		{
			cout << s.top()->_data << " ";
			s.pop();
		}
		cout << endl;
	}

protected:
	BinaryTreeNode_Thd<T>* _CreateTree(const T* a, size_t size, size_t& index)
	{
		BinaryTreeNode_Thd<T>* root = NULL;
		if (index < size)
		{
			if ('#' != a[index])
			{
				root = new BinaryTreeNode_Thd<T>(a[index]);
				root->_left = _CreateTree(a, size, ++index);
				root->_right = _CreateTree(a, size, ++index);
			}
		}
		return root;
	}

	void _PrevOrder_Thread(BinaryTreeNode_Thd<T>* cur, BinaryTreeNode_Thd<T>*& prev)
	{
		if (cur == NULL)
		{
			return;
		}
		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		if (cur->_leftTag == LINK)
		{
			_PrevOrder_Thread(cur->_left, prev);
		}
		if (cur->_rightTag == LINK)
		{
			_PrevOrder_Thread(cur->_right, prev);
		}
	}

	void _InOrder_Thread(BinaryTreeNode_Thd<T>* cur, BinaryTreeNode_Thd<T>*& prev)
	{
		if (cur == NULL)
		{
			return;
		}
		_InOrder_Thread(cur->_left, prev);
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		_InOrder_Thread(cur->_right, prev);
	}

	void _PostOrder_Thread(BinaryTreeNode_Thd<T>* cur, BinaryTreeNode_Thd<T>*& prev)
	{
		if (cur == NULL)
		{
			return;
		}
		_PostOrder_Thread(cur->_left, prev);
		_PostOrder_Thread(cur->_right, prev);
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
	}

private:
	BinaryTreeNode_Thd<T>* _root;
};

int main()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree_Thd<int> t1(a, 10);
	/*t1.InOrder_Thread();
	t1.InOrder_Thd();
	t1.PrevOrder_Thread();
	t1.Prev_Thd();*/
	t1.PostOrder_Thread();
	t1.PostOrder_Thd();
	return 0;
}