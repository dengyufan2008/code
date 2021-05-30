#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL a, b;
} v[200001];
LL n, k;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].a >> v[i].b;
  }
  v[n + 1] = {(LL)1e20 + 1, 0};
  sort(v + 1, v + n + 1, [](A i, A j) {
    return i.a < j.a;
  });
  for (LL i = 1, p = 0; i <= n + 1; i++) {
    if (k < v[i].a - p) {
      cout << p + k << endl;
      return 0;
    }
    k += p - v[i].a + v[i].b;
    p = v[i].a;
  }
  return 0;
}
