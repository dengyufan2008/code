#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 5e4 + 1, kMaxM = 2e5 + 1, kB = 225;
struct Q {
  int x, y, d;
} q[kMaxM];
struct H {
  int t[kB], a[kB][kMaxN];
  bool u;
  H(bool _u) : u(_u) {}

  int Insert(int x) {
    int mn = kMaxN;
    for (int i = 1; i < kB; i++) {
      int l = 1, r = min(t[i], mn);
      while (l <= r) {
        int mid = l + r >> 1;
        if ((a[i][mid] < x) ^ u) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      mn = min(mn, l), swap(x, a[i][l]);
      if (t[i] < l) {
        return t[i]++, u ? t[i] : i;
      }
    }
    return 0;
  }
} h1(0), h2(1);
struct T {
  int a[kMaxN];

  void Add(int x) {
    for (int i = x; i < kMaxN; i += i & -i) {
      a[i]++;
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += a[i];
    }
    return ans;
  }
} t;
int n, m, a[kMaxN], ans[kMaxM];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, a[i] = h1.Insert(x) | h2.Insert(x);
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].x >> q[i].y, q[i].d = i;
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.x < j.x;
  });
  for (int i = 1, j = 1; i <= m; i++) {
    for (; j <= q[i].x; j++) {
      t.Add(a[j]);
    }
    ans[q[i].d] = t.Ask(q[i].y);
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
