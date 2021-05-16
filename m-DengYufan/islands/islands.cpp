#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int h, a;
} v[100001];
int n, l[100001];

int main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
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
  }
  
  return 0;
}
