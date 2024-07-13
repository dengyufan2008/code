#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, m, a[200001];

void Find(LL x) {
  LL ans = 0;
  for (LL i = 1 << 20; i; i >>= 1) {  //倍增比二分好写[doge]
    if (ans + i <= n && a[ans + i] < x) {
      ans += i;
    }
  }
  cout << ans + 1 << " " << x - a[ans] << endl;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (LL i = 1, tmp; i <= n; i++) {
    cin >> tmp;
    a[i] = a[i - 1] + tmp;
  }
  for (LL i = 1, tmp; i <= m; i++) {
    cin >> tmp;
    Find(tmp);
  }
  return 0;
}
