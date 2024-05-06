#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include <unordered_map>
using namespace std;

class node
{
    string name;
    node* next;
    node* down;

    node(string n)
    {
        name=n;
        next=nullptr;
        down=nullptr;
    }

    friend class Graph;
};

class Graph
{
    node* head = nullptr;
    unordered_map<string, vector<string>> adjlist;

public:

    void add(string a, string b)
    {
        if(head==nullptr)
        {
            node* nodea = new node(a);
            node* nodeb = new node(b);
            head=nodea;
            nodea->next = nodeb;
        }
        else
        {
            node* curr = head;
            node* prev = NULL;
            bool found = false;
            while(curr!=nullptr)
            {
                if(curr->name==a)
                {
                    found=true;
                    node* neigh = curr;
                    while(neigh->next!=nullptr && neigh->name!=b)
                    {
                        neigh = neigh->next;
                    }
                    node* nodeb = new node(b);
                    neigh->next = nodeb;
                    cout<<endl<<"New node added";
                    break;
                }
                prev = curr;
                curr = curr->down;
            }

            if(!found)
            {
                node* nodea = new node(a);
                node* nodeb = new node(b);
                prev->down = nodea;
                nodea->next = nodeb;
                cout<<endl<<"New node added";
            }
        }//end of else
    }//

    void addEdge(string a, string b)
    {
        add(a,b);
        add(b,a);
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }//

    void display()
    {
        node* curr = head;

        while(curr!=nullptr)
        {
            cout<<"{"<<curr->name<<" : ";
            node* neigh = curr->next;
            while(neigh!=nullptr)
            {
                cout<<neigh->name<<", ";
                neigh = neigh->next;
            }
            cout<<"}";
            cout<<endl;
            curr = curr->down;
        }
    }//

    void dfs(string start, vector<string> &visited)
    {
        visited.push_back(start);
        cout<<" "<<start;

        for(string i: adjlist[start])
        {
            if(find(visited.begin(), visited.end(), i)==visited.end())
            {
                dfs(i, visited);
            }
        }
    }//

    void bfs(vector<string> &visited, queue<string> &q)
    {
        if(q.empty()) return;

        string curr = q.front();
        q.pop();
        cout<<curr<<" ";

        for(string i: adjlist[curr])
        {
            if(find(visited.begin(), visited.end(), i)==visited.end())
            {
                q.push(i);
                visited.push_back(i);
                bfs(visited, q);
            }
        }
    }
};


int main()
{
    Graph g;
    int n = 0;
    cout<<"\nEnter number of edges: ";
    cin>>n;
    string a, b;

    for(int i=0;i<n;i++)
    {
        cout<<endl<<"Enter the names of cities: ";
        cin>>a>>b;
        g.addEdge(a,b);
    }

    //dfs
    // vector<string> visited;
    // cout<<endl;
    // g.dfs("a", visited);

    //bfs
    vector<string>vis;
    queue<string> q;
    q.push("a");
    vis.push_back("a");
    cout<<endl;
    g.bfs(vis,q);

    // g.display();
}



// Code with progress printing
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_map>
// using namespace std;

// class Graph
// {   public:
//     int vertices;
//     vector<vector<int>> adjlist;
//     unordered_map<string, int> city_to_index;
//     vector<string> index_to_city;

// public:
//     Graph(int v) {
//         vertices = v;
//         adjlist.resize(v);
//     }

//     void addEdge(string a, string b) {
//         if (city_to_index.find(a) == city_to_index.end()) {
//             city_to_index[a] = city_to_index.size();
//             index_to_city.push_back(a);
//         }
//         if (city_to_index.find(b) == city_to_index.end()) {
//             city_to_index[b] = city_to_index.size();
//             index_to_city.push_back(b);
//         }
//         int u = city_to_index[a];
//         int v = city_to_index[b];
//         adjlist[u].push_back(v);
//         adjlist[v].push_back(u);
//     }

//     void printProgress(vector<int>& progress) {
//         for (int i : progress) {
//             cout << index_to_city[i] << " ";
//         }
//         cout << endl;
//     }

//     void bfs(vector<bool>& visited, queue<int>& q, vector<int>& progress) {
//         if (q.empty()) {
//             return;
//         }

//         int u = q.front();
//         q.pop();
//         progress.push_back(u);

//         for (int v : adjlist[u]) {
//             if (!visited[v]) {
//                 visited[v] = true;
//                 q.push(v);
//             }
//         }
//         printProgress(progress);
//         bfs(visited, q, progress);
//     }

//     void dfs(int u, vector<bool>& visited, vector<int>& progress) {
//         visited[u] = true;
//         progress.push_back(u);
//         printProgress(progress);

//         for (int v : adjlist[u]) {
//             if (!visited[v]) {
//                 dfs(v, visited, progress);
//             }
//         }
//     }
// };

// int main()
// {
//     int edges, choice;
//     char ans = 'y';
//     int vertices;
//     cout<<"Enter no of vertices: ";
//     cin>>vertices;
//     cout << "Enter the number of edges: ";
//     cin >> edges;

//     Graph g(vertices);

//     string city1, city2;
//     for (int i = 0; i < edges; i++) {
//         cout << "Enter edge " << i + 1 << " (City A City B): ";
//         cin >> city1 >> city2;
//         g.addEdge(city1, city2);
//     }

//     do {
//         cout << "\n1. BFS\n2. DFS\nEnter choice: ";
//         cin >> choice;

//         int start_vertex = 0; // Assuming start from vertex 0
//         vector<bool> visited(g.vertices, false);
//         vector<int> progress;
//         queue<int> q;
//         switch (choice) {
//         case 1:
//             visited[start_vertex] = true;
            
//             q.push(start_vertex);
//             g.bfs(visited, q, progress);
//             break;

//         case 2:
//             g.dfs(start_vertex, visited, progress);
//             break;

//         default:
//             cout << "\nInvalid!";
//             break;
//         }

//         cout << "Final Traversal: ";
//         g.printProgress(progress);

//         cout << "\nContinue? (y/n): ";
//         cin >> ans;
//     } while (ans == 'y' || ans == 'Y');

//     return 0;
// }