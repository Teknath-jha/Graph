#include<bits/stdc++.h>
using namespace std;

struct edge
{
int a;
int b;
int w;
};

#define MAX 100005
edge adj[MAX];
int parent[MAX];

bool cmp(edge x, edge y)
{
    if(x.w  < y.w)
        return true;
    return false;
}

int find(int a)
{
    if(parent[a]==-1)
        return a;
    
    return parent[a]=find(parent[a]);
}


void merge(int a,int b)
{
    parent[a]=b;
}


int main()
{
    int n,m;
    cin>>n>>m;
    memset(parent,-1,sizeof parent);
    
    for(int i=0;i<m;i++)
    {
        cin>>adj[i].a>>adj[i].b>>adj[i].w;
    }

    sort(adj,adj+m,cmp);

    int sum=0;

    for(int i=0;i<m;i++)
    {
        int a= find(adj[i].a);
        int b= find(adj[i].b);

        if(a!=b)
        {
            sum+=adj[i].w;
            merge(a,b);
        }
    }

    cout<<sum<<'\n';

    return 0;
}
