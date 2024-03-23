#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
    int len=0;
    char ibuf[(1<<21)+1],*iS,*iT,out[(1<<25)+1];
    #if ONLINE_JUDGE
    #define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<21)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
    #else
    #define gh() getchar()
    #endif
    #define reg register
    inline int read(){
        reg char ch=gh();
        reg int x=0;
        reg char t=0;
        while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
        while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
        return t?-x:x;
    }
    inline void putc(char ch){
        out[len++]=ch;
    }
    template<class T>
    inline void write(T x){
        if(x<0)putc('-'),x=-x;
        if(x>9)write(x/10);
        out[len++]=x%10+48;
    }
    inline void flush(){
        fwrite(out,1,len,stdout);
        len=0;
    }
    inline char getc(){
        char ch=gh();
        while(ch<'A'||ch>'Z') ch=gh();
        return ch;
    }
}
using IO::read;
using IO::write;
using IO::flush;
using IO::getc;
using IO::putc;
#define mpr make_pair
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
const int N=1.8e3+10,Q=1e6+10,INF=1e9;
struct Point{
    int x,y;
    inline void cng(int m){
        int t=x;
        x=m-y+1,y=t;
    }
    Point(int xa=0,int ya=0){ x=xa,y=ya; }
    inline friend bool operator<=(const Point &a,const Point &b){
        return a.x<=b.x&&a.y<=b.y;
    }
};
struct Query{
    Point a,b;
}qr[Q];
int n,m,q,tr[256],to[5];
short a[N][N],b[N][N];
bool ans[Q],vis[Q];
inline void alinit(){
    tr['U']=1,tr['R']=2,tr['D']=3,tr['L']=4;
    to[1]=4,to[2]=1,to[3]=2,to[4]=3;
}
inline void turn(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            b[m+1-j][i]=to[a[i][j]];
    for(int i=1;i<=q;i++)
        qr[i].a.cng(m),qr[i].b.cng(m);
    swap(n,m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j]=b[i][j];
} 
short lu[N][N],ul[N][N],ur[N][N],dr[N][N],ld[N][N],rd[N][N];
short Frd[N][N][12],Fdr[N][N][12],lg[N],f1[N][N],f2[N][N];
bool col[N][N];
inline int queryrd(int j,int l,int r){
    int t=lg[r-l+1];
    return max(Frd[l][j][t],Frd[r-(1<<t)+1][j][t]);
}
inline int querydr(int i,int l,int r){
    int t=lg[r-l+1];
    return max(Fdr[i][l][t],Fdr[i][r-(1<<t)+1][t]);
}
inline int findD(int j,int L,int R,int len){
    int ans=-1;
    while(L<=R){
        int mid=L+R>>1;
        if(queryrd(j,L,mid)>=len) ans=mid,R=mid-1;
        else L=mid+1;
    }
    return ans;
}
inline int findR(int i,int L,int R,int len){
    int ans=-1;
    while(L<=R){
        int mid=L+R>>1;
        if(querydr(i,L,mid)>=len) ans=mid,R=mid-1;
        else L=mid+1;
    }
    return ans;
}
struct Matrix{
    Point a,b;
};
inline int find1(int i,int j){
    while(i!=f1[i][j]) i=f1[i][j]=f1[f1[i][j]][j];
    return i;
}
inline int find2(int i,int j){
    while(j!=f2[i][j]) j=f2[i][j]=f2[i][f2[i][j]];
    return j;
}
inline void cover(int i,int x1,int y1,int x2,int y2){
    if(y2-y1<x2-x1){
        for(int y=y1;y<=y2;y++)
            for(int x=find1(x1,y);x<=x2;x=find1(x+1,y))
                col[x][y]=0,f1[x][y]=x+1;
    }else{
        for(int x=x1;x<=x2;x++)
            for(int y=find2(x,y1);y<=y2;y=find2(x,y+1))
                col[x][y]=0,f2[x][y]=y+1;
    }
}
struct QR{
    Point a,b;
    int ind;
};
vector<Matrix>mtx[N],mty[N];
vector<QR>qrx[N],qry[N];
inline void solve(){
    for(int i=0;i<=n+1;i++) 
        for(int j=0;j<=m+1;j++)
            lu[i][j]=ur[i][j]=ld[i][j]=ul[i][j]=
            dr[i][j]=rd[i][j]=0;
    for(int i=1;i<=n;i++){
        vector<QR>t1;
        vector<Matrix>t2;
        swap(qrx[i],t1),swap(mtx[i],t2);
    }
    for(int j=1;j<=m;j++){
        vector<QR>t1;
        vector<Matrix>t2;
        swap(qry[j],t1),swap(mty[j],t2);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            lu[i][j]=a[i][j]==1?lu[i][j-1]+1:0,
            ur[i][j]=a[i][j]==2?ur[i-1][j]+1:0,
            ld[i][j]=a[i][j]==3?ld[i][j-1]+1:0,
            ul[i][j]=a[i][j]==4?ul[i-1][j]+1:0;
    for(int i=n;i>=1;i--)
        for(int j=m;j>=1;j--)
            dr[i][j]=a[i][j]==2?dr[i+1][j]+1:0,
            rd[i][j]=a[i][j]==3?rd[i][j+1]+1:0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            Frd[i][j][0]=rd[i][j+1],
            Fdr[i][j][0]=dr[i+1][j];
    for(int k=1;k<=lg[n];k++)
        for(int j=1;j<=m;j++)
            for(int i=1;i+(1<<k)-1<=n;i++)
                Frd[i][j][k]=max(Frd[i][j][k-1],Frd[i+(1<<k-1)][j][k-1]);
    for(int k=1;k<=lg[m];k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j+(1<<k)-1<=m;j++)
                Fdr[i][j][k]=max(Fdr[i][j][k-1],Fdr[i][j+(1<<k-1)][k-1]);
    int cnt=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(!lu[i][j-1]||!ul[i-1][j]) continue;
            if(lu[i][j-1]<ul[i-1][j]){
                for(int yl=j-lu[i][j-1]-1;yl<j-1;yl++){
                    int xl=findD(yl,i-min(ul[i-1][j],ur[i-1][yl])-1,i-2,j-yl-1);
                    if(xl==-1) continue;
                    if(!(Point(xl+1,yl+1)<=Point(i-1,j-1))) continue;
                    Matrix tmp={Point(xl+1,yl+1),Point(i-1,j-1)};
                    mtx[i-1].push_back(tmp),mty[j-1].push_back(tmp);
                    cnt++;
                    break;
                }
            }else{
                for(int xl=i-ul[i-1][j]-1;xl<i-1;xl++){
                    int yl=findR(xl,j-min(lu[i][j-1],ld[xl][j-1])-1,j-2,i-xl-1);
                    if(yl==-1) continue;
                    if(!(Point(xl+1,yl+1)<=Point(i-1,j-1))) continue;
                    Matrix tmp={Point(xl+1,yl+1),Point(i-1,j-1)};
                    mtx[i-1].push_back(tmp),mty[j-1].push_back(tmp);
                    cnt++;
                    break;
                }
            }
        }
    for(int i=1;i<=q;i++)
        if(qr[i].a<=qr[i].b&&!vis[i]){
            QR tmp={qr[i].a,qr[i].b,i};
            qrx[qr[i].b.x].push_back(tmp);
            qry[qr[i].b.y].push_back(tmp);
            vis[i]=1;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            col[i][j]=1,f1[i][j]=i,f2[i][j]=j;
    for(int i=1,tim=0;i<=n;i++){
        for(auto qrc:qrx[i])
            ans[qrc.ind]=col[qrc.a.x][qrc.a.y];
        for(auto mt:mtx[i])
            cover(++tim,mt.a.x,mt.a.y,mt.b.x,mt.b.y);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            col[i][j]=1,f1[i][j]=i,f2[i][j]=j;
    for(int i=1,tim=0;i<=m;i++){
        for(auto qrc:qry[i])
            ans[qrc.ind]&=col[qrc.a.x][qrc.a.y];
        for(auto mt:mty[i])
            cover(++tim,mt.a.x,mt.a.y,mt.b.x,mt.b.y);
    }
}
int main(){
      freopen("retribution.in", "r", stdin);
  freopen("retribution.out", "w", stdout); 
    alinit();
    n=read(),m=read(),q=read();
    init(read());
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i+1][j+1]=tr[getc()];
    for(int i=1;i<=q;i++){
        int a=get(1,n)+1,b=get(1,m)+1,x=get(1,n)+1,y=get(1,m)+1;
        qr[i]={Point(x,y),Point(a,b)};
        if(a==x&&b==y) vis[i]=ans[i]=1;
    }
    n+=2,m+=2;
    for(int i=2;i<m;i++)
        a[1][i]=tr['D'],a[n][i]=tr['U'];
    for(int i=2;i<n;i++)
        a[i][1]=tr['R'],a[i][m]=tr['L'];
    for(int i=2;i<=max(n,m);i++)
        lg[i]=lg[i/2]+1;
    solve();
    turn();
    solve();
    turn();
    solve();
    turn();
    solve();
    for(int i=1;i<=q;i++)
        write(ans[i]); 
    flush();
}
