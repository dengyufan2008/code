#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct V {
  int a, b;
  bool operator<(const V &v) const {
    return a < v.a || a == v.a && b < v.b;
  }
} v[50001];
int n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].a >> v[i].b;
  }
  sort(v + 1, v + n + 1);
  v[0] = v[1];
  for (int i = 2; i <= n; i++) {
    if (v[0].b < v[i].a) {
      cout << "no" << endl;
      return 0;
    }
    v[0].a = min(v[0].a, v[i].a), v[0].b = max(v[0].b, v[i].b);
  }
  cout << v[0].a << " " << v[0].b << endl;
  return 0;
}
