#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct H {
  LL n, a[1000001];

  LL Son(LL x) {
    return x + (x < n && a[x] > a[x + 1]);
  }

  void Up() {
    for (LL i = n, j = i >> 1; j && a[i] < a[j]; i = j, j = i >> 1) {
      swap(a[i], a[j]);
    }
  }

  void Down() {
    for (LL i = 1, j = Son(i << 1); j <= n && a[i] > a[j]; i = j, j = Son(i << 1)) {
      swap(a[i], a[j]);
    }
  }

  void Push(LL x) {
    a[++n] = x;
    Up();
  }

  LL Top() {
    return a[1];
  }

  void Pop() {
    swap(a[1], a[n--]);
    if (n) {
      Down();
    }
  }
} h[2];
LL t, n, k;
string s;
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    h[0].n = h[1].n = flag = 0;
    cin >> n >> k >> s;
    for (LL i = 0; i < n; i++) {
      if (flag) {
        h[s[i] - '0'].Push(i);
      } else {
        if (s[i] == '1') {
          flag = true;
          h[1].Push(i);
        }
      }
    }
    while (h[0].n && h[1].n) {
      LL x0 = h[0].Top(), x1 = h[1].Top();
      h[1].Pop();
      if (abs(x0 - x1) <= k) {
        swap(s[x0], s[x1]);
        k -= abs(x0 - x1);
        h[1].Push(x0);
        h[0].Pop();
      }
    }
    cout << s << endl;
  }
  return 0;
}
