/*
ID: dengyuf1
TASK: ariprog
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, b;
  bool operator<(const A &x) const {
    return b < x.b || b == x.b && a < x.a;
  }
} v[10001];
int n, m, k, _k, a[100001];
bool b[125001];

bool C(int x, int y) {
  int d = y - x;
  if (x + (n - 1) * d > m * m * 2) {
    return false;
  }
  for (int i = 2; i < n; i++) {
    if (!b[x + i * d]) {
      return false;
    }
  }
  return true;
}

int main() {
  freopen("ariprog.in", "r", stdin);
  freopen("ariprog.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= m; j++) {
      if (!b[i * i + j * j]) {
        a[++_k] = i * i + j * j;
        b[i * i + j * j] = true;
      }
    }
  }
  sort(a + 1, a + _k + 1);
  for (int i = 1; i <= _k; i++) {
    for (int j = i + 1; j <= _k; j++) {
      if (C(a[i], a[j])) {
        v[++k] = {a[i], a[j] - a[i]};
      }
    }
  }
  sort(v + 1, v + k + 1);
  for (int i = 1; i <= k; i++) {
    cout << v[i].a << " " << v[i].b << endl;
  }
  if (!k) {
    cout << "NONE" << endl;
  }
  return 0;
}
