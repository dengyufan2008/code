#include <fstream>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const LL kMaxN = 2e5 + 1, kInf = 1e18;
struct V {
  LL k = -1, b;
  LL Calc(int x) {
    return k * x + b;
  }
} v[kMaxN << 2];
int n, a[kMaxN];
LL s, w, ans;

void Add(int p, int l, int r, V x) {
  if (v[p].k == -1) {
    v[p] = x;
    return;
  }
  int mid = l + r >> 1;
  if (v[p].Calc(mid) < x.Calc(mid)) {
    swap(v[p], x);
  }
  if (v[p].Calc(l) < x.Calc(l)) {
    Add(p << 1, l, mid, x);
  } else if (v[p].Calc(r) < x.Calc(r)) {
    Add(p << 1 | 1, mid + 1, r, x);
  }
}

LL Ask(int p, int l, int r, int x) {
  LL ans = v[p].k == -1 ? -kInf : v[p].Calc(x);
  if (l != r) {
    int mid = l + r >> 1;
    if (mid >= x) {
      ans = max(ans, Ask(p << 1, l, mid, x));
    } else {
      ans = max(ans, Ask(p << 1 | 1, mid + 1, r, x));
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i >= 1; i--) {
    Add(1, 1, n, V{s, -w});
    s += a[i], w += 1LL * a[i] * (i + 1);
    ans = max(ans, Ask(1, 1, n, i) - s * i + w);
  }
  cout << ans << '\n';
  return 0;
}
