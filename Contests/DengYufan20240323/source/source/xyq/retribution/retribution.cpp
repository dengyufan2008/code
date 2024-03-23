//retribution
#include<bits/stdc++.h>
using namespace std;

ifstream fin("retribution.in");
ofstream fout("retribution.out");
#define cin fin
#define cout fout

namespace Input{
  mt19937_64 R;
  inline void init(int seed){
  R=mt19937_64(seed);
  }
  inline int get(int l,int r){
  uniform_int_distribution<int> distribution(l,r);
  return distribution(R);
  }
}
using Input::init;
using Input::get;

#define pii pair<int,int>
#define mpi make_pair
#define fir first
#define sec second
const int NUM=1805;

int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int n,m,q,seed;
char a[NUM][NUM];

namespace sub1{
  int flg[105][105][105][105],vis[105][105],qq[1005][4];
  set<pii> qst;
  inline void bfs(int x,int y,int sx,int sy)
  {
    flg[sx][sy][x][y]=true;
    for(int k=0;k<4;++k)
    {
      if((a[x][y]=='D' && k==0) || (a[x][y]=='U' && k==1) || (a[x][y]=='R' && k==2) || (a[x][y]=='L' && k==3))
        continue;
      int nx=x+dir[k][0],ny=y+dir[k][1];
      if(nx<1 || nx>n || ny<1 || ny>m || vis[nx][ny])
        continue;
      vis[nx][ny]=1;
      bfs(nx,ny,sx,sy);
      vis[nx][ny]=0;
    }
  }
  inline void solve1()
  {
    init(seed);
    for(int i=1;i<=q;++i)
    {
      int a=get(1,n),b=get(1,m),x=get(1,n),y=get(1,m);
      // int a,b,x,y;
      // cin>>a>>b>>x>>y;
      qq[i][0]=a,qq[i][1]=b,qq[i][2]=x,qq[i][3]=y;
      qst.insert(mpi(a,b));
    }
    for(pii it:qst)
    {
      memset(vis,0,sizeof(vis));
      bfs(it.fir,it.sec,it.fir,it.sec);
      // cout<<it.fir<<" "<<it.sec<<'\n';
    }
    for(int i=1;i<=q;++i)
    {
      if(flg[qq[i][0]][qq[i][1]][qq[i][2]][qq[i][3]]==true)
        cout<<"1";
      else
        cout<<"0";
    }
  }
}
using sub1::solve1;

namespace sub2{
  int flg[3][505][3][505],vis[3][505],qq[200005][4];
  set<pii> qst;
  inline void bfs(int x,int y,int sx,int sy)
  {
    flg[sx][sy][x][y]=true;
    for(int k=0;k<4;++k)
    {
      if((a[x][y]=='D' && k==0) || (a[x][y]=='U' && k==1) || (a[x][y]=='R' && k==2) || (a[x][y]=='L' && k==3))
        continue;
      int nx=x+dir[k][0],ny=y+dir[k][1];
      if(nx<1 || nx>n || ny<1 || ny>m || vis[nx][ny])
        continue;
      vis[nx][ny]=1;
      bfs(nx,ny,sx,sy);
      vis[nx][ny]=0;
    }
  }
  inline void solve2()
  {
    init(seed);
    for(int i=1;i<=q;++i)
    {
      int a=get(1,n),b=get(1,m),x=get(1,n),y=get(1,m);
      // int a,b,x,y;
      // cin>>a>>b>>x>>y;
      qq[i][0]=a,qq[i][1]=b,qq[i][2]=x,qq[i][3]=y;
      qst.insert(mpi(a,b));
    }
    for(pii it:qst)
    {
      memset(vis,0,sizeof(vis));
      bfs(it.fir,it.sec,it.fir,it.sec);
      // cout<<it.fir<<" "<<it.sec<<'\n';
    }
    for(int i=1;i<=q;++i)
    {
      if(flg[qq[i][0]][qq[i][1]][qq[i][2]][qq[i][3]]==true)
        cout<<"1";
      else
        cout<<"0";
    }
  }
}
using sub2::solve2;

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin>>n>>m>>q>>seed;
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
      cin>>a[i][j];
  if(q<=1000)
  {
    solve1();
  }
  else if(n<=3)
  {
    solve2();
  }
  else
    solve1();

  return 0;
}