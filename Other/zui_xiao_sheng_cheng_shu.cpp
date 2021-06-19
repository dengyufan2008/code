#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, b;
} a[100000];
struct E {
  int a, b, c;
} e[100001];
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
int n, m, k, tot;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  h.Spawn();
  cin >> n >> m;
  for (int i = 1, a, b; i <= m; i++) {
    cin >> a >> b >> e[i].c;
    e[i].a = min(a, b), e[i].b = max(a, b);
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return i.c < j.c;
  });
  for (int i = 1; i <= m && k < n - 1; i++) {
    if (!h.Same(e[i].a, e[i].b)) {
      a[++k] = {e[i].a, e[i].b}, tot += e[i].c;
      h.Push(e[i].a, e[i].b);
    }
  }
  if (k < n - 1) {
    cout << "Impossible!" << endl;
  } else {
    sort(a + 1, a + k + 1, [](A i, A j) {
      return i.a < j.a || i.a == j.a && i.b < j.b;
    });
    cout << tot << endl;
    for (int i = 1; i <= k; i++) {
      cout << a[i].a << " " << a[i].b << endl;
    }
  }
  return 0;
}
