#include<iostream>
#include<iomanip>
using namespace std;

// sort processes as per arrival time
// calc ct = bt + ct[prev process]
// calc tat= ct-at
// calc wt = tat - bt
// calc rt=wt

void sort(int process[],int at[],int bt[],int n)
{   int temp=0;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(at[j]>at[j+1])
            {
                //sort at
                temp=at[j];
                at[j]=at[j+1];
                at[j+1]=temp;

                //sort bt
                temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                //sort process num
                temp=process[j];
                process[j]=process[j+1];
                process[j+1]=temp;
            }
        } 
    }
}//end of sort

void calc_ct(int bt[],int n,int ct[])
{
    ct[0]=bt[0];
    for(int i=1;i<n;i++)
    {
        ct[i]= bt[i]+ct[i-1];
    }
}

void calc_tat(int at[],int ct[],int n,int tat[])
{
    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
    }
}

void calc_wt(int tat[],int bt[],int n,int wt[])
{
    for(int i=0;i<n;i++)
    {
        wt[i]=tat[i]-bt[i];
    }
}

void calc_rt(int wt[],int rt[],int n)
{
    for(int i=0;i<n;i++)
    {
        rt[i]= wt[i];
    }
}

void fcfs(int process[],int at[],int bt[],int ct[],int tat[],int wt[],int rt[],int n)
{
    sort(process,at,bt,n);
    calc_ct(bt,n,ct);
    calc_tat(at,ct,n,tat);
    calc_wt(tat,bt,n,wt);
    calc_rt(wt,rt,n);

}

int main()
{
    int n;
    cout<<endl<<"Enter number of processes: ";cin>>n;
    int at[n],bt[n],process[n];
    for(int i=0;i<n;i++)
    {   process[i]=i+1;
        cout<<"Enter the arrival and burst time of {i}th process: ";
        cin>>at[i]>>bt[i];
    }
    int ct[n],tat[n],wt[n],rt[n];
    fcfs(process,at,bt,ct,tat,wt,rt,n);
    cout << endl;
    cout << endl
         << "Process Id" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Completion Time" << setw(20) << "Turn Around Time" << setw(20) << "Waiting Time" << setw(20) << "Response Time";
    for (int i = 0; i < n; i++)
    {
        cout << endl
             << process[i] << setw(20) << at[i] << setw(20) << bt[i] << setw(20) << ct[i] << setw(20) << tat[i] << setw(20) << wt[i] << setw(20) << rt[i];
    }

    return 0;
}