#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int k, s;
} e[5001];

int n, m;

bool P(A a, A b) {
  return a.s > b.s || a.s == b.s && a.k < b.k;
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].k >> e[i].s;
  }
  m *= 1.5;
  sort(e + 1, e + 1 + n, P);
  for (; e[m].s == e[m + 1].s; m++)
    ;
  cout << e[m].s << " " << m << "\n";
  for (int i = 1; i <= m; i++) {
    cout << e[i].k << " " << e[i].s << "\n";
  }
  return 0;
}
