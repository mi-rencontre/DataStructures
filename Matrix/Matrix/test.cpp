#include <iostream>
using namespace std;

#include <vector>

template <class T>
class SymmetricMatrix{
public:
	SymmetricMatrix(T *a, size_t n)
		:_array(new T[n*(n+1)/2])
		,_n(n)
	{
		size_t index = 0;
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (i >= j)
				{
					_array[index++] = a[i*n+j];
				}
				else
				{
					break;
				}
			}
		}
	}

	void display()
	{
		for (size_t i = 0; i < _n; ++i)
		{
			for (size_t j = 0; j < _n; ++j)
			{
				if (i >= j)
				{
					cout << _array[i*(i + 1) / 2 + j] << " ";
				}
				else
				{
					cout << _array[j*(j + 1) / 2 + i] << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	T& AccessNum(size_t i, size_t j)
	{
		assert(i < _n);
		assert(j < _n);

		if (i < j)
		{
			swap(i, j);
		}

		return _array[i*(i + 1) / 2 + j];
	}

	~SymmetricMatrix()
	{
		if (_array)
		{
			delete[] _array;
		}
	}
private:
	T *_array;     
	size_t _n;
};


template <class T>
struct Trituple
{
	int _row;
	int _col;
	T _value;
};

template <class T>
class SparseMatrix{
public:
	SparseMatrix()
		:_colSize(0)
		, _rowSize(0)
	{}

	SparseMatrix(T *a, size_t m, size_t n, const T& invalid)
		:_rowSize(m)
		, _colSize(n)
		, _invalid(invalid)
	{
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (_invalid != a[i*n + j])
				{
					Trituple<T> t1;
					t1._row = i;
					t1._col = j;
					t1._value = a[i*n + j];
					_array.push_back(t1);
				}
			}
		}
	}

	void display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowSize; i++)
		{
			for (size_t j = 0; j < _colSize; j++)
			{
				if ((index<_array.size())&&(i == _array[index]._row) && (j == _array[index]._col))
				{
					cout << _array[index++]._value << " ";
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

    SparseMatrix<T> Transpose()
	{
		SparseMatrix<T> sp;
		sp._rowSize = _colSize;
		sp._colSize = _rowSize;
		sp._invalid = _invalid;
		for (size_t i = 0; i < _colSize; ++i)
		{
			size_t index = 0;
			while (index < _array.size())
			{
				if (_array[index]._col == i)
				{
					Trituple<T> t;
					t._col = _array[index]._row;
					t._row = _array[index]._col;
					t._value = _array[index]._value;
					sp._array.push_back(t);
				}
				index++;
			}
		}
		return sp;
	}

	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> sp;
		sp._rowSize = _colSize;
		sp._colSize = _rowSize;
		sp._invalid = _invalid;
		int *rowCounts = new int[_colSize];
		int *rowStart = new int[_colSize];
		memset(rowCounts, 0, sizeof(int)*_colSize);
		memset(rowStart, 0, sizeof(int)*_colSize);
		size_t index = 0;
		while (index < _array.size())
		{
			rowCounts[_array[index]._col]++;
			++index;
		}

		rowStart[0] = 0;
		for (int i = 1; i < _colSize; ++i)
		{
			rowStart[i] = rowStart[i - 1] + rowCounts[i - 1];
		}
		// 借助rowStart定位转置后压缩存储的位置
		index = 0;
		sp._array.resize(_array.size());
		while (index < _array.size())
		{
			size_t begin = rowStart[_array[index]._col];
			Trituple<T> t;
			t._col = _array[index]._row;
			t._row = _array[index]._col;
			t._value = _array[index]._value;

			sp._array[begin] = t;

			++rowStart[_array[index]._col];
			++index;
		}

		delete[] rowCounts;
		delete[] rowStart;

		return sp;
	}

private:
	vector<Trituple<T>> _array;
	size_t _rowSize;
	size_t _colSize;
	T _invalid;
};

int main()
{
	int a1[5][5] = {
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 },
	};
	//SymmetricMatrix<int> sm((int*)a1, 5);
	//sm.display();
	int a2[6][5] = {
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 2, 0, 4, 0, 6 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
	};
	SparseMatrix<int> sp((int*)a2, 6, 5, 0);
	sp.display();
	SparseMatrix<int> sp1 = sp.Transpose();
	sp1.display();
	SparseMatrix<int> sp2 = sp.FastTranspose();
	sp2.display();
	return 0;
}