#include<iostream>
#include<iomanip>
using namespace std;

//non premp

class Process
{
public:
    int id;
    int bt;
    int at;
    int priority;
};

void npPriority(Process proc[],int n,int wt[],int ct[],int tat[])
{
    int rt[n];

    for(int i=0;i<n;i++)
    {
        rt[i]=proc[i].bt;
    }

    int currenttime=0,completedtask=0,hpt=0,maxprio=INT_MAX;
    bool activetask=false;

    while(completedtask!=n)
    {
        for(int j=0;j<n;j++)
        {
            if(proc[j].at<=currenttime && rt[j]>0 && proc[j].priority<maxprio)//considering 1 being highest priority so find smallest num
            {
                hpt=j;
                maxprio = proc[j].priority;
                activetask=true;
            }
        }

        if(activetask=false)
        {
            currenttime++;
            continue;
        }

        currenttime+=proc[hpt].bt;
        rt[hpt]=0;
        maxprio=INT_MAX;
        activetask=false;
        completedtask++;
        ct[hpt]=currenttime;
        tat[hpt]=ct[hpt]-proc[hpt].at;
        wt[hpt]=tat[hpt]-proc[hpt].bt;
    }
}

int main () {
    Process proc[] = { {1, 11, 0, 2}, {2, 28, 5, 0}, {3, 2, 12, 3}, {4, 10, 2, 1}, {5, 16, 9, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];
    
    npPriority(proc, n, wt, ct, tat);

    cout.width(5);
    cout<<"ID";
    cout.width(5);
    cout<<"AT";
    cout.width(5);
    cout<<"BT";
    cout.width(5);
    cout<<"CT";
    cout.width(5);
    cout<<"TAT";
    cout.width(5);
    cout<<"WT"<<endl;

    for(int i=0;i<n;i++) {
        cout.width(5);
        cout<<proc[i].id;
        cout.width(5);
        cout<<proc[i].at;
        cout.width(5);
        cout<<proc[i].bt;
        cout.width(5);
        cout<<ct[i];
        cout.width(5);
        cout<<tat[i]; 
        cout.width(5);
        cout<<wt[i]<<endl;
    }     

    return 0;
}