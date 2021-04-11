#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int h, t;
} v[200001];

int n, m, mx;
string s, t;

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> n >> m >> s >> t;
  for (int i = 0, j = 0; i < n && j < m; i++) {
    if (s[i] == t[j]) {
      v[j++].h = i;
    }
  }
  for (int i = n - 1, j = m - 1; i >= 0 && j >= 0; i--) {
    if (s[i] == t[j]) {
      v[j--].t = i;
    }
  }
  for (int i = 1; i < m; i++) {
    mx = max(mx, v[i].t - v[i - 1].h);
  }
  cout << mx;
  return 0;
}
