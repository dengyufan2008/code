#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 1 << 20;
int n, m, a[kMaxN], f[kMaxN], g[kMaxN], pop[kMaxN];
string o;

int Calc0() {
  int s = 0, w = 0;
  for (int i = 0; i < n; i++) {
    if (o[i] == '0') {
      s |= 1 << n - i - 1;
    } else if (o[i] == '1') {
      w |= 1 << n - i - 1;
    }
  }
  int ans = g[w];
  for (int t = s; t; t = t - 1 & s) {
    ans += pop[t] & 1 ? -g[t | w] : g[t | w];
  }
  return ans;
}

int Calc1() {
  int s = 0, w = 0;
  for (int i = 0; i < n; i++) {
    if (o[i] == '1') {
      s |= 1 << n - i - 1;
    } else if (o[i] == '?') {
      w |= 1 << n - i - 1;
    }
  }
  int ans = pop[s] & 1 ? -f[w] : f[w];
  for (int t = s; t; t = t - 1 & s) {
    ans += pop[s ^ t] & 1 ? -f[t | w] : f[t | w];
  }
  return ans;
}

int Calc2() {
  int s = 0, w = 0;
  for (int i = 0; i < n; i++) {
    if (o[i] == '?') {
      s |= 1 << n - i - 1;
    } else if (o[i] == '1') {
      w |= 1 << n - i - 1;
    }
  }
  int ans = a[w];
  for (int t = s; t; t = t - 1 & s) {
    ans += a[t | w];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxN; i++) {
    pop[i] = pop[i ^ (i & -i)] + 1;
  }
  cin >> n >> m >> o;
  for (int i = 0; i < 1 << n; i++) {
    a[i] = f[i] = g[i] = o[i] - '0';
  }
  for (int i = 0; i < n; i++) {
    for (int s = 0; s < 1 << n; s++) {
      if (s >> i & 1) {
        f[s] += f[s ^ 1 << i], g[s ^ 1 << i] += g[s];
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int c0 = 0, c1 = 0, c2 = 0;
    cin >> o;
    for (int j = 0; j < n; j++) {
      c0 += o[j] == '0', c1 += o[j] == '1', c2 += o[j] == '?';
    }
    if (c0 <= c1 && c0 <= c2) {
      cout << Calc0() << '\n';
    } else if (c1 <= c0 && c1 <= c2) {
      cout << Calc1() << '\n';
    } else if (c2 <= c0 && c2 <= c1) {
      cout << Calc2() << '\n';
    }
  }
  return 0;
}
