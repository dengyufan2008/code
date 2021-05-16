#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int h, a;
} v[101];
int n, a, ans, l[101];

int main() {
  // freopen("islands.in", "r", stdin);
  // freopen("islands.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].h;
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return v[i].h < v[j].h;
  });
  for (int i = 1; i <= n; i++) {
    v[l[i]].a = v[l[i - 1]].a + (v[l[i]].h != v[l[i - 1]].h);
    a = max(a, v[l[i]].a);
  }
  for (int i = 1, num; i <= a; i++) {
    num = 0;
    for (int j = 1; j <= n; j++) {
      if (v[j].a > i && v[j - 1].a <= i) {
        num++;
      }
    }
    ans = max(ans, num);
    num = 0;
    for (int j = 1; j <= n; j++) {
      if (v[j].a >= i && v[j - 1].a < i) {
        num++;
      }
    }
    ans = max(ans, num);
  }
  cout << ans << endl;
  return 0;
}
