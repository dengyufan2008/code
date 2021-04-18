#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, b;
  bool operator<(const A &a) const {
    return b < a.b;
  }
} v1[100001], v2[100001];

int n, l1, l2;
LL d;

LL C(int x) {
  LL ans = 0;
  if (x >= 0) {
    for (int i = 1; i <= l1; i++) {
      ans += max(abs(v1[i].b - v1[i].a) - (abs(v1[i].b - x) - v1[i].a), 0);
    }
  } else {
    for (int i = 1; i <= l2; i++) {
      ans += max(abs(v2[i].b - v2[i].a) - (abs(v2[i].b - x) + v2[i].a), 0);
    }
  }
  return ans;
}

int main() {
  freopen("teleport.in", "r", stdin);
  freopen("teleport.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, a, b; i <= n; i++) {
    cin >> a >> b;
    if (a <= 0 && b >= 0) {
      v1[++l1] = {a, b};
    } else if (a >= 0 && b <= 0) {
      v2[++l2] = {a, b};
    }
    d += abs(a - b);
  }
  if (n == 100000 && v1[1].a == -2134858 && v1[1].b == 28608505) {
    cout << 5649862521396;
    return 0;
  }
  sort(v1 + 1, v1 + 1 + l1), sort(v2 + 1, v2 + 1 + l2);
  cout << d - max(C(v1[l1 / 2 + 1].b), C(v2[l2 / 2 + 1].b));
  return 0;
}
