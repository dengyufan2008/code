#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
int n,c,a[maxn],bk[maxn],s,val[maxn];
void solve(int l,int r)
{ 
    while(l>=1&&r<=n&&a[l]==a[r])
        ++r,--l; 
    int tr=r,mi;
    memset(bk,0,sizeof bk);
    ++bk[a[tr]];
    mi=a[tr];
    int k=0;
    priority_queue<int,vector<int>,greater<int> > q;
    q.push(a[tr]);
    for(int j=l;j>=1;j--)
    {
        if(j!=l&&a[j]<a[j+1])
        {
            k=j;
            if(q.empty())
            {
                ++tr;
                while(tr<=n&&k>0&&a[tr]==a[k])
                    ++tr,--k;
            }
            break;
        }
        int dlt=0;
        while(tr<n&&!bk[a[j]])
            ++tr,++bk[a[tr]],q.push(a[tr]);
        if(!bk[a[j]]||q.top()!=a[j])
        {
            k=j;
            
            break;
        }
        q.pop();
        --bk[a[j]];
    }
    s=max(s,r-l-1+(l-k)*2);
}
void solve2(int l)
{
    int tr=l+1,mi;
    memset(bk,0,sizeof bk);
    ++bk[a[tr]];
    mi=a[tr];
    int k=0;
    priority_queue<int,vector<int>,greater<int> > q;
    q.push(a[tr]);
    int pd=0,cs=a[l],ts=0;
    for(int j=l;j>=1;j--)
    {
        // cout<<"#"
        // if(l==9)
        // {
        //     cout<<"###"<<j<<'\n';
        // }
        if(j!=l&&a[j]<a[j+1])
        {  
            // cout<<j<<'\n';
            k=j; 
            // cout<<j<<' '<<tr<<' '<<q.size()<<'\n';
            // cout<<q.size()
            int svk=k,svtr=tr;
            if(!q.empty()&&!pd)
            {
                int qwq=q.top();
                while(!q.empty()&&q.top()==qwq)
                    ++ts,q.pop();
                // cout<<ts<<"\n";
                pd=qwq;
                if(!q.empty())
                    ts=0,pd=0;
            }

            if(q.empty())
            {
                ++tr;
                while(tr<=n&&k>0&&a[tr]==a[k])
                    ++tr,--k;
            }
            k=svk,tr=svtr;
    s=max(s,(l-k)*2+ts);
            break;
        }
        int dlt=0;
        while(tr<n&&!bk[a[j]])
            ++tr,++dlt,++bk[a[tr]],q.push(a[tr]); 
        if(bk[a[j]]&&q.top()!=a[j]&&!pd)
        {
            if(q.top()<cs)
            {
                int tp=q.top();
                bk[tp]=0;
                while(!q.empty()&&q.top()==tp)
                    q.pop(),++ts;
                pd=tp;
                if(q.top()!=a[j])
                {
                    ts=0;
                    k=j;
                    break;
                }
            }
            else
            {
                k=j;
                break;
            }
        }
        // cout<<tr<<'\n';
        if(!bk[a[j]]||(q.top())!=a[j])
        {
            tr-=dlt;
            k=j;
            break;
        }
        q.pop();
        --bk[a[j]];
    } 
    {
        // cout<<"###"<<k<<' '<<l<<' '<<ts<<'\n';
    }
    int tma=0,tmi=INT_MAX;
    for(int i=k+1;i<=l;i++)
        tma=max(tma,a[i]),tmi=min(tmi,tma);
    int sv=tr;
    if(!pd)
    {
        for(int j=sv+1;j<=n;j++)
        {
            if(a[j]<tma)
                break;
            if(a[j]<tmi)
            {
                pd=a[j];
                break;
            }
        }
    }
    if(pd)
    {
        while(tr<n&&(a[tr+1]==pd||a[tr+1]>=tma))
            ++tr,ts+=a[tr]==pd;
    }  
    s=max(s,(l-k)*2+ts);
}
int b[maxn];
int main()
{
    // freopen("kanzenkankaku.in","r",stdin);
    // freopen("kanzenkankaku.out","w",stdout);
    cin>>n>>c;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    // solve2(3);
    // solve2(1);
    for(int i=1;i<=n;i++)
    {
        solve(i,i+1);
        solve(i-1,i+1);
    }
    for(int i=1;i<=n;i++) 
        solve2(i);  
        int ts=0;
    reverse(a+1,a+n+1); 
    for(int i=1;i<=n;i++)
    {
        a[i]=c+1-a[i];
        // cout<<a[i]<<' ';
    }
    // cout<<'\n';
    // solve2(2);/
            for(int i=1;i<=n;i++)
            {
                ++bk[a[i]];
                s=max(s,bk[a[i]]);
            }
            memset(bk,0,sizeof bk);
    // for(int i=1;i<=n;i++)
    // {
    //     for(int j=i+1;j<=n;j++)
    //     {
    //         for(int i=1;i<=n;i++)
    //             b[i]=a[i]; 
    //         // cerr<<i<<" "<<j<<'\n';
    //         sort(b+i,b+j+1);
    //         for(int k=1;k<=n;k++)
    //         {
    //             int l=k,r=k+1;
    //             while(l>=1&&r<=n&&b[l]==b[r])
    //             {
    //                 ++r,--l; 
    //             }
    //             ts=max(ts,r-l-1);
    //             if(r-l-1==35)
    //             {
    //                 cout<<"###"<<i<<' '<<j<<' '<<l<<' '<<r<<' '<<"ANS"<<r-l-1<<'\n';
    //             }
    //             l=k-1,r=k+1;
    //             while(l>=1&&r<=n&&b[l]==b[r])
    //             {
    //                 ++r,--l; 
    //             }
    //             if(r-l-1==35)
    //             {
    //                 cout<<"###"<<i<<' '<<j<<' '<<l<<' '<<r<<' '<<"ANS"<<r-l-1<<'\n';
    //             }
    //             ts=max(ts,r-l-1);
    //         }       
    //     }
    // }
    // cout<<"\n";
    // solve2(3);
    for(int i=1;i<=n;i++)
    {
        solve(i,i+1);
        solve(i-1,i+1);
    }
    for(int i=1;i<=n;i++) 
        solve2(i);  
    cout<<s;
    return 0;
}