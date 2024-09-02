#include <fstream>
#define LL long long

using namespace std;

ifstream cin("perm.in");
ofstream cout("perm.out");

const int kMaxN = 10, kMaxM = 30, kMaxK = 3628800;
const int kHash = 10000019, kMod = 998244353;
struct E {
  int a, b, c, d;
} e[kMaxM];
int n, m, k, f[kMaxK];
LL a[kMaxK];
bool b[kMaxN];
pair<LL, int> s[kHash];

int Hash(LL x) {
  return (x << 15 ^ x >> 9 ^ x << 7 ^ x >> 3) % kHash;
}

void Change(LL x, int k) {
  int y = Hash(x);
  for (; s[y].first;) {
    if (y == kHash - 1) {
      y = 0;
    } else {
      y++;
    }
  }
  s[y] = {x, k};
}

int Find(LL x) {
  int y = Hash(x);
  for (; s[y].first != x;) {
    if (y == kHash - 1) {
      y = 0;
    } else {
      y++;
    }
  }
  return s[y].second;
}

void S(int x, LL w) {
  if (x == n) {
    a[k] = w, Change(w, k), k++;
    return;
  }
  for (int i = 0; i < n; i++) {
    if (!b[i]) {
      b[i] = 1, S(x + 1, w << 4 | i), b[i] = 0;
    }
  }
}

bool C(int x) {
  static int r[kMaxN] = {};
  for (int i = 0; i < n; i++) {
    r[a[x] >> (i << 2) & 15] = i;
  }
  for (int i = 0; i < m; i++) {
    if (r[e[i].a] < r[e[i].b] && r[e[i].c] > r[e[i].d]) {
      return 0;
    }
  }
  return 1;
}

void Update(int &x, int y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> e[i].a >> e[i].b >> e[i].c >> e[i].d;
    e[i].a--, e[i].b--, e[i].c--, e[i].d--;
  }
  S(0, 0), f[0] = 1;
  for (int i = 0; i < k; i++) {
    if (C(i)) {
      for (int j = 1; j < n; j++) {
        LL w = a[i], x = w >> (j - 1 << 2) & 15, y = w >> (j << 2) & 15;
        w += y - x << (j - 1 << 2), w += x - y << (j << 2);
        Update(f[Find(w)], f[i]);
      }
    }
  }
  cout << f[k - 1] << '\n';
  return 0;
}
