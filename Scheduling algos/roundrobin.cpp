#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;

//premp

class Process
{
public: 
    int id;
    int bt;
    int at;
};

void roundrobin(Process proc[],int wt[],int tat[],int ct[],int n,int ts)
{
    int rt[n];
    queue<int>RQ;
    int currenttime=0,curr,completedtasks=0;

    for(int j=0;j<n;j++)
    {
        rt[j]=proc[j].bt;
    }

    for(int j=0;j<n;j++)
    {
        if(proc[j].at<=currenttime)
        {
            RQ.push(j);
        }
    }

    while(completedtasks!=n)
    {
        curr=RQ.front();
        RQ.pop();

        int cntr=0;

        while(cntr!=ts && cntr!=rt[curr])
        {
            currenttime++;
            cntr++;

            for(int j=0;j<n;j++)
            {
                if(proc[j].at==currenttime)
                {
                    RQ.push(j);
                }
            }
        }

        rt[curr]-=cntr;

        if(rt[curr]==0)
        {
            completedtasks++;
            ct[curr]=currenttime;
            tat[curr]= ct[curr]-proc[curr].at;
            wt[curr]=tat[curr]-proc[curr].bt;
        }
        else
        {
            RQ.push(curr);
        }

    }
}

int main() {
    
    Process proc[] = { {1, 8, 0}, {2, 2, 5}, {3, 7, 1 }, {4, 3, 6}, {5, 5, 8} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];
    for(int i=0;i<n;i++)
        wt[i] = 0;

    int ts=3;
    
    roundrobin(proc, wt,tat,ct,n,ts);
    
    cout.width(5);
    cout << "ID";
    cout.width(5);
    cout << "AT";
    cout.width(5);
    cout << "BT";
    cout.width(5);
    cout << "CT";
    cout.width(5);
    cout << "TAT";
    cout.width(5);
    cout << "WT" << endl;
    
    for (int i = 0; i < n; i++)
    {
        cout.width(5);
        cout << proc[i].id;
        cout.width(5);
        cout << proc[i].at;
        cout.width(5);
        cout << proc[i].bt;
        cout.width(5);
        cout << ct[i];
        cout.width(5);
        cout << tat[i];
        cout.width(5);
        cout << wt[i] << endl;
    }

    return 0;
}