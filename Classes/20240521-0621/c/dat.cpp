#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("c.in");

const int kT = 3, kN = 10000, kM = 1000, kC = 3;
int n, m;
string s, t;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int R(int l, int r) { return Rand() % (r - l + 1) + l; }

int main() {
  cout << kT << '\n';
  for (int o = 1; o <= kT; o++) {
    n = R(1, kN), s.resize(n);
    for (int i = 0; i < n; i++) {
      s[i] = R('a', 'a' + kC - 1);
    }
    m = n, t = s;
    for (int i = 0; i < kM; i++) {
      if (m < kN && R(1, 3) == 1) {
        int p = R(0, m);
        char c = R('a', 'a' + kC - 1);
        m++, t = t.substr(0, p) + c + t.substr(p);
      } else if (R(2, 3) == 2) {
        int p = R(0, m - 1);
        m--, t = t.substr(0, p) + t.substr(p + 1);
      } else {
        int p = R(0, m - 1);
        char c = R('a', 'a' + kC - 1);
        t[p] = c;
      }
    }
    cout << n << ' ' << m << ' ' << kM << '\n';
    cout << s << '\n';
    cout << t << '\n';
  }
  return 0;
}
