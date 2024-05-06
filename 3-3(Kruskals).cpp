#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;

void makeSet(vector<int> &parent, vector<int> &rank, int n)
{
    for(int i =0; i<n ; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(vector<int> &parent, int node)
{
    if (node < 0 || node >= parent.size()) {
        return -1;
    }
    
    if(parent[node] != node)
    {
        parent[node] = findParent(parent, parent[node]); 
    }

    return parent[node]; // path compression
}


void unionSet(int u , int v, vector<int> & parent, vector<int> & rank)
{
    int uroot = findParent(parent, u);
    int vroot = findParent(parent, v);

        if(rank[uroot] < rank[vroot])
        {
            parent[uroot] = vroot;
        }
        else if(rank[vroot] < rank[uroot])
        {
            parent[vroot] = uroot;
        }
        else
        {
            parent[vroot] = uroot;
            rank[uroot]++;
        }
    
}

bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2];
}

int kruskals(vector<vector<int>> edges, int n)
{
    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(n);
    vector<int> rank(n);

    makeSet(parent, rank, n);
    int result = 0;
    
    for(int i =0; i<edges.size(); i++)
    {
        int u =  findParent(parent, edges[i][0]);
        int v = findParent(parent, edges[i][1]);
        int w = edges[i][2];

    
        if(u != v)
        {
            cout<<edges[i][0]<<"->"<<edges[i][1]<<"->"<<edges[i][2]<<endl;
            result += w;
            unionSet(u, v , parent, rank);
        }
    }
    cout<<"result is : "<<result<<endl;
    return result;
}


int main()
{
    vector<vector<int>> edges;

    int n;
    cout<<"Enter total number of nodes : ";
    cin>>n;
    int edges1;
    cout<<"enter number of edges: ";
    cin>>edges1;


    for(int j =0; j<edges1; j++)
    {

            vector<int> temp;

        
            cout<<"Enter u , v, w: ";
            int u, v, w;
            cin>>u>>v>>w;
            temp.push_back(u);
            temp.push_back(v);
            temp.push_back(w);

            edges.push_back(temp);
    }

    for(int i =0; i<edges1; i++)
    {
        cout<<edges[i][0]<<edges[i][1]<<edges[i][2]<<endl;
    }


    int ans = kruskals(edges, n);
    cout<<ans<<endl;
    
}


//demo example: mst = 19

    // Graph g(4); 
    // g.addEdge(0, 1, 10); 
    // g.addEdge(1, 3, 15); 
    // g.addEdge(2, 3, 4); 
    // g.addEdge(2, 0, 6); 
    // g.addEdge(0, 3, 5); 
