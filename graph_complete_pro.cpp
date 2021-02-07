
// C++ program to represent undirected and weighted graph
// using STL.
//The program basically prints adjacency list
// representation of graph

/*-----------PROGRAMS-------------*/
/*
1. Creating a graph via a adjancy list 
2.print a grap
3.bfs  iterative
4.dfs  recursive
5.  (5.2)   dfs for counting number of components of graph
6.dfs iterative 
7.  (5.1)      count component auxillary function 
8.Dijkstra's Algo for shortest path 
9.printing all possible  path from src to dest (9.1 and 9.2)
10. Hamiltonian path 
11. Is Bipartite graph or not 
12. Spread of diseases at time t by pepcode


*/

#include <bits/stdc++.h>
using namespace std;
#define MAX 100005

//Adj list    array of vectors of pair
vector<pair<int, int>> adj[MAX];
//visited array
int visited[MAX];

// 1
// To add an edge
void addEdge(int u, int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt));
}

//2
// Print adjacency list representaion ot graph
void printGraph(int V)
{
	int v, w;
	for (int u = 0; u < V; u++)
	{
		cout << "Node " << u << " makes an edge with \n";
		for (auto it = adj[u].begin(); it != adj[u].end(); it++)
		{
			v = it->first;
			w = it->second;
			cout << "\tNode " << v << " with edge weight ="
				 << w << "\n";
		}
		cout << "\n";
	}
}

// 3
//bfs   breadth first search  iterative
void bfs(int src)
{

	cout << src << " -> ";
	queue<int> q;
	//int visited[MAX] {0};
	q.emplace(src);
	visited[src] = 1;

	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		if (visited[temp] == 0)
		{
			cout << temp << " -> ";
			visited[temp] = 1;
		}

		for (auto x : adj[temp])
			if (visited[x.first] == 0)
				q.emplace(x.first);
	}
}

// 4
//recursive
//dfs  depth first search
void r_dfs(int src)
{
	if (visited[src] == 0)
	{
		cout << src << " -> ";
		visited[src] = 1;
	}
	for (auto x : adj[src])
		if (visited[x.first] == 0)
			r_dfs(x.first);
}

//5  (5.1)
//dfs  depth first search auxilarry function  for component counting
void rr_dfs(int src, vector<int> &cmp)
{

	if (visited[src] == 0)
	{
		//	 	cout<<src<<" -> ";
		visited[src] = 1;
		cmp.push_back(src);
	}
	for (auto x : adj[src])
		if (visited[x.first] == 0)
			rr_dfs(x.first, cmp);
}

//6
//iterative
//dfs  depth first search
void i_dfs(int src)
{
	cout << src << " -> ";
	stack<int> stk;

	stk.push(src);
	visited[src] = 1;

	while (!stk.empty())
	{
		int temp = stk.top();
		stk.pop();

		if (visited[temp] == 0)
		{
			visited[temp] = 1;
			cout << temp << " -> ";
		}

		for (auto x : adj[temp])
			if (visited[x.first] == 0)
				stk.push(x.first);
	}
}

//7  (5.2)
// Aux to count components
void count_components(int vertices)
{
	int component = 0;
	memset(visited, 0, sizeof(visited));
	vector<vector<int>> allcmp;
	for (int i = 0; i < vertices; i++)
	{
		vector<int> cmp;
		if (visited[i] == 0)
		{
			rr_dfs(i, cmp);
			allcmp.push_back(cmp);
			component++;
		}
	}
	cout << endl;
	for (int i = 0; i < allcmp.size(); i++)
	{
		for (int j = 0; j < allcmp[i].size(); j++)
		{
			cout << allcmp[i][j] << " -> ";
		}
		cout << endl;
	}
	cout << "Total no. of components are : " << component << endl;
	// return component;
}

//8
//dijkstra's  algorithm to find shortest path from sourcr to destinstion
void dijkstra(int src, int vertices)
{
	//min priority queue
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> dist(vertices, INT_MAX);

	dist[src] = 0;

	pq.push(make_pair(0, src));

	while (!pq.empty())
	{
		int temp = pq.top().second;
		pq.pop();

		for (auto x : adj[temp])
		{
			int v = x.first;
			int w = x.second;

			if (dist[v] > dist[temp] + w)
			{
				dist[v] = dist[temp] + w;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	cout << "Dijkatra's algorithm for shortest path : \n";
	for (int i = 0; i < vertices; i++)
	{
		cout << src << " to " << i << " min distance is " << dist[i] << '\n';
	}
}

//9
//9.2
//Printing all possible path from src to destination
void printAllPath(int src, int dest, int path[], int &trace)
{
	path[trace] = src;
	trace++;
	visited[src] = 1;

	if (src == dest)
	{
		for (int i = 0; i < trace; i++)
			cout << path[i] << " -> ";
		cout << endl;
	}
	else
	{
		for (auto x : adj[src])
		{
			if (visited[x.first] == 0)
			{
				printAllPath(x.first, dest, path, trace);
			}
		}
	}

	visited[src] = 0;
	trace--;
}

//9.1
//printing all possible path from src to destination
void printAllPathAux(int src, int dest)
{
	memset(visited, 0, sizeof(visited));
	int path[MAX];
	int trace = 0;

	printAllPath(src, dest, path, trace);
}

//10
// Hamiltonian path and cycle

//10.2
// this function just used to distinguish path and cyle and print it
void printPath(vector<int> &path)
{
	// checking for path and cycle
	bool flag = false;
	for (auto x : adj[path[0]])
	{
		if (x.first == path[path.size() - 1])
		{
			flag = true;
			break;
		}
	}
	if (flag)
		cout << "Hamiltonian Cycle : "
			 << " ";
	else
		cout << "Hamiltonian Path  : "
			 << " ";
	for (auto x : path)
		cout << x << " ";

	cout << endl;
}

//10.1
// filling hamiltonian path  dfs
void hamiltonianPath(int src, vector<int> &path, int n)
{
	if (path.size() == n)
	{
		printPath(path);
		return;
	}

	for (auto x : adj[src])
	{
		if (visited[x.first] == 0)
		{
			visited[x.first] = 1;
			path.push_back(x.first);

			hamiltonianPath(x.first, path, n);
			// backtrack
			visited[x.first] = 0;
			path.pop_back();
		}
	}
}

// 11
// Is Bipartite graph or not
bool isBipartitie(int src, int n)
{
	vector<int> level(n);

	visited[src] = 1;
	level[src] = 0;

	queue<int> q;
	q.push(src);

	while (!q.empty())
	{
		int t = q.front();
		q.pop();

		for (auto x : adj[t])
		{
			if (visited[x.first] == 0)
			{
				visited[x.first] = 1;
				// storing level to detect even or odd cycle or to predict in else part
				//  whether parent and child belongs to same level
				level[x.first] = level[t] + 1;
				q.push(x.first);
			}
			else if (level[t] == level[x.first])
			{
				return false;
			}
		}
	}
	return true;
}

// 12
// spread of diseases at time t by pepcode
int countPatients(int src, int n, int time)
{
	if(time==0) return 0;
	int count = 0;

	visited[src] = 1;
	count++;

	int level[n];
	memset(level,0,sizeof(level));
	level[src] = 1;

	queue<int> q;
	q.push(src);
	while (!q.empty())
	{
		int t = q.front();
		q.pop();

		for (auto x : adj[t])
		{
			if (level[t] == time)
			{
				return count;
			}
			// cout<<count<<endl;

			if (visited[x.first] == 0)
			{
				level[x.first] = level[t] + 1;
				visited[x.first] = 1;
				count++;
				q.push(x.first);
			}
		}
	}
}

// Driver code
int main()
{
	int vertices = 6;
	int edges = 8;
	int n = vertices + 1;

	addEdge(0, 1, 10);
	addEdge(1, 2, 30);
	addEdge(2, 3, 10);
	addEdge(0, 3, 20);
	// addEdge(2, 5, 10);
	addEdge(3, 4, 40);
	addEdge(4, 5, 50);
	addEdge(4, 6, 60);
	addEdge(5, 6, 70);

	/*   printGraph( 5); 
    
    cout<<"\nBreadth first traversal : \n ";
    memset(visited,0,sizeof(visited));
    bfs(0);
	cout<<endl;
    
    cout<<"\nDepth first traversal recursive: \n ";
    memset(visited,0,sizeof(visited));
    r_dfs(0);
	cout<<endl;
    
    cout<<"\nDepth first traversal iterative: \n ";
    memset(visited,0,sizeof(visited));
    i_dfs(0);
	cout<<endl;

	cout << "\ncomponents : ";
	count_components(vertices);
	cout << endl;

	dijkstra(0,vertices);

	printAllPathAux(0,4);

	// Print all Hamiltonian path
	vector<int> path;
	memset(visited, 0, sizeof(visited));
	cout << "Hamiltonian paths are " << endl;
	hamiltonianPath(0, path, n);
	cout<<'\n'<<'\n';



	// 11 Tell wheather graph is bipartite or not 
	// drawn a special bipartite graph

	n=4;

	addEdge(0,1,10);
	addEdge(0,3,10);
	addEdge(1,2,10);
	addEdge(2,3,10);

	memset(visited,0,sizeof(visited));
	bool check = isBipartitie(0,n);
	if(check)
	 	cout<<"Graph is bipartite \n";
	else 
		cout<<"Graph is not bipartite \n";

*/

cout<<"No. of effected persons are : "<<countPatients(6,n,3);

	cout << '\n'
		 << '\n'
		 << '\n';
	return 0;
}
