#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 17, kMod = 1e9 + 7, kInf = 114514;
struct V {
  int f;
  LL g;
  void operator+=(V v) {
    if (f < v.f) {
      *this = v;
    } else if (f == v.f) {
      g = (g + v.g) % kMod;
    }
  }
  V operator*(V v) {
    return {f + v.f, g * v.g % kMod};
  }
} ans, v[1 << kMaxN][kMaxN + 1];
int n;
LL a[1 << kMaxN], w[kMaxN];

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

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> a[0], n--;
  for (int i = 0; i < n; i++) {
    cin >> a[1 << i], a[1 << i] -= a[0], a[0] += a[1 << i];
  }
  for (int s = 0; s < 1 << n; s++) {
    if ((s & -s) != s) {
      a[s] = a[s ^ s & -s] + a[s & -s];
    }
  }
  w[0] = 1;
  for (int i = 1; i < n; i++) {
    w[i] = w[i - 1] * Pow(i + 1) % kMod;
  }
  for (int i = 2; i < n; i++) {
    w[i] = w[i] * Pow(i + 1, i - 1) % kMod;
  }
  v[0][0] = {0, 1};
  for (int s = 0; s + 1 < 1 << n; s++) {
    for (int i = 0; i < n; i++) {
      if (v[s][i].g) {
        for (int j = 0; j < n; j++) {
          if (s >> j & 1 ^ 1) {
            if (a[s | 1 << j]) {
              v[s | 1 << j][i + 1] += v[s][i];
            } else {
              v[s | 1 << j][0] += v[s][i] * (V){1, w[i]};
            }
          }
        }
      }
    }
  }
  ans = v[(1 << n) - 1][0];
  for (int s = 0; s + 1 < 1 << n; s++) {
    int c = n - __builtin_popcount(s);
    ans += v[s][0] * (V){0, Pow(c + 2, c - 1) * 2 % kMod};
  }
  for (int i = 2; i <= ans.f; i++) {
    ans.g = ans.g * Pow(i) % kMod;
  }
  ans.f = n - ans.f;
  for (int i = 2; i <= ans.f; i++) {
    ans.g = ans.g * i % kMod;
  }
  cout << ans.f << '\n' << ans.g << '\n';
  return 0;
}
