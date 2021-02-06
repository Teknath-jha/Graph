#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
vector<int> v[MAX];
int vis[MAX];


void bfs(int node)
{
    vis[node]=1;
    cout<<node<<" ";
    queue<int> q;
    q.push(node);
    while(!q.empty())
    {
        int var=q.front();
        q.pop();
        if(vis[var]==0)
        {
            vis[var]=1;
            cout<<var<<" ";
        }
        for(auto i:v[var])
        {
            if(vis[i]==0)
                q.push(i);
        }
    }
}

///Depth First Search

void dfs(int node )
{

    if(vis[node]==0)
    {
        cout<<node<<" ";
        vis[node]=1;

        for(auto i:v[node])
            dfs(i);
    }
}

void dfs_stk(int node )
{
    vis[node]=1;
    stack<int> st;
    st.push(node);
    cout<<node<<" " ;
    while(!st.empty())
    {
        int var=st.top();
        st.pop();
        if(vis[var]==0)
        {
            vis[var]=1;
            cout<<var<<" ";
        }
        for(auto i: v[var])
            if(vis[i]==0)
                st.push(i);
    }
}


int main()
{
    int n,e;
    cin>>n>>e;
    for(int i=0; i<e; i++)
    {
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int component=0;
    cout<<"BFS queue : ";
    for(int i=1; i<=n; i++)
    {
        if(vis[i]==0)
        {
            component++;
            bfs(i);
        }
    }
    cout<<endl<<" No. of Components are : "<<component<<endl;
    cout<<endl<<endl;
    memset(vis,0,sizeof(vis));
    component=0;
    cout<<"DFS Recursion : ";
    for(int i=1; i<=n; i++)
    {
        if(vis[i]==0)
        {
            component++;
            dfs(i);
        }
    }
    cout<<endl<<" No. of Components are : "<<component<<endl;
    cout<<endl<<endl;
    memset(vis,0,sizeof(vis));
    component=0;
    cout<<"DFS Stack : ";
    for(int i=1; i<=n; i++)
    {
        if(vis[i]==0)
        {
            component++;
            dfs_stk(i);
        }
    }

    cout<<endl<<" No. of Components are : "<<component<<endl;

    memset(v,0,sizeof(v));
    memset(vis,0,sizeof(vis));
    return 0;
}
