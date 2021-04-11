#include <cmath>
#include <cstdio>
using namespace std;
long long s1, s2, cha = 0, n, m, sbp, sb, ans, max, c[100001];
double num;
int main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &c[i]);
  }
  scanf("%d%d%lld%lld", &m, &sbp, &s1, &s2);
  c[sbp] = c[sbp] + s1;
  for (int i = 1; i <= n; i++) {
    cha = cha + c[i] * (m - i);
  }
  num = m + ((double)cha) / s2;
  if (num >= n) {
    ans = n;
  } else if (num <= 1) {
    ans = 1;
  } else {
    if ((int)num == num) {
      ans = (int)num;
    } else {
      long long ans1 = abs(cha + (m - (int)num) * s2);
      long long ans2 = abs(cha + (m - (int)num - 1) * s2);
      if (ans1 <= ans2) {
        ans = (int)num;
      } else {
        ans = (int)num + 1;
      }
    }
  }
  printf("%lld", ans);
  return 0;
}
/*
  cha+s2(m-num)=0
cha+s2*m-s2*num=0
       cha+s2*m=s2*num
	   cha/s2+m=num
	        num=m+cha/s2 
*/
