#include <algorithm>
#include <bitset>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("grouping.in");
ofstream cout("grouping.out");

const int kMaxN = 1e4 + 1, kMaxM = 1e6 + 1;
const LL kMod = 114514191981000001;
struct V {
  int f, c[2];
  bool o;
} v[kMaxN];
int n, m, b[kMaxN];
LL g[kMaxN * 3];
pair<int, int> e[kMaxM];
vector<int> l, t;
bitset<kMaxN << 1> f[kMaxN];

int GetRoot(int x, bool &o) {
  if (v[x].f == x) {
    return x;
  }
  o ^= v[x].o, v[x].o ^= o;
  v[x].f = GetRoot(v[x].f, o), v[x].o ^= o;
  return v[x].f;
}

void Insert(int x) {
  if (x) {
    x = abs(x);
    for (int i = (kMaxN << 1) + x - 1; i >= x << 1; i--) {
      g[i] = (g[i] + g[i - (x << 1)]) % kMod;
    }
    for (int i = 0; i < kMaxN << 1; i++) {
      g[i] = g[i + x], g[i + x] = 0;
    }
  }
}

void Delete(int x) {
  if (x) {
    x = abs(x);
    for (int i = (kMaxN << 1) + x - 1; i >= x; i--) {
      g[i] = g[i - x], g[i - x] = 0;
    }
    for (int i = x << 1; i < (kMaxN << 1) + x; i++) {
      g[i] = (g[i] - g[i - (x << 1)] + kMod) % kMod;
    }
  }
}

void Check(int x, int y) {
  bool o = 1;
  x = GetRoot(x, o), y = GetRoot(y, o);
  if (x == y) {
    return;
  }
  v[x].c[0] + v[x].c[1] > v[y].c[0] + v[y].c[1] ? swap(x, y) : void();
  Delete(v[x].c[0] - v[x].c[1]), Delete(v[y].c[0] - v[y].c[1]);
  v[x].f = y, v[x].o = o, v[y].c[0] += v[x].c[o], v[y].c[1] += v[x].c[!o];
  Insert(v[y].c[0] - v[y].c[1]);
  if (!g[kMaxN]) {
    v[x].o = !o;
    Delete(v[y].c[0] - v[y].c[1]);
    v[y].c[0] -= v[x].c[o], v[y].c[1] -= v[x].c[!o];
    v[y].c[0] += v[x].c[!o], v[y].c[1] += v[x].c[o];
    Insert(v[y].c[0] - v[y].c[1]);
  }
}

void Print() {
  f[0].set(kMaxN);
  for (int i = 1; i <= n; i++) {
    b[i] = 2;
  }
  for (int i = 1; i <= n; i++) {
    bool o = 0;
    int x = GetRoot(i, o);
    if (b[x] == 2) {
      b[x] = o, l.push_back({v[x].c[o] - v[x].c[!o]}), t.push_back(x);
    }
  }
  reverse(l.begin(), l.end()), reverse(t.begin(), t.end());
  for (int i = 0; i < l.size(); i++) {
    if (l[i]) {
      f[i + 1] = f[i] << abs(l[i]) | f[i] >> abs(l[i]);
    } else {
      f[i + 1] = f[i];
    }
  }
  for (int i = l.size() - 1, j = 0; i >= 0; i--) {
    if (f[i][j - l[i] + kMaxN]) {
      j -= l[i];
    } else {
      j += l[i], b[t[i]] ^= 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    bool o = 0;
    int x = GetRoot(i, o);
    cout << (b[x] ^ o);
  }
  cout << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, n <<= 1;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].first >> e[i].second;
  }
  g[kMaxN] = 1;
  for (int i = 1; i <= n; i++) {
    v[i].f = i, v[i].c[0] = 1, Insert(1);
  }
  for (int i = m; i >= 1; i--) {
    Check(e[i].first, e[i].second);
  }
  Print();
  return 0;
}
