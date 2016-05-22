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
			LinkEdge<V, W>* ret = _LinkTable[src]._head;
			while (ret)
			{
				if (Visited[ret->_dstIndex] == false)
				{
					minHeap.Push(ret);
				}
//				ret = _GetNextEdge(src, ret->_dstIndex);
				ret = ret->_next;
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

	void Dijkstra(int src, const W& maxValue)
	{
		W* dist = new W[_vSize];
		int* path = new int[_vSize];
		bool* vSet = new bool[_vSize];

//		_Dijkstra(src, dist, path, vSet, _vSize, maxValue);
		_Dijkstra_OP(src, dist, path, vSet, _vSize, maxValue);

		_PrintPath(src, dist, path, _vSize);

		delete[] dist;
		delete[] path;
		delete[] vSet;
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

	//LinkEdge<V, W>* _GetFirstEdge(int src)
	//{
	//	return _LinkTable[src]._head;
	//}

	//LinkEdge<V, W>* _GetNextEdge(int src, int next)
	//{
	//	LinkEdge<V, W>* cur = _LinkTable[src]._head;
	//	while (cur)
	//	{
	//		if (cur->_dstIndex == next)
	//		{
	//			return cur->_next;
	//		}
	//		cur = cur->_next;
	//	}
	//	return NULL;
	//}

	void _DFS(int src, bool* Visited)
	{
		cout << _LinkTable[src]._vertex << "->";
		Visited[src] = true;

		LinkEdge<V, W>* cur = _LinkTable[src]._head;
		while (cur)
		{
			if (Visited[cur->_dstIndex] == false)
			{
				_DFS(cur->_dstIndex, Visited);
			}

//			cur = _GetNextEdge(src, cur->_dstIndex);
			cur = cur->_next;
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

			LinkEdge<V, W>* cur = _LinkTable[src]._head;
			while (cur)
			{
				if (Visited[cur->_dstIndex] == false)
				{
					cout << _LinkTable[cur->_dstIndex]._vertex << "->";
					Visited[cur->_dstIndex] = true;
					q.push(cur->_dstIndex);
				}
//				cur = _GetNextEdge(src ,cur->_dstIndex);
				cur = cur->_next;
			}
		}
	}

	W _GetWeight(int src, int dst, const W& maxValue)
	{
		if (src == dst)
		{
			return maxValue;
		}
		LinkEdge<V, W>* edge = _LinkTable[src]._head;
		while (edge)
		{
			if (edge->_dstIndex == dst)
			{
				return edge->_w;
			}
			edge = edge->_next;
		}
		return maxValue;
	}

	void _Dijkstra_OP(int src, W* dist, int* path, bool* vSet,int size, const W& maxValue)
	{
		for (int i = 0; i < size; i++)
		{
			dist[i] = _GetWeight(src, i, maxValue);
			path[i] = src;
			vSet[i] = false;
		}

		struct Compare
		{
			bool operator()(const pair<W, int>& l, const pair<W, int>& r)
			{
				return l.first < r.first;
			}
		};

		Heap<pair<W, int>, Compare> minHeap;
		for (int i = 0; i < size; ++i)
		{
			if (dist[i] < maxValue)
			{
				minHeap.Push(make_pair(dist[i], i));
			}
		}

		vSet[src] = true;

		int count = size;
		while (count--)
		{
			if (minHeap.Empty())
			{
				continue;
			}

			int minIndex = minHeap.Top().second;
			minHeap.Pop();

			vSet[minIndex] = true;
			for (int k = 0; k < size; k++)
			{
				W w = _GetWeight(minIndex, k, maxValue);
				if (vSet[k] == false && dist[minIndex] + w < dist[k])
				{
					dist[k] = dist[minIndex] + w;
					path[k] = minIndex;

					minHeap.Push(make_pair(dist[k], k));
				}
			}
		}
	}

	void _Dijkstra(int src, W* dist, int* path, bool* vSet, int size, const W& maxtValue)
	{
		//dist初始化src到其他顶点的距离
		//path初始化src到其他顶点的路径
		//初始化顶点集合
		for (int i = 0; i < size; i++)
		{
			dist[i] = _GetWeight(src, i, maxtValue);
			path[i] = src;
			vSet[i] = false;
		}

		vSet[src] = true;
		int count = size;
		while (count--)
		{
			//选出与src顶点连接中最小的边
			W min = maxtValue;
			int minIndex = src;
			for (int j = 0; j < size; j++)
			{
				if (vSet[j] == false && dist[j] < min)
				{
					minIndex = j;
					min = dist[j];
				}
			}

			vSet[minIndex] = true;
			for (int k = 0; k < size; k++)
			{
				if (k == src)
				{
					continue;
				}
				W w = _GetWeight(minIndex, k, maxtValue);
				if (vSet[k] == false && dist[minIndex] + w < dist[k])
				{
					dist[k] = dist[minIndex] + w;
					path[k] = minIndex;
				}
			}
		}
	}

	void _PrintPath(int src, W* dist, int* path, int size)
	{
		int* vPath = new int[size];
		for (int i = 0; i < size; i++)
		{
			if (i != src)
			{
				int index = i;
				int count = 0;
				while (index != src)
				{
					vPath[count++] = index;
					index = path[index];
				}
				vPath[count++] = src;
//				cout << src << "," << i << "的路径为:";
				cout << _LinkTable[src]._vertex << "," << _LinkTable[i]._vertex << "的路径为:";
				while (count)
				{
					cout << _LinkTable[vPath[--count]]._vertex << "->";
				//	cout << vPath[--count] << "->";
				}
				cout << "路径长度为:" << dist[i] << endl;
			}
		}
	}

private:
	LinkVertex<V, W>* _LinkTable;
	int _vSize;
	bool _IsDigraph;
};