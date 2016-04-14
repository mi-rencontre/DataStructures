#include<iostream>
using namespace std;

#include <assert.h>

enum Type
{
	HEAD,
	VALUE,
	SUB,
};

struct GeneralListNode
{
	Type _type;
	GeneralListNode* _next;

	union{
		char _value;
		GeneralListNode* _sublink;
	};

	GeneralListNode(Type type = VALUE, char value = 0)
		:_type(type)
		, _next(NULL)
	{
		if (_type == VALUE)
		{
			_value = value;
		}
		else if (_type == SUB)
		{
			_sublink = NULL;
		}
	}
};

class GeneralList
{
public:
	GeneralList()
		:_head(NULL)
	{}

	GeneralList(char *s)
		:_head(NULL)
	{
		_head = _CreateGeneralList(s);
	}

	GeneralList(const GeneralList& g)
	{
		_head = _Copy(g._head);
	}

	GeneralList& operator=(const GeneralList& g)
	{
		if (this != &g)
		{
			this->_Destory(_head);
			_head = _Copy(g._head);
		}
		return *this;
	}

	//GeneralList& operator=(GeneralList g)
	//{
	//	swap(_head, g._head);
	//	return *this;
	//}

	~GeneralList()
	{
		_Destory(_head);
	}

	size_t Size()
	{
		return _size(_head);
	}

	size_t Depth()
	{
		return _depth(_head);
	}

	void Print()
	{
		_Print(_head);
		cout << endl;
	}

protected:
	GeneralListNode* _CreateGeneralList(char*& s)
	{
		assert(*s == '(');
		GeneralListNode *head = new GeneralListNode(HEAD);
		++s;
		GeneralListNode *cur = head;
		while (*s)
		{
			if (*s == '(')
			{
				GeneralListNode *subnode = new GeneralListNode(SUB);
				cur->_next = subnode;
				cur = cur->_next;
				subnode->_sublink = _CreateGeneralList(s);
			}
			else if (*s == ')')
			{
				++s;
				break;
			}
			else if (IsValue(*s))
			{
				GeneralListNode* valuenode = new GeneralListNode(VALUE, *s);
				cur->_next = valuenode;
				cur = cur->_next;
				++s;
			}
			else
			{
				++s;
			}
		}
		return head;
	}

	GeneralListNode* _Copy(GeneralListNode *head)
	{
		assert(head);
		GeneralListNode *newhead = new GeneralListNode(HEAD);
		GeneralListNode *cur = head->_next;
		GeneralListNode *newcur = newhead;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				newcur->_next = new GeneralListNode(VALUE, cur->_value);
				newcur = newcur->_next;
			}
			else if (cur->_type = SUB)
			{
				newcur->_next = new GeneralListNode(SUB);
				newcur = newcur->_next;
				newcur->_sublink = _Copy(cur->_sublink);
			}
			cur = cur->_next;
		}
		return newhead;
	}
	
	void _Print(GeneralListNode* head)
	{
		GeneralListNode *cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)
			{
				cout << "(";
			}
			else if (cur->_type == VALUE)
			{
				cout << cur->_value;
				if (cur->_next)
				{
					cout << ",";
				}
			}
			else
			{
				_Print(cur->_sublink);
				if (cur->_next)
				{
					cout << ",";
				}
			}
			cur = cur->_next;
		}
		cout << ")";
	}

	bool IsValue(char c)
	{
		if ((c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		{
			return true;
		}
		return false;
	}

	size_t _size(GeneralListNode *head)
	{
		GeneralListNode *cur = head;
		size_t size = 0;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				size++;
			}
			else if (cur->_type == SUB)
			{
				size += _size(cur->_sublink);
			}
			cur = cur->_next;
		}
		return size;
	}

	size_t _depth(GeneralListNode *head)
	{
		size_t depth = 1;
		GeneralListNode *cur = head;  
		while (cur)
		{
			if (cur->_type == SUB)
			{
				size_t subdepth = _depth(cur->_sublink);
				if (subdepth + 1 > depth)
				{
					depth = subdepth + 1;
				}
			}
			cur = cur->_next;
		}
		return depth;
	}

	void _Destory(GeneralListNode *head)
	{
		GeneralListNode *cur = head;
		while (cur)
		{
			GeneralListNode* del = cur;
			cur = cur->_next;

			if (del->_type == SUB)
			{
				_Destory(del->_sublink);
			}
			delete del;
		}
	}

private:
	GeneralListNode* _head;
};

int main()
{
	GeneralList g1("()");
	GeneralList g2("(a,b)");
	GeneralList g3("(a,b,(c,d))");
	GeneralList g4("(a,b,(c,d),(e,(f),h))");
	GeneralList g5(g4);
	g3 = g4;
	g3.Print();
	cout<<g5.Depth()<<endl;
	cout<<g5.Size()<<endl;
	return 0;
}