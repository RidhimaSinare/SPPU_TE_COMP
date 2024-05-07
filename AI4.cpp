//Graph Coloring Problem using Backtracking
//Algorithm:
//1.Create a recursive function that takes graph, color array, num of vertices and current index
//2.If curr index== num of vertices, print color config array.
//3.Assign color to every vertex from 1 to n
//  3.1.For every assigned color check if config is safe(i.e adjacent vertex do not have same color)
//      recursively call with index increment and num of vertex else return false
//  3.2.If any recursive function returns true break loop and return true
//  3.3.If no rec returns true then return false

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int n=4;

bool isSafe(int v,bool graph[n][n],int color[],int c)
{
    for(int i=0;i<n;i++)
    {
        if(graph[v][i] && color[c]==i)
        {
            return false;
        }
    }
    return true;
}

    
