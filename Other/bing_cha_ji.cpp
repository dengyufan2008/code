#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct H {
  int f[100001];

  void Spawn() {
    for (int i = 1; i <= 100000; i++) {
      f[i] = i;
    }
  }

  int Father(int x) {
    return f[x] = (f[x] != x ? Father(f[x]) : f[x]);
  }

  void Push(int x, int y) {
    f[y] = x;
  }

  bool Same(int x, int y) {
    return Father(x) == Father(y);
  }
} h;

int n, q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  h.Spawn();
  cin >> n;
  for (int i = 1, a, b; i <= n; i++) {
    cin >> a >> b;
    h.Push(a, b);
  }
  cin >> q;
  for (int i = 1, a, b; i <= q; i++) {
    cin >> a >> b;
    cout << (h.Same(a, b) ? "Yes" : "No") << endl;
  }
  return 0;
}
