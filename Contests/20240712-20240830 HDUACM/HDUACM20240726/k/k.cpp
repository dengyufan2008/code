#include <fstream>
#define LL long long

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 2e5 + 1, kMove[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
const LL kInf = 1e16;
struct V {
  LL x, y;
  int o;
} v[kMaxN];
int n, u[128];
LL x, ans, _ans;
char c;

LL Calc(LL t) {
  LL xmin = kInf, xmax = -kInf, ymin = kInf, ymax = -kInf;
  for (int i = 1; i <= n; i++) {
    LL _x = v[i].x + t * kMove[v[i].o][0];
    LL _y = v[i].y + t * kMove[v[i].o][1];
    xmin = min(xmin, _x), xmax = max(xmax, _x);
    ymin = min(ymin, _y), ymax = max(ymax, _y);
  }
  return xmax - xmin + ymax - ymin << 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  u['E'] = 0, u['W'] = 1, u['S'] = 2, u['N'] = 3;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y >> c, v[i].o = u[c];
  }
  ans = Calc(0);
  for (int i = 40; i >= 0; i--) {
    _ans = Calc(x + (1LL << i));
    if (_ans < ans) {
      x += 1LL << i, ans = _ans;
      continue;
    }
    _ans = Calc(x - (1LL << i));
    if (_ans < ans) {
      x -= 1LL << i, ans = _ans;
      continue;
    }
  }
  cout << ans << '\n';
  return 0;
}
