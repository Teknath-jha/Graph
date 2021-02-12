//k-cores
// remove all vertices which have edges less than k remove again
// and again untill all vertices have no. of edges  > k
#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
vector<pair<int, int>> adj[MAX];
int visited[MAX];

void addEdge(int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void k_cores(int n, int k)
{
    // cores array maintain count of no. of edges each vertex have 
    int cores[n];

    for (int i = 0; i < n; i++)
        cores[i] = adj[i].size();

    while (1)
    {
        for (int i = 0; i < n; i++)
        {

            if (cores[i] < k && cores[i] > 0 && visited[i] == 0)
            {
                for (auto x : adj[i])
                {
                    cores[x.first]--;
                }
                cores[i] = 0;
            }
        }
        int flag = 0;
        // check is there any vertex having edges < k
        for (int i = 0; i < n; i++)
            if (cores[i] < k && cores[i] > 0)
                flag = 1;

        //  not found any edges so done
        if (flag == 0)
            break;
    }

    // print graph
    for (int i = 0; i < n; i++)
    {
        if (cores[i] > 0)
        {
            cout << i << " : -> ";
            for (auto x : adj[i])
            {
                if (cores[x.first] >= k)
                    cout << x.first << " -> ";
            }

            cout << '\n';
        }
    }
}

int main()
{
    int n = 9; //no. of vertices

    addEdge(0, 1, 10);
    addEdge(0, 2, 10);
    addEdge(1, 2, 10);
    addEdge(1, 5, 10);
    addEdge(2, 3, 10);
    addEdge(2, 4, 10);
    addEdge(2, 5, 10);
    addEdge(2, 6, 10);
    addEdge(3, 4, 10);
    addEdge(3, 6, 10);
    addEdge(3, 7, 10);
    addEdge(4, 6, 10);
    addEdge(4, 7, 10);
    addEdge(5, 6, 10);
    addEdge(5, 8, 10);
    addEdge(6, 7, 10);
    addEdge(6, 8, 10);

    memset(visited, 0, sizeof(visited));

    int k = 3;

    k_cores(n, k);

    return 0;
}