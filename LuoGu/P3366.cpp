#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct E {
  int a, b, c;
} e[400002];
struct H {
  int f[5001];

  void Spawn() {
    for (int i = 1; i <= 5000; i++) {
      f[i] = i;
    }
  }

  int Father(int x) {
    return f[x] == x ? x : f[x] = Father(f[x]);
  }

  void Push(int x, int y) {
    f[Father(y)] = Father(x);
  }

  bool Same(int x, int y) {
    return Father(x) == Father(y);
  }
} h;
int n, m, k, tot;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  h.Spawn();
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; i++) {
    cin >> e[i].a >> e[i].b >> e[i].c;
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return i.c < j.c;
  });
  for (int i = 1; i <= m && k < n - 1; i++) {
    if (!h.Same(e[i].a, e[i].b)) {
      k++;
      tot += e[i].c;
      h.Push(e[i].a, e[i].b);
    }
  }
  if (k < n - 1) {
    cout << "orz" << endl;
  } else {
    cout << tot << endl;
  }
  return 0;
}
