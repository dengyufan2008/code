//kanzenkankaku
#include<bits/stdc++.h>
using namespace std;

ifstream fin("kanzenkankaku.in");
ofstream fout("kanzenkankaku.out");
#define cin fin
#define cout fout

const int NUM=3005;

int n,cn,maxn;
int s[NUM];

namespace sub1{
  int p[3005],np[6005],d[6005],qs[3005];
  inline void sr(int x,int y)
  {
    int tot=0;
    for(int i=0;i<x;++i)
      p[i]=s[i];
    for(int i=y+1;i<n;++i)
      p[i]=s[i];
    for(int i=x;i<=y;++i)
      qs[++tot]=s[i];
    sort(qs+1,qs+1+tot);
    int now=0;
    for(int i=x;i<=y;++i)
    {
      ++now;
      p[i]=qs[now];
    }
  }
  inline int init()
  {
    np[0]=5001,np[1]=5000;
    int j=2;
    for(int i=0;i<n;++i)
    {
      np[j++]=p[i];
      np[j++]=5000;
    }
    np[j]=5002;
    return j;
  }
  inline int manacher()
  {
    int len=init(),maxlen=-1,idx,mx=0;
    for(int i=1;i<len;++i)
    {
      if(i<mx)
        d[i]=min(d[2*idx-i],mx-i);
      else
        d[i]=1;
      while(np[i-d[i]]==np[i+d[i]])
        ++d[i];
      if(mx<i+d[i])
      {
        idx=i;
        mx=i+d[i];
      }
      maxlen=max(maxlen,d[i]-1);
    }
    return maxlen;
  }
  inline void solve1()
  {
    for(int i=0;i<n;++i)
    {
      for(int j=i;j<n;++j)
      {
        sr(i,j);
        maxn=max(maxn,manacher());
      }
    }
    cout<<maxn<<'\n';
  }
}
using sub1::solve1;

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin>>n>>cn;
  for(int i=0;i<n;++i)
    cin>>s[i];
  solve1();

  return 0;
}