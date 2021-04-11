#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int c, t, n;
} v[301];

int n;

bool P(A a, A b) {
  return a.t > b.t || a.t == b.t && a.c > b.c ||
         a.t == b.t && a.c == b.c && a.n < b.n;
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1, m, e; i <= n; i++) {
    cin >> v[i].c >> m >> e;
    v[i].t = v[i].c + m + e;
    v[i].n = i;
  }
  sort(v + 1, v + 1 + n, P);
  for (int i = 1; i <= 5; i++) {
    cout << v[i].n << " " << v[i].t << "\n";
  }
  return 0;
}
