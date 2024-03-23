#include <iostream>
#include <set>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 2.5e5 + 1, kMaxM = kMaxN << 1, kInf = 1e9;
struct T {
  struct V {
    int ans, w[2];
  } v[kMaxM << 2];
  multiset<int> s[2][kMaxM];

  void Init() {
    v[0].ans = v[0].w[0] = v[0].w[1] = kInf;
    fill(&v[1], &v[kMaxM << 2], v[0]);
    s[0][0].insert(kInf), s[1][0].insert(kInf);
    fill(&s[0][1], &s[0][kMaxM], s[0][0]);
    fill(&s[1][1], &s[1][kMaxM], s[1][0]);
  }

  void Change(int p, int l, int r, int x, int k, bool o) {
    if (l == r) {
      v[p].w[o] = k, v[p].ans = v[p].w[0] + v[p].w[1];
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, k, o);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, k, o);
    }
    v[p].w[0] = min(v[p << 1].w[0], v[p << 1 | 1].w[0]);
    v[p].w[1] = min(v[p << 1].w[1], v[p << 1 | 1].w[1]);
    v[p].ans = v[p << 1].w[0] + v[p << 1 | 1].w[1];
    v[p].ans = min(v[p].ans, min(v[p << 1].ans, v[p << 1 | 1].ans));
  }

  void Insert(int p, int w, bool o) {
    if (*s[o][p].begin() > w) {
      Change(1, 1, kMaxM - 1, p, w, o);
    }
    s[o][p].insert(w);
  }

  void Erase(int p, int w, bool o) {
    auto t = s[o][p].find(w);
    s[o][p].erase(t);
    if (*s[o][p].begin() > w) {
      Change(1, 1, kMaxM - 1, p, *s[o][p].begin(), o);
    }
  }

  int Ask() { return v[1].ans; }
} t[2];
int n, g;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  t[0].Init(), t[1].Init();
  cin >> n >> g;
  for (int i = 1, o, x, y, z, p = 0; i <= n; i++) {
    cin >> o >> x >> y >> z;
    if (g) {
      y ^= p, z ^= p;
    }
    if (o == 1) {
      if (x) {
        t[0].Insert(z - y + kMaxN, y, 0), t[1].Insert(z - y + kMaxN, z, 1);
      } else {
        t[0].Insert(y - z + kMaxN, y, 1), t[1].Insert(y - z + kMaxN, z, 0);
      }
    } else {
      if (x) {
        t[0].Erase(z - y + kMaxN, y, 0), t[1].Erase(z - y + kMaxN, z, 1);
      } else {
        t[0].Erase(y - z + kMaxN, y, 1), t[1].Erase(y - z + kMaxN, z, 0);
      }
    }
    p = min(t[0].Ask(), t[1].Ask());
    p == kInf && (p = 0);
    cout << p << '\n';
  }
  return 0;
}
