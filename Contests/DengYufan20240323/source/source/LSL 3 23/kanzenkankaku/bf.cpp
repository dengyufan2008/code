#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=3005,inf=1e9,B=1e4+7;
mt19937 rnd(time(0));
ull pw[N];
struct hash{
  ull hs[N];
  ull qry(int l,int r){return hs[r]-hs[l-1]*pw[r-l+1];}
}H1,H2;
int fbk[N];
int c[N];
int bukl[N],bukr[N];
bool ck[N][N];
int n,Z,ans;
void work1(int x,int y){
  int l=x,r=y,mx=inf,sm=0;
  while(l>=1&&r<=n&&c[l]==c[r])l--,r++;
  ans=max(ans,r-l-1);
  memset(bukl,0,sizeof(bukl));
  memset(bukr,0,sizeof(bukr));
  while(l>=1&&r<=n&&c[r]<=mx){
    mx=c[r];
    if(bukl[c[l]]==bukr[c[l]])sm++;
    if(bukl[c[r]]==bukr[c[r]])sm++;
    bukl[c[l]]++,bukr[c[r]]++;
    if(bukl[c[l]]==bukr[c[l]])sm--;
    if(bukl[c[r]]==bukr[c[r]])sm--;
    if(!sm)ck[l][r]=1;
    l--,r++;
  }
}
void work2(int x,int y){
  int l=x,r=y,mx=0,sm=0;
  while(l<=n&&r>=1&&c[l]==c[r])l++,r--;
  ans=max(ans,l-r-1);
  memset(bukl,0,sizeof(bukl));
  memset(bukr,0,sizeof(bukr));
  while(l<=n&&r>=1&&c[r]>=mx){
    mx=c[r];
    if(bukl[c[l]]==bukr[c[l]])sm++;
    if(bukl[c[r]]==bukr[c[r]])sm++;
    bukl[c[l]]++,bukr[c[r]]++;
    if(bukl[c[l]]==bukr[c[l]])sm--;
    if(bukl[c[r]]==bukr[c[r]])sm--;
    if(!sm)ck[r][l]=1;
    l++,r--;
  }
}
int find(int x,int y){
  int l=0,r=min(x,n-y+1),res=0;
  while(l<=r){
    int mid=(l+r)>>1;
    if(H1.qry(x-mid+1,x)==H2.qry(n-y-mid+1,n-y))res=mid,l=mid+1;
    else r=mid-1;
  }
  return res;
}
signed main(){
//  freopen("ex_kanzenkankaku4.in","r",stdin);
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  cin>>n>>Z;
  for(int i=1;i<=Z;i++)fbk[i]=rnd();
  for(int i=1;i<=n;i++)cin>>c[i];
  for(int i=1;i<=n;i++){
    int l=i-1,r=i,mx=inf,sm=0,mxl=0;
    memset(bukl,0,sizeof(bukl));
    memset(bukr,0,sizeof(bukr));
    while(l>=1&&r<=n&&c[r]<=mx){
      if(c[r]<mx&&bukl[c[r]]!=bukr[c[r]])sm++;
      mx=c[r];
      if(bukr[c[r]]==bukl[c[r]])sm++;
      bukr[c[r]]++;
      while(l>=1&&bukl[c[r]]<bukr[c[r]]){
        if(bukl[c[l]]==bukr[c[l]]&&c[l]>=mx)sm++;
        bukl[c[l]]++,mxl=max(mxl,c[l]),l--;
      }
      if(bukl[c[r]]==bukr[c[r]])sm--;
      int nl=i-(r-i+1+bukl[mxl])-1;
      if(!sm||(sm==1&&bukl[mxl]!=bukr[mxl])){
        ck[nl][r]=1;
        if(!sm&&c[l]==mxl)sm++;
        while(l>=1&&c[l]==mxl)bukl[c[l]]++,l--,nl=i-(r-i+1+bukl[mxl])-1,ck[nl][r]=1;
      }
      r++;
    }
  }
  for(int i=1;i<=n;i++){
    int r=i-1,l=i,mx=0,sm=0,mil=inf;
    memset(bukl,0,sizeof(bukl));
    memset(bukr,0,sizeof(bukr));
    while(l<=n&&r>=1&&c[r]>=mx){
      if(c[r]>mx&&bukl[c[r]]!=bukr[c[r]])sm++;
      mx=c[r];
      if(bukl[c[r]]==bukr[c[r]])sm++;
      bukr[c[r]]++;
      while(l<=n&&bukl[c[r]]<bukr[c[r]]){
        if(bukl[c[l]]==bukr[c[l]]&&c[l]<=mx)sm++;
        bukl[c[l]]++,mil=min(mil,c[l]),l++;
      }
      if(bukl[c[r]]==bukr[c[r]])sm--;
      int nl=i+(i-r+1+bukl[mil])-1;
      if(!sm||(sm==1&&bukl[mil]!=bukr[mil])){
        ck[r][nl]=1;
        if(!sm&&c[l]==mil)sm++;
        while(l<=n&&c[l]==mil)bukl[c[l]]++,l++,nl=i+(i-r+1+bukl[mil])-1,ck[r][nl]=1;
      }
      r--;
    }
  }
  for(int i=1;i<=n;i++)work1(i,i),work1(i-1,i);
  for(int i=1;i<=n;i++)work2(i,i),work2(i,i-1);
  for(int i=1;i<=n;i++)H1.hs[i]=1ull*H1.hs[i]*B+fbk[c[i]];
  for(int i=n;i>=1;i--)H2.hs[n-i+1]=1ull*H2.hs[n-i+1]*B+fbk[c[i]];
  for(int l=1;l<=n;l++)
    for(int r=l;r<=n;r++){
      if(!ck[l][r])continue;
      cout<<l<<' '<<r<<endl;
      ans=max(ans,r-l+1+find(l-1,r+1));
    }
  cout<<ans;
  return 0;
}
