#include<bits/stdc++.h>
using namespace std;
const int N=3005,inf=1e9,B=1e4+7;
int c[N];
int b[N],g[N];
int p[N<<1],nex[N<<1];
int n,Z,m,ans;
void solve(){
  m=0;
  p[++m]='#';
  for(int i=1;i<=n;i++)p[++m]=b[i],p[++m]='#';
  for(int i=1;i<=m;i++)nex[i]=0;
  nex[1]=1;
  for(int i=2,k=1;i<=m;i++){
    int s=i+nex[2*k-i]-1;
    if(k+nex[k]-1<=s){
      int l=k+nex[k];
      while(2*i-l>=1&&l<=m&&p[2*i-l]==p[l])l++;
      nex[i]=l-i;k=i;
    }
    else nex[i]=nex[2*k-i];
    ans=max(ans,(2*nex[i]-1)/2);
  }
}
signed main(){
  freopen("kanzenkankaku.in","r",stdin);
  freopen("kanzenkankaku.out","w",stdout);
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  cin>>n>>Z;
  for(int i=1;i<=n;i++)cin>>c[i];
  for(int i=1;i<=n;i++)
    for(int j=i;j<=n;j++){
      for(int k=1;k<=n;k++)b[k]=c[k];
      for(int k=i;k<=j;k++)g[c[k]]++;
      for(int k=1,cnt=0;k<=Z;k++){
        for(int l=1;l<=g[k];l++)cnt++,b[i+cnt-1]=k;
        g[k]=0;
      }
      solve();
    }
  cout<<ans;
  return 0;
}
