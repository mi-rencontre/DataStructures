#include <iostream>
using namespace std;

#include <vector>
#include<assert.h>

template<class T>
struct Less
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};



template<class T, class compare = Less<T>>
class Heap{
public:
	Heap()
	{}

	Heap(const int* a, size_t size)
	{
		for (int i = 0; i < size; i++)
		{
			_array.push_back(a[i]);
		}
		int parent = (_array.size() - 2)/2;
		for (; parent >= 0; parent--)
		{
			_AdjustDown(parent);
		}
	}

	int Size()
	{
		return _array.size();
	}

	bool IsEmpty()
	{
		return _array.size() == 0;
	}

	T& Top()
	{
		assert(_array.size());
		return _array[0];
	}

	void Pop()
	{
		if (IsEmpty())
		{
			return;
		}
		swap(_array[0],_array[_array.size() - 1]);
		_array.pop_back();
		_AdjustDown(0);
	}

	void Push(const T& x)
	{
		_array.push_back(x);
		if (_array.size() > 1)
		{
			_AdjustUp(_array.size() - 1);
		}
	}

	void Print()
	{
		for (size_t i = 0; i < _array.size(); ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

protected:

	void _AdjustUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (compare()(_array[parent], _array[child]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void _AdjustDown(int parent)
	{
		int child = parent * 2 + 1;
		compare com;
		while (child < _array.size())
		{
			if ((child+1<_array.size()) && com(_array[child], _array[child+1]))
			{
				child++;
			}
			if (com(_array[parent], _array[child]))
			{
				swap(_array[parent], _array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _array;
};

int main()
{
	int a[10] = {10,16,18,12,11,13,15,17,14,19};
	Heap<int> hp(a,10);
	hp.Print();
	hp.Push(5);
	hp.Top();
	hp.Pop();
	hp.Size();
	return 0;
}