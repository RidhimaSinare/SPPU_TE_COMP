#include<iostream>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;

class Memory
{
    int bsize,psize;
    int *blocks;
    int *process;
    int *flag;
public:
    Memory()
    {
        bsize=psize=0;
    }
    void input();
    void firstfit();
    void bestfit();
    void worstfit();
    void nextfit();
};

void Memory::input()
{
    cout<<endl<<"Enter number of blocks: ";
    cin>>bsize;
    blocks=new int[bsize];
    flag=new int[bsize];

    for(int i=0;i<bsize;i++)
    {
        cout<<endl<<"Enter size of block "<<i<<": ";
        cin>>blocks[i];
    }
    cout<<endl<<"Enter number of processes: ";
    cin>>psize;
    process=new int[psize];
    for(int i=0;i<psize;i++)
    {
        cout<<endl<<"Enter size of process "<<i<<": ";
        cin>>process[i];
    }
}

void Memory::firstfit()
{
    for(int i=0;i<bsize;i++)
    {
        flag[i]=0;
    }

    map<int,int> mp;
    map<int,int>::iterator it;
    for(int i=0;i<psize;i++)
    {
        for(int j=0;j<bsize;j++)
        {
            if(blocks[j]>=process[i] && flag[j]==0)
            {
                flag[j]=1;
                mp[j]=process[i];
                break;
            }
        }
    }

    cout<<endl<<"Block No."<<setw(20)<<"Block Size"<<setw(20)<<"Size of process allocated";
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<endl<<it->first+1<<setw(20)<<blocks[it->first]<<setw(20)<<it->second;
    }
    for(int i=0;i<bsize;i++)
    {
        if(flag[i]==0)
        {
            cout<<endl<<i+1<<setw(20)<<blocks[i]<<setw(20)<<"Not allocated";
        }
    }
}

void Memory::bestfit()
{
    for(int i=0;i<bsize;i++)
    {
        flag[i]=0;
    }
    map<int,int> mp;
    map<int,int>::iterator it;
    int wastage[bsize];
    
    for(int i=0;i<psize;i++)
    {
        for(int k=0;k<bsize;k++)
        {
            wastage[k]=0;
        }

        for(int j=0;j<bsize;j++)
        {
            if(blocks[j]>=process[i] && flag[j]==0)
            {
                wastage[j]=blocks[j]-process[i];
            }
            else
            {
                wastage[j]=9999;
            }
        }
        
        int min=*min_element(wastage,wastage+bsize);
        int pos=find(wastage,wastage+bsize,min)-wastage;
        flag[pos]=1;
        mp[pos]=process[i];

    }
    cout<<endl<<"Block No."<<setw(20)<<"Block Size"<<setw(20)<<"Size of process allocated";
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<endl<<it->first+1<<setw(20)<<blocks[it->first]<<setw(20)<<it->second;
    }
    for(int i=0;i<bsize;i++)
    {
        if(flag[i]==0)
        {
            cout<<endl<<i+1<<setw(20)<<blocks[i]<<setw(20)<<"Not allocated";
        }
    }

}

void Memory::worstfit()
{
    int wastage[bsize];
    for(int i=0;i<bsize;i++)
    {
        flag[i]=0;
    }
    map<int,int> mp;
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
                wastage[j]=-9999;
            }
        }

        int max=*max_element(wastage,wastage+bsize);
        int pos=find(wastage,wastage+bsize,max)-wastage;
        if(max==-9999)
        {
            continue;
        }
        else
        {
            flag[pos]=1;
        mp[pos]=process[i];
        }
    }
    cout<<endl<<"Block No."<<setw(20)<<"Block Size"<<setw(20)<<"Size of process allocated";
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<endl<<it->first+1<<setw(20)<<blocks[it->first]<<setw(20)<<it->second;
    }
    for(int i=0;i<bsize;i++)
    {
        if(flag[i]==0)
        {
            cout<<endl<<i+1<<setw(20)<<blocks[i]<<setw(20)<<"Not allocated";
        }
    }
}

void Memory::nextfit()
{   
    for(int i=0;i<bsize;i++)
    {
        flag[i]=0;
    }

    int blocknum=0;
    cout<<endl<<"Enter the block id to start from";cin>>blocknum;
    blocknum-=1;
    map<int,int> mp;
    map<int,int>::iterator it;
    for(int i=0;i<psize;i++)
    {   int al=0;
        for(int j=blocknum;j<bsize;j++ )
        {
            if(blocks[j]>=process[i] && flag[j]==0)
            {
                mp[j]=process[i];
                flag[j]=1;
                al=1;
                break;
            }
            
        }
        if(al==0)
        {
            for(int j=0;j<blocknum;j++ )
        {
            if(blocks[j]>=process[i] && flag[j]==0)
            {
                mp[j]=process[i];
                flag[j]=1;
                al=1;
                break;
            }
            
        }
        }

    }

    cout<<endl<<"Block No."<<setw(20)<<"Block Size"<<setw(20)<<"Size of process allocated";
    for(it=mp.begin();it!=mp.end();it++)
    {
        cout<<endl<<it->first+1<<setw(20)<<blocks[it->first]<<setw(20)<<it->second;
    }
    for(int i=0;i<bsize;i++)
    {
        if(flag[i]==0)
        {
            cout<<endl<<i+1<<setw(20)<<blocks[i]<<setw(20)<<"Not allocated";
        }
    }

}


int main()
{
    Memory m;
    m.input();
    //m.firstfit();
    // m.bestfit();
    // m.worstfit();
    m.nextfit();
}
