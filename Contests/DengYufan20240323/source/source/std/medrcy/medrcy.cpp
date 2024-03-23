#include<bits/stdc++.h>
using namespace std;
const int inf=0x7f7f7f7f;
int ceilDiv(int x,int y)
{
	return (x+y-1)/y;
}
int n,m,k;
vector<int> t[1100];
int deg[1100];
bool chs[1100];
int vis[1100];
int mnc;
bool can[1100];
void clear()
{
	for(int i=0;i<=n+10;i++)
	{
		t[i].clear();
		deg[i]=chs[i]=vis[i]=can[i]=0;
	}
	n=m=k=mnc=0;
}
void getComponent(int u,vector<int> &p,int gid)
{
	vis[u]=gid,p.push_back(u);
	for(int i=0;i<t[u].size();i++)
	{
		int v=t[u][i];
		if(!chs[v]&&vis[v]!=gid)
			getComponent(v,p,gid);
	}
}
void solveComponent(int rt)
{
	vector<int> p(0);
	getComponent(rt,p,1);
	int h=0,mxd=0;
	for(int u:p)
	{
		mxd=max<int>(mxd,deg[u]);
		if(deg[u]==1)
			h=u;
	}
	if(mxd==0)
		return;
	if(!h)
	{
		for(int u:p)
			can[u]=1;
		return;
	}
	p=vector<int>(0);
	getComponent(h,p,2);
	if(p.size()%2==1)
	{
		for(int i=1;i<p.size();i+=2)
			can[p[i]]=1;
	}
	if(p.size()%2==0)
	{
		for(int i=0;i<p.size();i+=1)
			can[p[i]]=1;
	}
}
void dfs()
{
	int p=max_element(deg+1,deg+n+1)-deg,cnt=accumulate(chs+1,chs+n+1,0);
	if(cnt>mnc||cnt>k)
		return;
	if(deg[p]<=2)
	{
		int rcnt=cnt;
		fill(vis+1,vis+n+1,0);
		for(int i=1;i<=n;i++)
		{
			if(!chs[i]&&vis[i]==0)
			{
				vector<int> p(0);
				getComponent(i,p,1);
				int edg=0;
				for(int u:p)
					edg+=deg[u];
				assert(edg%2==0);
				rcnt+=ceilDiv(edg/2,2);
			}
		}
		if(rcnt<mnc&&rcnt<=k)
		{
			mnc=rcnt;
			fill(can+1,can+n+1,0);
		}
		if(rcnt==mnc)
		{
			for(int i=1;i<=n;i++)
				can[i]|=chs[i];
			fill(vis+1,vis+n+1,0);
			for(int i=1;i<=n;i++)
			{
				if(!chs[i]&&vis[i]==0)
					solveComponent(i);
			}
		}
		return;
	}
	if(cnt>=mnc||cnt>=k)
		return;
	function<void(int,int)> choosePoint=[&](int u,int x)
	{
		for(int i=0;i<t[u].size();i++)
		{
			int v=t[u][i];
			deg[u]-=(!chs[u]&&!chs[v]),deg[v]-=(!chs[u]&&!chs[v]);
			deg[u]+=(!x&&!chs[v]),deg[v]+=(!x&&!chs[v]);
		}
		chs[u]=x;
	};
	// not choose p
	vector<int> q(0);
	for(int i=0;i<t[p].size();i++)
	{
		int v=t[p][i];
		if(!chs[v])
		{
			q.push_back(v);
			choosePoint(v,1);
		}
	}
	dfs();
	for(int v:q)
		choosePoint(v,0);
	// choose p
	choosePoint(p,1);
	dfs();
	choosePoint(p,0);
}
bool checkTree()
{
	if(m!=n-1)
		return 0;
	fill(vis+1,vis+n+1,0);
	vector<int> p(0);
	getComponent(1,p,1);
	fill(vis+1,vis+n+1,0);
	if(p.size()!=n)
		return 0;
	return 1;
}
int main()
{
    freopen("medrcy.in", "r", stdin);
  freopen("medrcy.out", "w", stdout); 
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	for(int _=1;_<=T;_++)
	{
		cin>>n>>m>>k;
		// assert(k<=3);
		set<pair<int,int>> edg={};
		for(int i=1;i<=m;i++)
		{
			int a,b;
			cin>>a>>b;
			if(a>b)
				swap(a,b);
			if(edg.count(make_pair(a,b)))
				continue;
			edg.insert(make_pair(a,b));
			t[a].push_back(b);
			t[b].push_back(a);
			deg[a]++,deg[b]++;
		}
		// assert(checkTree());
		mnc=inf;
		dfs();
		if(mnc==inf)
		{
			cout<<-1<<'\n';
		}
		else
		{
			cout<<mnc<<" "<<accumulate(can+1,can+n+1,0)<<'\n';
			for(int i=1;i<=n;i++)
			{
				if(can[i])
					cout<<i<<" ";
			}
			cout<<'\n';
		}
		cout<<flush;
		clear();
	}
}
