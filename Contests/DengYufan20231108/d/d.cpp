#include <bitset>
#include <iostream>
#include <unordered_map>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const LL kMove[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
LL n, m;
bitset<36> s;
unordered_map<LL, LL> q;

LL R(LL x, LL y) { return x * (m + 1) + y; }

LL W(LL x, LL y, LL z, bool b) { return (R(x, y) * (1LL << 36) + z) * 2LL + b; }

bool S(LL x, LL y, bool b) {  // 0:Mouse 1:Cat
  if (x < 0 || x > m || y < 0 || y > m) {
    return !b;
  } else if (s[R(x, y)]) {
    return b;
  }
  LL w = W(x, y, s.to_ullong(), b);
  if (q.count(w)) {
    return ~q[w] ? q[w] : b;
  }
  q[w] = -1;
  if (b) {
    for (int i = s._Find_first(); i != 36; i = s._Find_next(i)) {
      for (int j = 0; j < 4; j++) {
        LL x = i / (m + 1), y = i % (m + 1), _x = x + kMove[j][0], _y = y + kMove[j][1];
        if (_x >= 0 && _x <= m && _y >= 0 && _y <= m && !s[R(_x, _y)]) {
          s[i] = 0, s[R(_x, _y)] = 1;
          if (!S(x, y, 0)) {
            s[i] = 1, s[R(_x, _y)] = 0;
            return q[w] = 1;
          }
          s[i] = 1, s[R(_x, _y)] = 0;
        }
      }
    }
    return q[w] = 0;
  } else {
    for (int i = 0; i < 4; i++) {
      if (!S(x + kMove[i][0], y + kMove[i][1], 1)) {
        return q[w] = 1;
      }
    }
    return q[w] = 0;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, ans; i <= n; i++) {
    cin >> x >> y;
    s[R(x, y)] = 1, ans = 0;
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= m; k++) {
        if (!S(j, k, 0)) {
          ans++;
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
