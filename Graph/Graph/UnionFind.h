#pragma once

class UnionFindSet
{
public:
	UnionFindSet(size_t size)
		:_array(new int[size])
		, _size(size)
	{
		memset(_array, -1, sizeof(int)*_size);
	}

	~UnionFindSet()
	{
		if (_array != NULL)
		{
			delete[] _array;
		}
	}

	void Merge(int root1, int root2)
	{
		while (_array[root2] >= 0)
		{
			root2 = _array[root2];
		}
		_array[root1] += _array[root2];
		_array[root2] = root1;
	}

	int Find(int child)
	{
		while (_array[child] >= 0)
		{
			child = _array[child];
		}
		return child;
	}

	void print()
	{
		for (int i = 0; i < _size; ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

private:
	int*  _array;
	size_t _size;
};

void Test()
{
	UnionFindSet us(10);
	us.Merge(0, 6);
	us.Merge(0, 7);
	us.Merge(0, 8);

	us.Merge(1, 4);
	us.Merge(1, 9);

	us.Merge(2, 3);
	us.Merge(2, 5);

	us.Merge(0, 4);
	us.Find(4);
	us.print();
}