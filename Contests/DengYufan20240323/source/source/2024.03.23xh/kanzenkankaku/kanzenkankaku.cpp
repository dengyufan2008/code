#include<bits/stdc++.h>
inline int read()
{   int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c))f|=(c=='-'),c=getchar();
    while(isdigit(c))x=x*10+(c&15),c=getchar();
    return f?-x:x;
}
using namespace std;
int n,c,gs[3005],s[3005],ans;
priority_queue<int,vector<int>,greater<int> > q;
int main()
{   freopen("kanzenkankaku.in","r",stdin);
    freopen("kanzenkankaku.out","w",stdout);
    n=read(),c=read();
    s[0]=-200686,s[n+1]=-200687;
    for(int i=1;i<=n;++i)s[i]=read(),gs[s[i]]++,ans=max(ans,gs[s[i]]);
    // cerr<<gs[2]<<endl;
    for(int i=1,len,st,ST,St,id;i<=n;++i)
    {   while(!q.empty())q.pop();
        len=1;
        st=ST=St=id=0;
        for(int j=1;;++j)
            if(s[i-j]!=s[i+j])
            {   st=j;
                break;
            }
            else len+=2;
        ans=max(ans,len);
        if(st!=0)
        {   for(int j=st;i-j>=0;++j)
                if(j!=st&&s[i-j]<s[i-j+1])
                {   ST=j;
                    break;
                }
            int now=st,flag=0;
            for(int j=st;i+j<=n;++j)
            {   q.push(s[i+j]);
                while(!q.empty()&&now<ST&&q.top()==s[i-now])
                {   q.pop();
                    now++;
                    if(q.empty())flag=1;
                }
            }
            if(flag)
            {   for(int j=now;;++j)
                    if(s[i-j]!=s[i+j])
                    {   now=j;
                        break;
                    }
            }
            ans=max(ans,2*now-1);
        }
    }
    // cerr<<ans<<endl;
    for(int i=1,len,st,ST,St,id;i<=n;++i)
    {   while(!q.empty())q.pop();
        len=0;
        st=ST=St=id=0;
        for(int j=1;;++j)
            if(s[i-j+1]!=s[i+j])
            {   st=j;
                break;
            }
            else len+=2;
        ans=max(ans,len);
        if(st!=0)
        {   //if(i==5)cerr<<st;
            for(int j=st;i-j+1>=0;++j)
                if(j!=st&&s[i-j+1]<s[i-j+2])
                {   ST=j;
                    break;
                }
            // if(i==5)cerr<<ST<<endl;
            int now=st,flag=0;
            for(int j=st;i+j<=n;++j)
            {   q.push(s[i+j]);
                while(!q.empty()&&now<ST&&q.top()==s[i-now+1])
                {   q.pop();
                    now++;
                    if(q.empty())flag=1;
                }
            }
            if(flag)
            {   for(int j=now;;++j)
                    if(s[i-j+1]!=s[i+j])
                    {   now=j;
                        break;
                    }
            }
            // if(i==3)cerr<<"!!!"<<now<<' '<<st<<endl;
            ans=max(ans,2*now-2);
            // cerr<<2*now-2<<' '<<i<<endl;
        }
    }
    // cerr<<ans<<endl;
    for(int i=2,st;i<=n;++i)
    {   st=i;
        for(int j=1;i-j>=0;++j)
            if(j!=1&&s[i-j]<s[i-j+1])
            {   st=j;
                break;
            }
        int minn=20071026,gs=0,flag=0,GS=0;
        while(!q.empty())q.pop();
        int now=1;
        for(int j=0;i+j<=n;++j)
        {   if(s[i+j]<s[i-now])
            {   if(minn!=20071026&&minn!=s[i+j])break;
                minn=s[i+j];
                gs++;
            }
            else
            {   if(s[i+j]==minn)gs++;
                else q.push(s[i+j]);
            }
            // if(i==4&&j==0)cerr<<q.top()<<' '<<s[i-now]<<' '<<st;
            if(!q.empty()&&q.top()<s[i-now])break;
            while(!q.empty()&&now<st&&q.top()==s[i-now])
            {   q.pop();
                now++;
                if(q.empty())flag=1;
            }
        }
        if(flag)
        { //  cerr<<i<<' '<<now<<endl;
            for(int j=now;;++j)
                if(s[i-j]!=s[i+gs+j-1])
                {   now=j;
                    break;
                }
        }
        ans=max(ans,2*now-2+gs);
        // if(2*now-2+gs==1528)cerr<<i<<"!!"<<now<<" "<<gs<<endl;
        // if(i==2)cerr<<gs<<' '<<now<<endl;
    }
    // cerr<<ans;

    reverse(s+1,s+n+1);
    for(int i=1;i<=n;++i)s[i]=-s[i];
    for(int i=1,len,st,ST,St,id;i<=n;++i)
    {   while(!q.empty())q.pop();
        len=1;
        st=ST=St=id=0;
        for(int j=1;;++j)
            if(s[i-j]!=s[i+j])
            {   st=j;
                break;
            }
            else len+=2;
        ans=max(ans,len);
        if(st!=0)
        {   for(int j=st;i-j>=0;++j)
                if(j!=st&&s[i-j]<s[i-j+1])
                {   ST=j;
                    break;
                }
            int now=st,flag=0;
            for(int j=st;i+j<=n;++j)
            {   q.push(s[i+j]);
                while(!q.empty()&&now<ST&&q.top()==s[i-now])
                {   q.pop();
                    now++;
                    if(q.empty())flag=1;
                }
            }
            if(flag)
            {   for(int j=now;;++j)
                    if(s[i-j]!=s[i+j])
                    {   now=j;
                        break;
                    }
            }
            ans=max(ans,2*now-1);
        }
    }
    for(int i=1,len,st,ST,St,id;i<=n;++i)
    {   while(!q.empty())q.pop();
        len=0;
        st=ST=St=id=0;
        for(int j=1;;++j)
            if(s[i-j+1]!=s[i+j])
            {   st=j;
                break;
            }
            else len+=2;
        ans=max(ans,len);
        if(st!=0)
        {   //if(i==5)cerr<<st;
            for(int j=st;i-j+1>=0;++j)
                if(j!=st&&s[i-j+1]<s[i-j+2])
                {   ST=j;
                    break;
                }
            // if(i==5)cerr<<ST<<endl;
            int now=st,flag=0;
            for(int j=st;i+j<=n;++j)
            {   q.push(s[i+j]);
                while(!q.empty()&&now<ST&&q.top()==s[i-now+1])
                {   q.pop();
                    now++;
                    if(q.empty())flag=1;
                }
            }
            if(flag)
            {   for(int j=now;;++j)
                    if(s[i-j+1]!=s[i+j])
                    {   now=j;
                        break;
                    }
            }
            // if(i==3)cerr<<"!!!"<<now<<' '<<st<<endl;
            ans=max(ans,2*now-2);
            // cerr<<2*now-2<<' '<<i<<endl;
        }
    }
    // cerr<<ans<<endl;
    for(int i=2,st;i<=n;++i)
    {   st=i;
        for(int j=1;i-j>=0;++j)
            if(j!=1&&s[i-j]<s[i-j+1])
            {   st=j;
                break;
            }
        int minn=20071026,gs=0,flag=0,GS=0;
        while(!q.empty())q.pop();
        int now=1;
        for(int j=0;i+j<=n;++j)
        {   if(s[i+j]<s[i-now])
            {   if(minn!=20071026&&minn!=s[i+j])break;
                minn=s[i+j];
                gs++;
            }
            else
            {   if(s[i+j]==minn)gs++;
                else q.push(s[i+j]);
            }
            // if(i==4&&j==0)cerr<<q.top()<<' '<<s[i-now]<<' '<<st;
            if(!q.empty()&&q.top()<s[i-now])break;
            while(!q.empty()&&now<st&&q.top()==s[i-now])
            {   q.pop();
                now++;
                if(q.empty())flag=1;
            }
        }
        if(flag)
        { //  cerr<<i<<' '<<now<<endl;
            for(int j=now;;++j)
                if(s[i-j]!=s[i+gs+j-1])
                {   now=j;
                    break;
                }
        }
        ans=max(ans,2*now-2+gs);
        // if(i==2)cerr<<gs<<' '<<now<<endl;
    }
    // cerr<<ans;
    cout<<ans;
    // cerr<<clock();
    return 0;
}