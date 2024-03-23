#include<bits/stdc++.h>
using namespace std;
int n,c,ans;
int a[3005];
bool dp[3005][3005];
int s1[3005],s2[3005],sum=0;
void soll(int x){
	int l=x,minn=c+1,f=0;sum=0;
	for(int i=1;i<=c;++i)s1[i]=s2[i]=0;
	for(int i=x;i<=n;++i){
		minn=min(minn,a[i]);++s2[a[i]];
		if(s2[a[i]]==s1[a[i]])--sum;
		if(s2[a[i]]==s1[a[i]]+1)++sum;
		if(s2[minn]==s1[minn])f=0;
		else f=1;
		while(x-l<i-x+1-s2[minn]+s1[minn]){
			--l;if(!l||(l!=x-1&&a[l]<a[l+1]))return;
			++s1[a[l]];
			if(s1[a[l]]==s2[a[l]])--sum;
			if(s1[a[l]]==s2[a[l]]+1)++sum;
			if(s2[minn]==s1[minn])f=0;
			else f=1;
		}
		if(sum==f)dp[l][i]=1;
	}
}
void solr(int x){
	int r=x,minn=c+1,f=0;sum=0;
	for(int i=1;i<=c;++i)s1[i]=s2[i]=0;
	for(int i=x;i;--i){
		minn=min(minn,a[i]);++s2[a[i]];
		if(s2[a[i]]==s1[a[i]])--sum;
		if(s2[a[i]]==s1[a[i]]+1)++sum;
		if(s2[minn]==s1[minn])f=0;
		else f=1;
		while(r-x<x-i+1-s2[minn]+s1[minn]){
			++r;if(r>n||(r!=x+1&&a[r]>a[r-1]))return;
			++s1[a[r]];
			if(s1[a[r]]==s2[a[r]])--sum;
			if(s1[a[r]]==s2[a[r]]+1)++sum;
			if(s2[minn]==s1[minn])f=0;
			else f=1;
		}
		if(sum==f)dp[i][r]=1;
	}
}
void sl(int L,int R){
	int l=L,r=R;
	while(l>=1&&r<=n){
		++s1[a[l]];
		if(s1[a[l]]==s2[a[l]]+1)++sum;
		if(s1[a[l]]==s2[a[l]])--sum;
		++s2[a[r]];
		if(s1[a[r]]==s2[a[r]]-1)++sum;
		if(s1[a[r]]==s2[a[r]])--sum;
		if(r!=R&&a[r]>a[r-1]){
			for(int i=l;i<=L;++i)s1[a[i]]=0;
			for(int i=R;i<=r;++i)s2[a[i]]=0;
			sum=0;
			return;
		}
		if(!sum){
			dp[l][r]=1;
			for(int i=l;i<=L;++i)s1[a[i]]=0;
			for(int i=R;i<=r;++i)s2[a[i]]=0;
			sum=0;
			return;
		}
		--l;++r;
		if(dp[l][r])break;
	}
	for(int i=l;i<=L;++i)s1[a[i]]=0;
	for(int i=R;i<=r;++i)s2[a[i]]=0;
	sum=0;
	return;
}
void sr(int L,int R){
	int l=L,r=R;
	while(l>=1&&r<=n){
		++s1[a[l]];
		if(s1[a[l]]==s2[a[l]]+1)++sum;
		if(s1[a[l]]==s2[a[l]])--sum;
		++s2[a[r]];
		if(s1[a[r]]==s2[a[r]]-1)++sum;
		if(s1[a[r]]==s2[a[r]])--sum;
		if(l!=L&&a[l]<a[l+1]){
			for(int i=l;i<=L;++i)s1[a[i]]=0;
			for(int i=R;i<=r;++i)s2[a[i]]=0;
			sum=0;
			return;
		}
		if(sum==0){
			dp[l][r]=1;
			for(int i=l;i<=L;++i)s1[a[i]]=0;
			for(int i=R;i<=r;++i)s2[a[i]]=0;
			sum=0;
			return;
		}
		--l;++r;
		if(dp[l][r])break;
	}
	for(int i=l;i<=L;++i)s1[a[i]]=0;
	for(int i=R;i<=r;++i)s2[a[i]]=0;
	sum=0;
	return;
}
signed main(){
	freopen("kanzenkankaku.in","r",stdin);
	freopen("kanzenkankaku.out","w",stdout);
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),dp[i][i-1]=1;
	for(int i=1;i<=n;++i){
		soll(i);solr(i);
	}
	for(int i=1;i<=c;++i)s1[i]=s2[i]=0;sum=0;
	for(int len=0;len<=n;++len){
		for(int i=1;i+len-1<=n;++i){
			if(!dp[i][i+len-1])continue;
			ans=max(ans,len);
			sl(i-1,i+len);sr(i-1,i+len);
		}
	}
	printf("%d",ans);
	return 0;
}
