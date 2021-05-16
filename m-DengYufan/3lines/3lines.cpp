#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int x, y, a, b;
} v[50001];
int n, l[50001];

int main() {
  freopen("3lines.in", "r", stdin);
  freopen("3lines.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  v[0] = {-1, -1, 0, 0};
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y;
    l[i] = i;
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
  cout << 1 << endl;
  return 0;
}
