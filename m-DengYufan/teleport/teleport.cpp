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

LL C(int x) {  //以x点为传送终点,求节省距离
  if (x >= 0) {
    return x * l1;
  } else {
    return -x * l2;
  }
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
  sort(v1 + 1, v1 + 1 + l1), sort(v2 + 1, v2 + 1 + l2);
  cout << d - max(C(v1[l1 / 2].b), C(v2[l2 / 2].b));
  return 0;
}
