// 傻逼出题人题解给一个注意到充要条件 简直没有母亲😡😡😡
#include <fstream>

using namespace std;

ifstream cin("merge.in");
ofstream cout("merge.out");

const int kMaxN = 1 << 20, kMaxL = 20;
struct V {
  int x, y, ans;
  V operator+(V v) {
    return {max(x, v.x), max(y, v.y), max(max(ans, v.ans), min(x, v.y))};
  }
} w[kMaxN], v[kMaxL][kMaxN];
int n, m, a[kMaxN];
unsigned seed, ans;

unsigned Rand(unsigned &seed) {
  seed ^= seed << 7;
  seed ^= seed >> 15;
  seed ^= seed << 9;
  return seed;
}
void Spawn(const int &n, unsigned &seed, int &l, int &r) {
  int len = Rand(seed) % (n + 1 >> 1) << 1;
  l = Rand(seed) % (n - len) + 1, r = l + len;
}

void Build(int l, int r, int d) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  v[d][mid] = w[mid], v[d][mid + 1] = w[mid + 1];
  for (int i = mid - 1; i >= l; i--) {
    v[d][i] = w[i] + v[d][i + 2];
  }
  for (int i = mid + 2; i <= r; i++) {
    v[d][i] = v[d][i - 2] + w[i];
  }
  Build(l, mid, d + 1), Build(mid + 1, r, d + 1);
}

void Init() {
  for (int i = 0; i <= n; i++) {
    int x = i == 0 ? a[0] : min(a[i - 1], a[i]);
    int y = i == n ? a[n] : min(a[i], a[i + 1]);
    w[i] = {x, y, min(x, y)};
  }
  Build(0, kMaxN - 1, 0);
}

int Ask(int l, int r) {
  if (l == r) {
    return a[l];
  }
  V x = {a[l], min(a[l], a[l + 1]), min(a[l], a[l + 1])};
  V y = {min(a[r - 1], a[r]), a[r], min(a[r - 1], a[r])};
  if (l + 2 == r) {
    return (x + y).ans;
  } else if (l + 4 == r) {
    return (x + w[l + 2] + y).ans;
  } else {
    l += 2, r -= 2;
    int d = __builtin_clz(l ^ r) - 12;
    return (x + v[d][l] + v[d][r] + y).ans;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, n--;
  for (int i = 0; i <= n; i++) {
    cin >> a[i];
  }
  if (!n) {
    cout << unsigned(m) * (m + 1) * a[0] << '\n';
    return 0;
  }
  Init();
  cin >> seed;
  for (int i = 0, l, r; i < m; i++) {
    Spawn(n + 1, seed, l, r), l--, r--;
    ans += unsigned(i + 1) * Ask(l, r);
  }
  cout << ans << '\n';
  return 0;
}
