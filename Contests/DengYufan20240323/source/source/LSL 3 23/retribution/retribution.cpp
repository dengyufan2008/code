#include<bits/stdc++.h>
using namespace std;
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
const int N=1e5+10,M=N*3,K=1e6+10,d1[4]={-1,0,1,0},d2[4]={0,1,0,-1};
const char it[4]={'U','R','D','L'};
int h[N],nex[M],to[M],tot,cnt;
struct edge{
  int x,y;
}e[M];
int dfn[N],low[N],num,sd[N],col,st[N],top;
map<pair<int,int>,bool> mp;
int in[N];
vector<pair<int,int>> v[N];
int ans[K];
int rt[N];
int n,m,q,seed;
int id(int x,int y){return m*(x-1)+y;}
bool isin(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
void add(int x,int y){to[++tot]=y,nex[tot]=h[x],h[x]=tot;}
void tj(int u){
  dfn[u]=low[u]=++num,st[++top]=u;
  for(int i=h[u];i;i=nex[i]){
    int v=to[i];
    if(!dfn[v]){
      tj(v);
      low[u]=min(low[u],low[v]);
    }
    else if(!sd[v])low[u]=min(low[u],dfn[v]);
  }
  if(low[u]==dfn[u]){
    col++;sd[u]=col;
    while(st[top]!=u)sd[st[top--]]=col;
    top--;
  }
}
//struct segtree{
//  #define mid (l+r>>1)
//  struct tree{
//    int ls,rs;
//    bool v;
//  }t[N*21];
//  int top;
//  int upd(int k,int l,int r,int x){
//    if(!k)k=++top;
//    if(l==r){t[k].v=1;return k;}
//    if(mid>=x)t[k].ls=upd(t[k].ls,l,mid,x);
//    else t[k].rs=upd(t[k].rs,mid+1,r,x);
//    return k;
//  }
//  int merge(int x,int y,int l,int r){
//    if(!x||!y)return x+y;
//    if(l==r)return x;
//    t[x].ls=merge(t[x].ls,t[y].ls,l,mid);
//    t[x].rs=merge(t[x].rs,t[y].rs,mid+1,r);
//  }
//  int qry(int k,int l,int r,int x){
//    if(!k)return 0;
//    if(l==r)return 1;
//    if(mid>=x)return qry(t[k].ls,l,mid,x);
//    else return qry(t[k].rs,mid+1,r,x);
//  }
//}T;
bitset<N>b[N];
void topo(){
  queue<int>q;
  for(int i=1;i<=col;i++)
    if(!in[i])q.push(i);
  while(!q.empty()){
    int u=q.front();q.pop();
    b[u][u]=1;
    for(auto j:v[u])
      ans[j.second]=b[u][j.first];
    for(int i=h[u];i;i=nex[i]){
      int v=to[i];
      in[v]--;
      b[v]|=b[u];
      if(!in[v])q.push(v);
    }
  }
}
signed main(){
  freopen("retribution.in","r",stdin);
  freopen("retribution.out","w",stdout);
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  cin>>n>>m>>q>>seed;
  init(seed);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
      char c;
      cin>>c;
      for(int k=0;k<4;k++){
        int x=i+d1[k],y=j+d2[k];
        if(!isin(x,y)||c==it[k])continue;
        add(id(i,j),id(x,y));
        e[++cnt]=(edge){id(i,j),id(x,y)};
      }
    }
  for(int i=1;i<=n*m;i++)if(!dfn[i])tj(i);
  memset(h,0,sizeof(h));tot=0;
  for(int i=1;i<=cnt;i++){
    if(sd[e[i].x]==sd[e[i].y]||mp[make_pair(sd[e[i].x],sd[e[i].y])])continue;
    add(sd[e[i].x],sd[e[i].y]);in[sd[e[i].y]]++;
  }
  for(int i=1,a,b,x,y;i<=q;i++){
    a=get(1,n),b=get(1,m),x=get(1,n),y=get(1,m);
    v[sd[id(x,y)]].push_back(make_pair(sd[id(a,b)],i));
  }
  topo();
  for(int i=1;i<=q;i++)cout<<ans[i];
  return 0;
}
