#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int r, c;
  bool operator<(const A &a) const {
    return c < a.c;
  }
} v[200001];

int t, n, m;

void M(void) {
  int k = 0;
  for (int i = 1; i <= m; i++) {
    if (v[i].c != v[k].c) {
      v[++k] = v[i];
    } else {
      v[k].r |= v[i].r;  //标记结束或不变
    }
  }
  m = k;  //之后的部分不用判断
}

bool C(void) {
  bool ans = true;
  for (int i = 1, s = 3; i <= m; i++) {
    if (s == 3) {
      s = v[i].r;
    } else {
      ans &= v[i].r != 3 && (v[i].r != s) ^ ((v[i].c - v[i - 1].c) & 1);
      s = 3;
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
      cin >> v[i].r >> v[i].c;
    }
    v[++m] = {3, n + 1};
    sort(v + 1, v + m + 1);
    M();
    cout << (C() ? "YES" : "NO") << endl;
  }
  return 0;
}
