// Graph
// Floyd warshall algo dp in graph
// all pairs of shortest path

#include <bits/stdc++.h>
using namespace std;


int main()
{
    int V=4,E;
    // cout << "Enter no. of vertices  and edges : ";
    // cin >> V>>E;
    int n=V;

    int max=1000;

    int mat[n][n]={
        {0,3,max,7},
        {8,0,2,max},
        {5,max,0,1},
        {2,5,max,0}
    };

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         if (i == j)
    //             mat[i][j] = 0;
    //         else
    //             mat[i][j] = INT_MAX;
    //     }
    // }


    // cout<<" vertex vertex weight \n";

    // for(int i=0;i<E;i++)
    // {
    //     int u,v,wt;
    //     cin>>u>>v>>wt;
    //     mat[u][v]=wt;
    //     mat[v][u]=wt;
    // }

    cout<<"floyd warshall algo dp"<<endl<<endl;


    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }

    cout<<'\n'<<'\n'<<'\n';
    return 0;
}