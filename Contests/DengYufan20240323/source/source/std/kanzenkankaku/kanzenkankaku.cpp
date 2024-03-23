#include<bits/stdc++.h>
#define rep(i,a,b) for (register int i=(a);i<=(b);i++)
#define drep(i,a,b) for (register int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;

#define fir first
#define sec second
void chkmax(auto &x,auto y){x=(x>y)?x:y;}

const int N=3010;

int n,lcp[N][N],a[N],m,ans;

int cnt[N];

int solve(int L,int R,int v)
{
	static int cntl[N],cntr[N];
	memset(cntl,0,sizeof(cntl)),memset(cntr,0,sizeof(cntr));
	
	vector<pair<int,int> > vec;
	drep(i,L,1)
	{
		cntl[a[i]]++;
		vec.push_back(make_pair(a[i],cntl[a[i]]));
		if (a[i]>a[i-1]) break;
	}
	
	int match=0,invalid=vec.size(),cc=0,ans=0;
	rep(i,R,n)
	{
		if (a[i]<v) break;
		if (a[i]==v) cc++;
		else
		{
			cntr[a[i]]++;
			if (cntr[a[i]]<=cntl[a[i]]) while (match<vec.size()&&vec[match].sec<=cntr[vec[match].fir]) match++;
			else while (invalid&&a[i]<vec[invalid-1].fir) invalid--;
		}
		int ok=min(match,invalid);
		chkmax(ans,cc+2*ok);
		if (i-R+1==cc+ok) chkmax(ans,cc+2*ok+2*lcp[L-ok][i+1]);
	}
	
	return ans;
}

void work()
{
	rep(i,1,m) cnt[i]=0;
	rep(i,1,n) cnt[a[i]]++;
	rep(i,1,m) chkmax(ans,cnt[i]);
	
	rep(i,1,n) drep(j,n,i) lcp[i][j]=(a[i]==a[j])?lcp[i-1][j+1]+1:0;
	
	rep(i,1,n)
	{
		int d=lcp[i][i];
		chkmax(ans,2*d-1+solve(i-d,i+d,-1));
	}
	rep(i,1,n-1)
	{
		int d=lcp[i][i+1];
		chkmax(ans,2*d+solve(i-d,i+1+d,-1));
	}
	rep(i,1,n)
	{
		int id=0;
		rep(j,i+1,n) if (a[j]<a[i])
		{
			id=j;
			break;
		}
		if (id) chkmax(ans,solve(i,i+1,a[id]));
	}
}

int main()
{
  freopen("kanzenkankaku.in", "r", stdin);
  freopen("kanzenkankaku.out", "w", stdout); 
	ios::sync_with_stdio(false); cin.tie(0);
	
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	
	work();
	reverse(a+1,a+n+1);
	rep(i,1,n) a[i]=m-a[i]+1; 
	work();
	
	cout<<ans<<endl;
	
	return 0;
}
