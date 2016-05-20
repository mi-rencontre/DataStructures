#pragma once

#include<queue>
#include"Heap.h"
#include"UnionFind.h"

template<class V, class W>
struct LinkEdge
{
	W _w;
	size_t _srcIndex;
	size_t _dstIndex;
	LinkEdge<V, W>* _next;

	LinkEdge(size_t srcIndex, size_t dstIndex, const W& w)
		: _w(w)
		, _srcIndex(srcIndex)
		, _dstIndex(dstIndex)
		, _next(NULL)
	{}
};

template<class V, class W>
struct LinkVertex
{
	V _vertex;
	LinkEdge<V, W>* _head;

	LinkVertex(const V& vertex = V())
		:_vertex(vertex)
		, _head(NULL)
	{}
};

template<class V, class W>
struct CompareLinkEdge
{
	bool operator()(LinkEdge<V, W>* l, LinkEdge<V, W>* r)
	{
		return l->_w < r->_w;
	}
};

template<class V, class W>
class GraphLink
{
public:

	GraphLink(bool IsDigraph = false)
		:_vSize(0)
		, _IsDigraph(IsDigraph)
		,_LinkTable(0)
	{}

	GraphLink(const V* vArray, int size, bool IsDigraph = false)
		:_vSize(size)
		, _IsDigraph(IsDigraph)
	{
		_LinkTable = new LinkVertex<V, W>[size];
		for (int i = 0; i < size; i++)
		{
			_LinkTable[i]._vertex = vArray[i];
		}
	}

public:
	void AddEdge(const V& src, const V& dst, const W& weight)
	{
		int srcIndex = GetVertexIndex(src);
		int dstIndex = GetVertexIndex(dst);

		assert(srcIndex != -1);
		assert(dstIndex != -1);

		if (_IsDigraph)
		{
			_AddEdge(srcIndex, dstIndex, weight);	
		}
		else
		{
			_AddEdge(srcIndex, dstIndex, weight);
			_AddEdge(dstIndex, srcIndex, weight);
		}
	}

	void DFS(int src)
	{
		cout << "DFS:";

		bool* Visited = new bool[_vSize];
		memset(Visited, false, sizeof(bool)*_vSize);

		_DFS(src, Visited);

		delete[] Visited;

		cout << endl;
	}

	void BFS(int src)
	{
		cout << "BFS:";

		bool* Visited = new bool[_vSize];
		memset(Visited, false, sizeof(bool)*_vSize);

		_BFS(src, Visited);

		delete[] Visited;

		cout << endl;
	}

	bool Kruskal(GraphLink& minTree)
	{
		//初始化最小生成树
		minTree._LinkTable = new LinkVertex<V, W>[_vSize];
		minTree._vSize = _vSize;
		for (int i = 0; i < _vSize; i++)
		{
			minTree._LinkTable[i]._vertex = _LinkTable[i]._vertex;
		}
		//将所有边的权放入最小堆
		Heap<LinkEdge<V, W>*, CompareLinkEdge<V, W>> minHeap;
		for (int i = 0; i < _vSize; ++i)
		{
			LinkEdge<V, W>* begin = _LinkTable[i]._head;
			while (begin)
			{
				if (begin->_srcIndex < begin->_dstIndex)
				{
					minHeap.Push(begin);
				}
				begin = begin->_next;
			}
		}
		//使用并查集与最小堆生成最小生成树
		UnionFindSet us(_vSize);
		int count = 1;
		while (count < _vSize)
		{
			if (minHeap.Empty())
			{
				return false;
			}
			LinkEdge<V, W>* ret = minHeap.Top();
			minHeap.Pop();
			int src = us.Find(ret->_srcIndex);
			int dst = us.Find(ret->_dstIndex);
			if (src != dst)
			{
				us.Merge(src, dst);

				minTree._AddEdge(ret->_srcIndex, ret->_dstIndex, ret->_w);
				minTree._AddEdge(ret->_dstIndex, ret->_srcIndex, ret->_w);
				count++;
			}
		}
		return true;
	}

	bool Prim(GraphLink& minTree)
	{
		minTree._LinkTable = new LinkVertex<V, W>[_vSize];
		minTree._vSize = _vSize;
		for (int i = 0; i < _vSize; i++)
		{
			minTree._LinkTable[i]._vertex = _LinkTable[i]._vertex;
		}
		bool *Visited = new bool[_vSize]();
		int src = 0;
		Visited[src] = true;
		Heap<LinkEdge<V, W>*, CompareLinkEdge<V, W>> minHeap;
		int count = 1;
		while (count < _vSize)
		{
			LinkEdge<V, W>* ret = _GetFirstEdge(src);
			while (ret)
			{
				if (Visited[ret->_dstIndex] == false)
				{
					minHeap.Push(ret);
				}
				ret = _GetNextEdge(src, ret->_dstIndex);
			}

			if (minHeap.Empty())
			{
				return false;
			}

			while (!minHeap.Empty())
			{
				ret = minHeap.Top();
				minHeap.Pop();
				if (Visited[ret->_dstIndex] == false)
				{
					minTree._AddEdge(ret->_srcIndex, ret->_dstIndex, ret->_w);
					minTree._AddEdge(ret->_dstIndex, ret->_srcIndex, ret->_w);
					Visited[ret->_dstIndex] = true;
					src = ret->_dstIndex;
					count++;
					break;
				}
			}
		}
		return true;
	}

	void Display()
	{
		for (int i = 0; i < _vSize; i++)
		{
			cout << _LinkTable[i]._vertex << "[" << i << "]->";
			LinkEdge<V, W>* cur = _LinkTable[i]._head;
			while (cur != NULL)
			{
				cout << cur->_w << "[" << cur->_dstIndex << "]->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
		cout << endl;
	}

protected:
	int GetVertexIndex(const V& vertex)
	{
		for (int i = 0; i < _vSize; i++)
		{
			if (_LinkTable[i]._vertex == vertex)
			{
				return i;
			}
		}
		return -1;
	}

	void _AddEdge(const V& srcIndex, const V& dstIndex, const W& weight)
	{
		LinkEdge<V, W>* head = _LinkTable[srcIndex]._head;
		LinkEdge<V, W>* tmp = new LinkEdge<V, W>(srcIndex, dstIndex, weight);

		tmp->_next = head;
		_LinkTable[srcIndex]._head = tmp;
	}

	LinkEdge<V, W>* _GetFirstEdge(int src)
	{
		return _LinkTable[src]._head;
	}

	LinkEdge<V, W>* _GetNextEdge(int src, int next)
	{
		LinkEdge<V, W>* cur = _LinkTable[src]._head;
		while (cur)
		{
			if (cur->_dstIndex == next)
			{
				return cur->_next;
			}
			cur = cur->_next;
		}

		return NULL;
	}

	void _DFS(int src, bool* Visited)
	{
		cout << _LinkTable[src]._vertex << "->";
		Visited[src] = true;

		LinkEdge<V, W>* cur = _GetFirstEdge(src);
		while (cur)
		{
			if (Visited[cur->_dstIndex] == false)
			{
				_DFS(cur->_dstIndex, Visited);
			}

			cur = _GetNextEdge(src, cur->_dstIndex);
		}
	}

	void _BFS(int src, bool* Visited)
	{
		cout << _LinkTable[src]._vertex << "->";
		Visited[src] = true;

		queue<int> q;
		q.push(src);
		while (!q.empty())
		{
			src = q.front();
			q.pop();

			LinkEdge<V, W>* cur = _GetFirstEdge(src);
			while (cur)
			{
				if (Visited[cur->_dstIndex] == false)
				{
					cout << _LinkTable[cur->_dstIndex]._vertex << "->";
					Visited[cur->_dstIndex] = true;
					q.push(cur->_dstIndex);
				}
				cur = _GetNextEdge(src ,cur->_dstIndex);
			}
		}
	}

private:
	LinkVertex<V, W>* _LinkTable;
	int _vSize;
	bool _IsDigraph;
};