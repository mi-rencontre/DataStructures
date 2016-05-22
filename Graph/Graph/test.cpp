#include<iostream>
using namespace std;

#include"GraphMatrix.h"
#include"GraphLink.h"

//无向图
void TestGraphMatrix1()
{
	GraphMatrix<char, int> gm("ABCDE", 5);
	gm.AddEdge('A', 'D', 10);
	gm.AddEdge('A', 'E', 20);
	gm.AddEdge('B', 'C', 10);
	gm.AddEdge('B', 'D', 20);
	gm.AddEdge('B', 'E', 30);
	gm.AddEdge('C', 'E', 40);
	gm.Display();
}

//有向图
void TestGraphMatrix2()
{
	GraphMatrix<char, int> gm("ABCDE", 5, true);
	gm.AddEdge('A', 'D', 10);
	gm.AddEdge('E', 'A', 20);
	gm.AddEdge('B', 'C', 10);
	gm.AddEdge('D', 'B', 20);
	gm.AddEdge('E', 'B', 30);
	gm.AddEdge('C', 'E', 40);
	gm.Display();
}

//无向图
void TestGraphLink1()
{
	GraphLink<char, int> gl("ABCDE", 5);
	gl.AddEdge('A', 'D', 10);
	gl.AddEdge('A', 'E', 20);
	gl.AddEdge('B', 'C', 10);
	gl.AddEdge('B', 'D', 20);
	gl.AddEdge('B', 'E', 30);
	gl.AddEdge('C', 'E', 40);
	gl.Display();
	gl.DFS(0);
	gl.BFS(0);
	GraphLink<char, int> minTree1(false);
	cout << gl.Kruskal(minTree1) << endl;
	minTree1.Display();

	GraphLink<char, int> minTree2(false);
	cout << gl.Prim(minTree2) << endl;
	minTree2.Display();
}

//有向图
void TestGraphLink2()
{
	GraphLink<char, int> gl("ABCDE", 5, true);
	gl.AddEdge('A', 'D', 10);
	gl.AddEdge('E', 'A', 20);
	gl.AddEdge('B', 'C', 10);
	gl.AddEdge('D', 'B', 20);
	gl.AddEdge('E', 'B', 30);
	gl.AddEdge('C', 'E', 40);
	gl.Display();
	gl.DFS(0);
	gl.BFS(0);

	gl.Dijkstra(0, 10000);
}

int main()
{
//	TestGraphMatrix1();
//  TestGraphMatrix2();
//	TestGraphLink1();
	TestGraphLink2();
	return 0;
}