#include <fstream>
#include <map>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("rain.in");
ofstream cout("rain.out");

const int kMaxN = 1e4 + 1, kMaxM = 20, kMod = 998244353;
struct V {
  LL a[kMaxM][kMaxM];

  V operator*(const V &v) const {
    V ans;
    for (int i = 0; i < kMaxM; i++) {
      for (int j = 0; j < kMaxM; j++) {
        ans.a[i][j] = 0;
        for (int k = 0; k < kMaxM; k++) {
          ans.a[i][j] = (ans.a[i][j] + a[i][k] * v.a[k][j] % kMod) % kMod;
        }
      }
    }
    return ans;
  }
} o, w, h, d[kMaxN];
int k, l, r, t;
string s;
vector<int> v[kMaxN];
map<pair<int, int>, int> m;

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

void Calc() {
  cin >> k >> l >> r >> s;
  for (int i = 0, j = Pow(k); i < k; i++) {
    o.a[i][i] = 1, w.a[i][0] = 1LL * (i + 1) * j % kMod;
    if (i + 1 < k) {
      w.a[i][i + 1] = 1LL * (k - i - 1) * j % kMod;
    }
  }
  s = '~' + s, h = d[0] = o;
  V _w = w;
  for (int i = 1; i <= l; i <<= 1) {
    if (i & l) {
      h = h * _w;
    }
    _w = _w * _w;
  }
  for (int i = 1; i <= r - l; i++) {
    d[i] = d[i - 1] * w;
  }
}

void Run() {
  int x = 0, y = 0, ans = 1;
  m[{0, 0}] = 0, v[0].push_back(0);
  for (int i = 1; i <= r - l; i++) {
    if (s[i] == 'U' || s[i] == 'D') {
      x += s[i] == 'U' ? -1 : 1;
    } else {
      y += s[i] == 'L' ? -1 : 1;
    }
    auto p = m.find({x, y});
    if (p != m.end()) {
      v[p->second].push_back(i);
    } else {
      m[{x, y}] = ++t, v[t].push_back(i);
    }
  }
  for (int i = 0; i <= t; i++) {
    V _w = h * d[v[i][0]];
    for (int j = 1; j < v[i].size(); j++) {
      _w.a[0][0] = 0, _w = _w * d[v[i][j] - v[i][j - 1]];
    }
    int s = 0;
    for (int j = 1; j < kMaxM; j++) {
      s = (s + _w.a[0][j]) % kMod;
    }
    ans = 1LL * ans * s % kMod;
  }
  cout << ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Calc(), Run();
  return 0;
}
