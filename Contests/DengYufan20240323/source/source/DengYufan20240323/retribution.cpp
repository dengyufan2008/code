#include <fstream>
#include <random>

using namespace std;

ifstream cin("retribution.in");
ofstream cout("retribution.out");

const int kMaxN = 1e4 + 1, kMove[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int n, m, q, seed, b[kMaxN], o[128];
char c[kMaxN];

namespace Input {
mt19937_64 R;

inline void Init(int seed) {
  R = mt19937_64(seed);
}

inline int Get(int l, int r) {
  uniform_int_distribution<int> distribution(l, r);
  return distribution(R);
}
}  // namespace Input
using Input::Get;
using Input::Init;

int R(int x, int y) { return (x - 1) * m + y; }

bool S(int x1, int y1, int x2, int y2, int t) {
  if (x1 == x2 && y1 == y2) {
    return 1;
  } else if (x1 < 1 || y1 < 1 || x1 > n || y1 > m || b[R(x1, y1)] == t) {
    return 0;
  }
  b[R(x1, y1)] = t;
  for (int i = 0; i < 4; i++) {
    if (i != o[c[R(x1, y1)]] && S(x1 + kMove[i][0], y1 + kMove[i][1], x2, y2, t)) {
      return 1;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  o['L'] = 0, o['R'] = 1, o['U'] = 2, o['D'] = 3;
  cin >> n >> m >> q >> seed;
  for (int i = 1; i <= n * m; i++) {
    cin >> c[i];
  }
  Init(seed);
  for (int i = 1; i <= q; i++) {
    int x1 = Get(1, n), y1 = Get(1, m), x2 = Get(1, n), y2 = Get(1, m);
    cout << S(x1, y1, x2, y2, i);
  }
  cout << '\n';
  return 0;
}
