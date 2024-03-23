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
int n,m,q,seed;
int id(int x,int y){
	return (x-1)*m+y;
}
struct Edge{
	int nxt,to;
}edge[800005];
int head[4000005],tot;
void add(int x,int y){edge[++tot].nxt=head[x];edge[tot].to=y;head[x]=tot;}
int dfn[4000005],low[4000005],T,in[4000005];
stack<int>s;
int d[4000005],st;
void dfs(int x){
	low[x]=dfn[x]=++T;s.push(x);in[x]=1;
	for(int i=head[x];i;i=edge[i].nxt){
		if(!dfn[edge[i].to]){
			dfs(edge[i].to);low[x]=min(low[x],low[edge[i].to]);
		}else if(in[edge[i].to])low[x]=min(low[x],dfn[edge[i].to]);
	}
	if(low[x]==dfn[x]){
		++st;
		while(low[s.top()]!=dfn[s.top()]){
			int t=s.top();s.pop();in[t]=0;
			d[t]=st;
		}
		int t=s.top();s.pop();in[t]=0;
		d[t]=st;
	}
	return;
}
char C[1805][1805];
void add2(int x,int y){
	if(d[x]==d[y])return;
	add(d[x],d[y]);
}
bool f[4000005];
int bfs(int x,int y){
	x=d[x];y=d[y];
	if(x==y)return 1;
	for(int i=1;i<=st;++i)f[i]=0;
	queue<int>q;
	q.push(x);
	while(!q.empty()){
		int X=q.front();q.pop();
		for(int i=head[X];i;i=edge[i].nxt){
			if(!f[edge[i].to]){
				f[edge[i].to]=1;q.push(edge[i].to);
				if(edge[i].to==y)return 1;
			}
		}
	}
	return 0;
}
signed main(){
	freopen("retribution.in","r",stdin);
	freopen("retribution.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&q,&seed);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>C[i][j];char c=C[i][j];
			if(i!=1&&c!='U')add(id(i,j),id(i-1,j));
			if(i!=n&&c!='D')add(id(i,j),id(i+1,j));
			if(j!=1&&c!='L')add(id(i,j),id(i,j-1));
			if(j!=m&&c!='R')add(id(i,j),id(i,j+1));
		}
	for(int i=1;i<=id(n,m);++i)if(!dfn[i])dfs(i);tot=0;memset(head,0,sizeof(head));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			char c=C[i][j];
			if(i!=1&&c!='U')add2(id(i,j),id(i-1,j));
			if(i!=n&&c!='D')add2(id(i,j),id(i+1,j));
			if(j!=1&&c!='L')add2(id(i,j),id(i,j-1));
			if(j!=m&&c!='R')add2(id(i,j),id(i,j+1));
		}
	init(seed);
	while(q--){
		int a=get(1,n),b=get(1,m),x=get(1,n),y=get(1,m);
		printf("%d",bfs(id(a,b),id(x,y)));
	}
	return 0;
}
