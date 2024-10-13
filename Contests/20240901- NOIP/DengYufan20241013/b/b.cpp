#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

int t, n, m, ansm;
LL answ;

int Next(int x, int m, int &t) {
  t += (n - x) / m + 1;
  return m - (n - x) % m;
}

LL Calc2(int x, int m, int t) {
  int y = (1LL * m * t - x) / (m - 1) + 1;
  y += ((x - y) % m + m) % m;
  int _n = n - (n - x) % m;
  if (y <= _n) {
    return 1LL * (_n - y + m) / m * (y + _n) / 2;
  } else {
    return 0;
  }
}

LL Calc(int m) {
  int t = 1;
  LL ans = Calc2(m, m, t);
  for (int i = Next(m, m, t); i != m; i = Next(i, m, t)) {
    ans += Calc2(i, m, t);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    ansm = 1, answ = 0;
    cin >> n >> m, m > n && (m = n);
    for (int i = 2; i <= m; i++) {
      LL w = Calc(i);
      if (w > answ) {
        ansm = i, answ = w;
      }
    }
    cout << ansm << '\n';
  }
  return 0;
}
