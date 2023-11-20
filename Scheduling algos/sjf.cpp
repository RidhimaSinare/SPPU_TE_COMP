#include<iostream>
#include<iomanip>
using namespace std;

//preemptive sjf
//ct= currenttime+1
// wt= ct-at-bt  or tat-bt
//tat=ct-at

class Process
{
public:
    int id;
    int bt;
    int at;
};

void srtf(Process proc[],int n, int wt[],int ct[],int tat[])
{
    int rt[n];

    for(int i=0;i<n;i++)
    {
        rt[i]=proc[i].bt;
    }

    int currenttime=0,completedtasks=0,shortesttask=0,minburst=INT_MAX;
    bool activetask=false;

    while(completedtasks!=n)
    {
        //finding sjf task
        for(int j=0;j<n;j++)
        {
            if(proc[j].at<=currenttime && proc[j].bt<minburst && rt[j]>0)
            {
                shortesttask=j;
                minburst=proc[j].bt;
                activetask=true;
            }
        }

        if(activetask==false)
        {
            currenttime++;
            continue;
        }

        rt[shortesttask]--;
        minburst=rt[shortesttask];
        if(minburst==0)
        {
            minburst=INT_MAX;
        }

        if(rt[shortesttask]==0)
        {
            completedtasks++;
            activetask=false;
            ct[shortesttask]=currenttime+1;
            tat[shortesttask]=ct[shortesttask]-proc[shortesttask].at;
            wt[shortesttask]=tat[shortesttask]-proc[shortesttask].bt;
            if(wt[shortesttask]<0)
                wt[shortesttask]=0;
        }

        currenttime++;

    }
}

int main()
{
    int n;
    cout<<endl<<"Enter number of processes: ";cin>>n;
    Process proc[n];
    for(int i=0;i<n;i++)
    {   proc[i].id=i+1;
        cout<<"Enter the arrival and burst time of {i}th process: ";
        cin>>proc[i].at>>proc[i].bt;
    }

    int ct[n],wt[n],tat[n];

    srtf(proc,n,wt,ct,tat);

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