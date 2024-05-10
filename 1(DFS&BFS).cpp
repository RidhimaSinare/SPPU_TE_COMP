#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
using namespace std;

//1 dfs bfs

class Graph
{public:
    vector<vector<int>> adjlist;
    vector<string> index_to_city;
    unordered_map<string, int> city_to_index;
    int v;

    Graph(int vertices)
    {
        v = vertices;
        adjlist.resize(v);
    }

    void addEdge(string a, string b)
    {
        if(city_to_index.find(a) == city_to_index.end())
        {
            city_to_index[a] = city_to_index.size();
            index_to_city.push_back(a);
        }
        if(city_to_index.find(b) == city_to_index.end())
        {
            city_to_index[b] = city_to_index.size();
            index_to_city.push_back(b);
        }

        int aidx = city_to_index[a];
        int bidx = city_to_index[b];
        adjlist[aidx].push_back(bidx);
        adjlist[bidx].push_back(aidx);
    }//end of addEdge

    void printProgress(vector<int> &progress)
    {
        cout<<endl;
        for(int i: progress)
        {
            cout<<index_to_city[i]<<" ";
        }    
    }

    void dfs(vector<bool> &visited, vector<int> &progress, int idx)
    {   
        visited[idx] = true;
        progress.push_back(idx);
        printProgress(progress);

        for(int j: adjlist[idx])
        {
            if(!visited[j])
            {
                dfs(visited, progress, j);
            }
        }
    }//end of dfs

    void bfs(vector<bool> &visited, vector<int> &progress, queue<int> q)
    {
        if(q.empty()) return ;

        //else
        int curr = q.front();
        q.pop();
        progress.push_back(curr);

        for(int v: adjlist[curr])
        {
            if(!visited[v])
            {
                q.push(v);
                visited[v] = true;
            }
        }

        printProgress(progress);
        bfs(visited, progress, q);
    }//end of bfs
};//end of class graph

int main()
{   
    int n;
    cout<<"\nEnter number of cities: ";cin>>n;

    int edges;
    cout<<"\nEnter number of routes: ";cin>>edges;
    
    Graph g(n);

    string a, b;
    for(int i=0;i<edges;i++)
    {
        cout<<endl<<"Enter each route : ";cin>>a>>b;
        g.addEdge(a,b);
    }

    vector<bool>visited(n, false);
    vector<int>progress;
    queue<int> q;

    //dfs
    // g.dfs(visited, progress, 0);

    //bfs
    q.push(0);
    visited[0] = true;
    g.bfs(visited, progress, q);
    return 0;
}
