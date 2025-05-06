#include <fstream>
#define LL long long

using namespace std;

ifstream cin("game.in");
ofstream cout("game.out");

const int kMaxN = 5e5 + 1;
int n, m, k, a[kMaxN];
LL s;

class Seg {
  LL v[kMaxN << 2];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = max(m - a[l], 0);
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  void Change(int p, int l, int r, int x, int y) {
    if (l == r) {
      v[p] = y;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  int Ask(int p, int l, int r, int w) {
    if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (v[p << 1] >= w) {
      return Ask(p << 1, l, mid, w);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, w - v[p << 1]);
    }
  }

 public:
  void Init() { Init(1, 0, n); }
  void Change(int x, int y) { Change(1, 0, n, x, max(m - y, 0)); }
  int Ask(int w) { return v[1] >= w ? Ask(1, 0, n, w) : n + 1; }
} seg;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k, s = m++;
  for (int i = 0; i <= n; i++) {
    cin >> a[i], s += a[i];
  }
  seg.Init();
  cout << min(s / m, (LL)seg.Ask(m - s % m)) << '\n';
  for (int i = 1, x, y; i <= k; i++) {
    cin >> x >> y;
    s += y - a[x], a[x] = y, seg.Change(x, a[x]);
    cout << min(s / m, (LL)seg.Ask(m - s % m)) << '\n';
  }
  return 0;
}
