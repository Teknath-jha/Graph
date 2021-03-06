
// C++ program to represent undirected and weighted graph
// using STL.
//The program basically prints adjacency list
// representation of graph

/*-----------PROGRAMS-------------*/
/*
1.  Creating a graph via a adjancy list 
2.  print a grap
3.  bfs  iterative
4.  dfs  recursive
5.  (5.2)   dfs for counting number of components of graph
6.  dfs iterative 
7.  (5.1)      count component auxillary function 
8.  Dijkstra's Algo for shortest path 
9.  Printing all possible  path from src to dest (9.1 and 9.2)
10. Hamiltonian path 
11. Is Bipartite graph or not 
12. Spread of diseases at time t by pepcode
13. Prim's algo to give minimum no. of wires or cables to setup a lan  so that each pc would connect to other 
14. Topological sort and Order of work (only applicable in DAC Directed Acyclic Graph)
15. Iterative dfs
16. Graph coloring (BFS) no adjacent vertices have same color

*/

#include <bits/stdc++.h>
using namespace std;
#define MAX 100005


typedef pair<int, int> iPair;
//Adj list    array of vectors of pair
vector<pair<int, int>> adj[MAX];
//visited array
int visited[MAX];

// 1
// To add an edge
void addEdge(int u, int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt));    //comment it out for directed graph i did in topological sort 
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
	return count;
}


// 13
// prims algo (minimum wire to setup a lan pepcode)
// MST minimum spaning tree
void primsAlgo(int src, int n)
{
// minimum prioprity queue 
	priority_queue<iPair ,vector<iPair>, greater<iPair> > pq;

	vector<int> key(n,INT_MAX);

	vector<int> parent(n,-1);

	pq.push(make_pair(0,src));
	key[src]=0;

	while(!pq.empty())
	{	
		int t = pq.top().second;
		pq.pop();

		visited[t]=1;

		for(auto x:adj[t])
		{
			int v= x.first;
			int wt=x.second;

			if(visited[v]==0 && key[v] > wt)
			{	
				key[v] = wt;
				pq.push(make_pair(key[v],v));
				parent[v]=t;
			}
		}
	}

	for( int i=1; i<n ; i++)
	{
		cout<<parent[i]<<" -> "<<key[i]<<" -> "<<i<<endl;
	}
}


// 14
// Topological sort 
// pura dfs hai sirf stack me add kar rahe hai 
void topologicalSort(int src , stack<int> &stk)
{
	visited[src]=1;
	for(auto x:adj[src])
	{
		if(visited[x.first]==0)
		{
			topologicalSort(x.first , stk);
		}
	}
	stk.push(src);
}


// 15 
// Iterative dfs 
// key point->  instead of sibling in bfs here we explore its child first 
void iterativeDfs(int src)
{
	stack<int> stk;
	stk.push(src);
	visited[src]=1;
	cout<<src<<" -> ";

	while(!stk.empty())
	{
		int t = stk.top();
		stk.pop();

		if(visited[t]==0)
		{
			visited[t]=1;
			cout<<t<<" -> ";
		}
		for(auto x:adj[t])
		{
			if(visited[x.first]==0)
			{
				stk.push(x.first);
			}
		}
	}
}


// 16
// Graph coloring (BFS) no adjacent vertices have same color
void graphColoring(int src , int n)
{
	int color[n];
	memset(color,-1,sizeof(color));

	queue<int> q;
	q.push(src);
	color[src]=0;  //source colored with 0


	while(!q.empty())
	{
		int t=q.front();
		q.pop();

		if(visited[t]==0)
		{
			visited[t]=1;
		}

		for(auto x:adj[t])
		{
			if(visited[x.first]==0 && color[x.first]==-1)
			{
				color[x.first]=1-color[t];
				q.push(x.first);
			}
			if(visited[x.first]==1 && color[x.first]== color[t])
			{
				color[x.first]=1+color[t];
				q.push(x.first);
			}
		}
	}
	cout<<"Different colors are as follow in graph coloring : \n";
	for(int i=0;i<n;i++)
	{
		cout<<"At "<<i<<"th vertex ,  color "<<color[i]<<'\n';
	}
}



// Driver code
int main()
{
	int vertices = 6;
	int edges = 8;
	int n = vertices + 1;

	addEdge(0, 1, 10);
	addEdge(1, 2, 10);
	addEdge(2, 3, 10);
	addEdge(0, 3, 40);
	// addEdge(2, 5, 10);
	addEdge(4, 3, 20);
	addEdge(4, 5, 10);
	addEdge(4, 6, 60);
	addEdge(5, 6, 10);

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



	// spread of disease
	cout<<"No. of effected persons are : "<<countPatients(6,n,3);


	cout<<"Prim's algo :\n";
	cout<<"from -> wt -> to \n";
	memset(visited,0,sizeof(visited));
	primsAlgo(0,n);



	cout<<"Topological sort : \n";
	memset(visited,0,sizeof(visited));
	stack<int> stk;
	for(int i=0;i<n;i++)
	{
		if(visited[i]==0)
		{
			topologicalSort(i,stk);
		}
	}
	vector<int> orderOfWork;
	while(!stk.empty())
	{
		int t=stk.top();
		stk.pop();
		cout<<t<<" -> ";
		orderOfWork.push_back(t);
	}

	// reverse of topological sort is order of work
	cout<<"\n\nOrder of work  : \n";
	vector<int>::iterator i;
	for(i =orderOfWork.end()-1;i > orderOfWork.begin()-1;i--)
	{
		cout<<(*i)<<" -> ";
	}


	// Iterative dfs
	cout<<"Iterative dfs : \n";
	memset(visited,0,sizeof(visited)); 
	iterativeDfs(0);

*/

// Graph coloring 
memset(visited,0,sizeof(visited));
graphColoring(0,n);


	cout << '\n'
		 << '\n'
		 << '\n';
	return 0;
}
