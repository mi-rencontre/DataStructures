#pragma once

#include<assert.h>

template<class V, class W>
class GraphMatrix
{
public:
	GraphMatrix(const V* vArray, int size, bool IsDigraph = false)
		:_vArray(new V[size])
		, _vSize(size)
		, IsDigraph(IsDigraph)
	{
		_Matrix = new W*[_vSize];
		for (int i = 0; i < size; ++i)
		{
			_vArray[i] = vArray[i];
			_Matrix[i] = new W[_vSize];
			memset(_Matrix[i], 0, sizeof(W)*_vSize);
		}
	}

	int GetVertexIndex(const V& vt)
	{
		for (int i = 0; i < _vSize; ++i)
		{
			if (_vArray[i] == vt)
			{
				return i;
			}
		}
		return -1;
	}

	void AddEdge(const V& src, const V& dst, const W& weight)
	{
		int srcIndex = GetVertexIndex(src);
		int dstIndex = GetVertexIndex(dst);

		assert(srcIndex != -1);
		assert(dstIndex != -1);

		if (IsDigraph)
		{
			_Matrix[srcIndex][dstIndex] = weight;
		}
		else
		{
			_Matrix[srcIndex][dstIndex] = weight;
			_Matrix[dstIndex][srcIndex] = weight;
		}
	}

	void Display()
	{
		for (int i = 0; i < _vSize; ++i)
		{
			cout << _vArray[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < _vSize; ++i)
		{
			for (int j = 0; j < _vSize; ++j)
			{
				cout << _Matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	~GraphMatrix()
	{
		if (_vArray != NULL)
		{
			delete[] _vArray;
			_vArray = NULL;
			for (int i = 0; i < _vSize; ++i)
			{
				delete[] _Matrix[i];
				_Matrix[i] = NULL;
			}
			delete[] _Matrix;
			_Matrix = NULL;
		}	
	}

private:
	V* _vArray;           //顶点集
	int _vSize;          //顶点数
	W** _Matrix;         //邻接矩阵
	bool IsDigraph;
};