#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1, kMaxL = 22;
int n;
LL p[kMaxN];
LL a, b, c, d, e, f;  // 将 01 看成格路中的 xy, 则围出的格子左下角 (x,y) 会变为 (ax+by+c,dx+ey+f)
vector<pair<int, int>> v[kMaxN << 1];
string ans1, ans2;

void Assert(bool o) {
  if (!o) {
    while (1) {
    }
  }
}

void Exgcd(LL a, LL b, LL c, LL &x, LL &y) {
  if (!b) {
    x = c / a, y = 0;
  } else {
    Exgcd(b, a % b, c, x, y);
    swap(x, y), y -= a / b * x;
    if (y < 0) {  // Gcd(a, b) = 1, 故直接用 a 和 b 调即可
      LL t = (-y + a - 1) / a;
      x -= b * t, y += a * t;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  a = 1, b = 0, c = 0, d = 0, e = 1, f = 0;
  for (int i = 0; i < kMaxL; i++) {
    LL _a = a * 2 + d, _b = b * 2 + e, _c = c * 2 + f + 1;
    LL _d = a + d, _e = b + e, _f = c + f;
    a = _a, b = _b, c = _c, d = _d, e = _e, f = _f;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  sort(p + 1, p + n + 1), n >>= 1;
  for (int i = 1; i <= n; i++) {
    LL z = p[i * 2 - 1] - 1, x, y;
    Exgcd(a + d, b + e, z - c - f, x, y);
    Assert(x >= 0 && x < kMaxN && y >= 0 && y < kMaxN);
    v[x + y].push_back({x, y});
  }
  for (int i = 0, j = 0, x = 0, y = 0; i < kMaxN << 1; i = j) {
    for (; j < kMaxN << 1 && v[i].empty() == v[j].empty(); j++) {
    }
    if (!v[i].empty()) {
      Assert(v[i].size() == 1);
      ans1 += string(v[i][0].first - x, '0');
      ans1 += string(v[i][0].second - y, '1');
      ans1 += '0';
      ans2 += string(v[i][0].first - x, '0');
      ans2 += string(v[i][0].second - y, '1');
      ans2 += '1';
      for (int k = i + 1; k < j; k++) {
        sort(v[k].begin(), v[k].end());

        Assert(v[k].back().first - v[k - 1].back().first +
                   v[k].back().second - v[k - 1].back().second ==
               1);
        if (v[k].back().first == v[k - 1].back().first) {
          ans1 += '1';
        } else {
          ans1 += '0';
        }

        Assert(v[k].front().first - v[k - 1].front().first +
                   v[k].front().second - v[k - 1].front().second ==
               1);
        if (v[k].front().first == v[k - 1].front().first) {
          ans2 += '1';
        } else {
          ans2 += '0';
        }
      }
      ans1 += '1', ans2 += '0';
      Assert(v[j - 1].size() == 1);
      x = v[j - 1][0].first + 1, y = v[j - 1][0].second + 1;
    }
  }
  cout << ans1 << '\n';
  cout << ans2 << '\n';
  return 0;
}
