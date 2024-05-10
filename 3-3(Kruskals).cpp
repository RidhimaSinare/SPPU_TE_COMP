#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
using namespace std;

//3.3 kruskals
void makeSet(vector<int> &parent, vector<int> &rank, int n)
{
    for(int i=0;i<n;i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}
bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2]<b[2];
}

int findParent(vector<int> &parent, int node)
{
    if(node<0 || node>=parent.size()) return -1;    //remember >=

    if(parent[node] != node)
    {
        parent[node] = findParent(parent, parent[node]);
    }

    return parent[node];
}

void makeUnion(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if(rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if(rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

int kruskals(vector<vector<int>> &edges, int n)
{
    sort(edges.begin(), edges.end(), cmp);

    vector<int>parent(n);
    vector<int>rank(n);

    makeSet(parent, rank, n);
    int res = 0;

    for(int i=0;i<edges.size();i++)
    {
        int u = findParent(parent, edges[i][0]);
        int v = findParent(parent, edges[i][1]);
        int w = edges[i][2];

        if(u!=v)
        {
            res += w;
            makeUnion(u,v, parent, rank);
        }
    }

    return res;
    
}

int main()
{
    int n;
    cout<<endl<<"Enter number of vertices in graph: ";cin>>n;
    int ed;
    cout<<endl<<"Enter number of edges in graph: ";cin>>ed;

    vector<vector<int>>edges;

    for(int i=0;i<ed;i++)
    {
        int u, v, w;
        cout<<endl<<"Enter nodes and weight: ";
        cin>>u>>v>>w;
        edges.push_back({u, v, w});
    }
    for(int i=0;i<ed;i++)
    {
        cout<<endl<<edges[i][0]<<"->"<<edges[i][1]<<" = "<<edges[i][2];
    }

    int ans = kruskals(edges, n);
    cout<<endl<<"Result: "<<ans;

    return 0;

}
