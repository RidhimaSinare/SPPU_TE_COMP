#include<iostream>
#include<iomanip>
#include<algorithm>
#include<map>
using namespace std;

class Memory
{
    int *blocks;
    int *process;
    int *flag;
    int bsize,psize;

public:
    Memory()
    {
        bsize=0;
        psize=0;
    }
    void input();
    void firstfit();
    void bestfit();
    void worstfit();
};

void Memory::input()
{
    cout<<endl<<"Enter number of blocks: ";
    cin>>bsize;
    cout<<endl<<"Enter number of process: ";
    cin>>psize;

    blocks=new int [bsize];
    process=new int[psize];
    flag= new int[bsize];

    cout<<endl<<"Enter block sizes: ";
    for(int i=0;i<bsize;i++)
    {
        cout<<endl<<"Block "<<i<<": ";
        cin>>blocks[i];
    }
    cout<<endl<<"Enter process sizes: ";
    for(int i=0;i<psize;i++)
    {
        cout<<endl<<"Process "<<i<<": ";
        cin>>process[i];
    }
}

void Memory::firstfit()
{
    for(int i=0;i<bsize;i++)
    {
        flag[i]=0;
    }

    map<int,int>mp;
    map<int,int>::iterator it;

    for(int i=0;i<psize;i++)
    {
        for(int j=0;j<bsize;j++)
        {
            if(process[i]<=blocks[j] && flag[j]==0)
            {
                mp[j]=process[i];
                flag[j]=1;
                break;
            }
        }
    }

    cout<<endl<<"Block No."<<setw(20)<<"Size of Block"<<setw(20)<<"Allocated Size"<<endl;
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<endl;
    }

}

void Memory::bestfit()
{
    for(int i=0;i<bsize;i++)
    {
        flag[i]=0;
    }
    int wastage[bsize];

    map<int,int>mp;
    map<int,int>::iterator it;
    for(int i=0;i<psize;i++)
    {
        for(int k=0;k<bsize;k++)
        {
            wastage[k]=0;
        }

        for(int j=0;j<bsize;j++)
        {
            if(process[i]<=blocks[j] && flag[j]==0)
            {
                wastage[j]=blocks[j]-process[i];
            }
            else
            {
                wastage[j]=9999;
            }
        }

        int min=*min_element(wastage,wastage+bsize);
        int pos= find(wastage,wastage+bsize,min)-wastage;
        mp[pos]=process[i];
        flag[pos]=1;
    }
    cout<<endl<<"Block No."<<setw(20)<<"Size of Block"<<setw(20)<<"Allocated Size"<<endl;
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<endl;
    }
}

void Memory::worstfit()
{   int i,j,k;
    for(i=0;i<bsize;i++)
    {
        flag[i]=0;
    }
    int wastage[bsize];
    map<int,int>mp;
    map<int,int>::iterator it;

    for(i=0;i<psize;i++)
    {
        for(k=0;k<bsize;k++)
        {
            wastage[k]=0;
        }

        for(j=0;j<bsize;j++)
        {
            if(process[i]<=blocks[j] && flag[j]==0)
            {
                wastage[j]=blocks[j]-process[i];
            }
            else
            {
                wastage[j]=0;
            }
        }

        int max=*max_element(wastage,wastage+bsize);
        int pos=find(wastage,wastage+bsize,max)-wastage;
        mp[pos]=process[i];
        flag[pos]=1;
    }
    cout<<endl<<"Block No."<<setw(20)<<"Size of Block"<<setw(20)<<"Allocated Size"<<endl;
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<endl;
    }
}

int main()
{
    Memory m;
    m.input();
    //m.firstfit();
    //m.bestfit();
    m.worstfit();
}

