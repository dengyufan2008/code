#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 18, kMod = 998244353;
struct V {
  LL a, b;
  vector<int> e;
} v[kMaxN];
int n, m, r;
LL f[1 << kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Calc(int f, int x, int s) {
  if (s >> x & 1) {
    v[x].a = v[x].b = 0;
    return;
  }
  LL a = v[x].e.size(), b = v[x].e.size();
  for (int i : v[x].e) {
    if (i != f) {
      Calc(x, i, s);
      a = (a + v[i].a) % kMod;
      b = (b - v[i].b + kMod) % kMod;
    }
  }
  v[x].b = Pow(b), v[x].a = a * v[x].b % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> r, r--;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, x--, y--;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int s = 1; s < 1 << n; s++) {
    Calc(r, r, s), f[s] = v[r].a;
  }
  for (int i = 0; i < n; i++) {
    for (int s = 1; s < 1 << n; s++) {
      if (s >> i & 1) {
        f[s] = (f[s] - f[s ^ 1 << i] + kMod) % kMod;
      }
    }
  }
  for (int s = 1; s < 1 << n; s++) {
    if (__builtin_popcount(s) & 1 ^ 1) {
      f[s] = (kMod - f[s]) % kMod;
    }
  }
  for (int i = 0, x, s; i < m; i++) {
    cin >> x, s = 0;
    for (int j = 0, y; j < x; j++) {
      cin >> y, s |= 1 << y - 1;
    }
    cout << f[s] << '\n';
  }
  return 0;
}
