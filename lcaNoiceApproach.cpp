#include<bits/stdc++.h>
using namespace std;
#define MAX 1000
vector<int> adj[MAX];
int level[MAX];
int vis[MAX];

int lca(int a,int b)
{
    if(level[a]<level[b])
    swap(a,b);

    int d=level[a]-level[b];

    while(d--)
    {
        //incomplete implementation
        // a=parent[a];
    }


}

void bfs(int src)
{
    queue<int> q;
    q.push(src);
    level[src]=1;
    vis[src]=1;

    while(!q.empty())
    {
        int t=q.front();
        q.pop();

        for(int nb:adj[t])
        {
            if(vis[nb]==0)
            {
                vis[nb]=1;
                level[nb]=level[t]+1;
                q.push(nb);
            }
        }
    }

}

int  main()
{
    int n,m;
    cin>>n>>m;
    
    for(int i=1;i<=n;i++)
        adj[i].clear(),vis[i]=0,level[i]=1;

    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(b);
    }

    cout<<"\nEnter a and b for LCA : ";
    int a,b;
    cin>>a>>b;

    bfs(1);

    cout<<lca(a,b)<<endl;

    return 0;
}