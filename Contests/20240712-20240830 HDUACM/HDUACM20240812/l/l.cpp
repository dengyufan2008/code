// by lsl
#include <bits/stdc++.h>
using namespace std;
const int N = (1 << 3) + 5, M = 2e5 + 10;
int buk[N];
char s1[M], s2[M], s3[M];
int n, TE, ans;
void work() {
  memset(buk, 0, sizeof(buk));
  ans = 0;
  cin >> n;
  cin >> s1 >> s2 >> s3;
  for (int i = 0; i < n; i++) buk[(s1[i] - '0') + ((s2[i] - '0') << 1) + ((s3[i] - '0') << 2)]++;
  for (int i = 0; i < 8; i++)
    if (__builtin_popcount(i) <= 1) buk[i ^ 7] += buk[i];
  int l = 0, r = n, ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1, sum1 = buk[3] + buk[5], sum2 = buk[6] + buk[3], sum3 = buk[6] + buk[5], fl = 1;
    if (sum1 < mid) sum2 += sum1 - mid, sum3 += sum1 - mid, sum1 = mid;
    if (sum2 < mid) sum1 += sum2 - mid, sum3 += sum2 - mid, sum2 = mid;
    if (sum3 < mid) sum1 += sum3 - mid, sum2 += sum3 - mid, sum3 = mid;
    fl &= (sum1 >= mid && sum2 >= mid && sum3 >= mid);
    if (fl)
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  cout << ans + buk[7] << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> TE;
  while (TE--) work();
  return 0;
}
