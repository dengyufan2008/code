#include <fstream>
#include <vector>

using namespace std;

ifstream cin("eggplant.in");
ofstream cout("eggplant.out");

const int kMaxN = 5e3 + 1;
struct A {
  int n, a[kMaxN];

  void Update() {
    for (int &i = n; i > 0 && !a[i - 1]; i--) {
    }
    for (int i = n - 1; i > 0; i--) {
      a[i - 1] += a[i] / 2, a[i] %= 2;
    }
    if (n && !a[0]) {
      int p = 0;
      for (; p < n && !a[p]; p++) {
      }
      a[0] = a[p];
      for (int i = 1; i <= p; i++) {
        a[i] = -a[0];
      }
    } else if (n > 1 && a[0] * a[1] > 0) {
      a[0] += a[1] > 0 ? 1 : -1, a[1] = -a[1];
    }
  }

  void operator+=(const A &x) {
    n = max(n, x.n);
    for (int i = 0; i < x.n; i++) {
      a[i] += x.a[i];
    }
    Update();
  }

  void operator+=(const bool &x) {
    if (!n) {
      n = 1, a[0] = x ? 1 : -1;
    } else if (a[0] * (x ? 1 : -1) > 0) {
      a[0] += x ? 1 : -1;
    } else {
      int w = abs(a[0]);
      n += w;
      for (int i = n - 1; i > w; i--) {
        a[i] = a[i - w];
      }
      for (int i = 1; i <= w; i++) {
        a[i] = a[0] > 0 ? 1 : -1;
      }
      a[0] = x ? 1 : -1, Update();
    }
  }
} f;
struct V {
  bool o;
  A f;
  vector<int> e;
} v[kMaxN];
int n;

void T(int f, int x) {
  for (int i : v[x].e) {
    T(x, i), v[x].f += v[i].f;
  }
  v[x].f += v[x].o;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x >> v[i].o;
    v[x].e.push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].f.n) {
      T(0, i), f += v[i].f;
    }
  }
  cout << (f.a[0] >= 0 ? "Bob\n" : "Alice\n");
  return 0;
}
