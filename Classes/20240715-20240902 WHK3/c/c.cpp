#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 15001;
int t, n, a[kMaxN], d1[kMaxN], d2[kMaxN];
int f[kMaxN], g[kMaxN], ff[kMaxN], gg[kMaxN];

void Clear1() {
  for (int i = 1; i <= n; i++) {
    d1[i] = 0;
  }
}

void Change1(int x, int y) {
  for (int i = x; i <= n; i += i & -i) {
    d1[i] = max(d1[i], y);
  }
}

int Ask1(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans = max(ans, d1[i]);
  }
  return ans;
}

void Clear2() {
  for (int i = 1; i <= n; i++) {
    d2[i] = n + 1;
  }
}

void Change2(int x, int y) {
  for (int i = x; i >= 1; i -= i & -i) {
    d2[i] = min(d2[i], y);
  }
}

int Ask2(int x) {
  int ans = n + 1;
  for (int i = x; i <= n; i += i & -i) {
    ans = min(ans, d2[i]);
  }
  return ans;
}

int Dp() {
  int ans = 2;  // it is excepted that ans is O(\sqrt n)
  for (bool o = 1; o; ans += o) {
    Clear1(), Clear2();
    for (int i = n - 1; i >= 1; i--) {
      f[i] = Ask2(a[i] + 1), g[i] = Ask1(a[i] - 1);
      Change2(a[i], ff[i]), Change1(a[i], gg[i]);
      if (i + ans - 1 < n) {
        int j = i + ans - 1;
        Change2(gg[j], a[j]), Change1(ff[j], a[j]);
      }
    }
    // for (int i = 1; i < n; i++) {
      // for (int j = i + 1; j < n; j++) {
      //   if (a[i] < a[j]) {
      //     f[i] = min(f[i], ff[j]);
      //   }
      //   if (a[i] > a[j]) {
      //     g[i] = max(g[i], gg[j]);
      //   }
      // }
      // for (int j = i + ans; j < n; j++) {
      //   if (a[i] < gg[j]) {
      //     f[i] = min(f[i], a[j]);
      //   }
      //   if (a[i] > ff[j]) {
      //     g[i] = max(g[i], a[j]);
      //   }
      // }
    // }
    o = 0;
    for (int i = 1; i < n; i++) {
      o |= f[i] <= n || g[i] >= 1;
      ff[i] = f[i], f[i] = n + 1, gg[i] = g[i], g[i] = 0;
    }
  }
  return ans;
}

int Dp1() {
  for (int i = 1; i < n; i++) {
    ff[i] = f[i] = n + 1, gg[i] = g[i] = 0;
    a[i] < a[n] ? ff[i] = a[n] : gg[i] = a[n];
  }
  return Dp();
}

int Dp2() {
  for (int i = 1; i < n; i++) {
    f[i] = n + 1, g[i] = 0;
    ff[i] = gg[i] = a[i];
  }
  return Dp() - 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    cout << max(Dp1(), Dp2()) << '\n';
  }
  return 0;
}
