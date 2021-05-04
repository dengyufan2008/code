/*
ID: dengyuf1
TASK: wormhole
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, f[15], nt[15], x[15], y[15];

bool C() {
  int u;
  for (int i = 1; i <= n; i++) {
    u = i;
    for (int j = 1; j <= n; j++) {
      u = nt[f[u]];
    }
    if (u) {
      return true;
    }
  }
  return false;
}

int S(int s) {
  int x, ans = 0;
  if (s == n / 2) {
    return C();
  }
  for (x = 1; x <= n; x++) {
    if (!f[x]) {
      break;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (i != x && !f[i]) {
      f[x] = i, f[i] = x;
      ans += S(s + 1);
      f[x] = 0, f[i] = 0;
    }
  }
  return ans;
}

int main() {
  freopen("wormhole.in", "r", stdin);
  freopen("wormhole.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j && y[i] == y[j] && x[j] > x[i] && (!nt[i] || x[nt[i]] > x[j])) {
        nt[i] = j;
      }
    }
  }
  cout << S(0) << endl;
  return 0;
}
