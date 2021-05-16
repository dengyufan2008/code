#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int x, y, a, b;
} v[51];
int n, l[51];

int main() {
  // freopen("3lines.in", "r", stdin);
  // freopen("3lines.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return v[i].x < v[j].x;
  });
  for (int i = 1; i <= n; i++) {
    v[l[i]].a = v[l[i - 1]].a + (v[l[i]].x != v[l[i - 1]].x);
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return v[i].y < v[j].y;
  });
  for (int i = 1; i <= n; i++) {
    v[l[i]].b = v[l[i - 1]].b + (v[l[i]].y != v[l[i - 1]].y);
  }
  for (int i = 1; i <= n; i++) {
    cout << v[i].a << " " << v[i].b << endl;
  }
  return 0;
}
