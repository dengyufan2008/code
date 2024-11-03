#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("girl.in");
ofstream cout("girl.out");

const int kMaxN = 5e5 + 2, kMod = 1e9 + 7;
struct A {
  int l, r;
} a[2][kMaxN];
int n, m[2], f[kMaxN][26][3];

class Seg {
  struct V {
    int w, l, r;
  } v[kMaxN * 20];
  int u, s[kMaxN];

  void Add(int &p, int l, int r, int x) {
    v[++u] = v[p], p = u;
    if (l == r) {
      v[p].w++;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Add(v[p].l, l, mid, x);
    } else {
      Add(v[p].r, mid + 1, r, x);
    }
    v[p].w = v[v[p].l].w + v[v[p].r].w;
  }

  int Pre(int p, int l, int r) {
    if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (v[v[p].r].w) {
      return Pre(v[p].r, mid + 1, r);
    } else {
      return Pre(v[p].l, l, mid);
    }
  }

  int Pre(int p, int l, int r, int x) {
    if (!v[p].w) {
      return 0;
    } else if (r <= x) {
      return Pre(p, l, r);
    }
    int mid = l + r >> 1, ans = 0;
    if (mid < x) {
      ans = Pre(v[p].r, mid + 1, r, x);
    }
    if (ans == 0) {
      ans = Pre(v[p].l, l, mid, x);
    }
    return ans;
  }

 public:
  void InitS(int x) { s[x] = s[x + 1]; }
  void Add(int o, int x) { Add(s[o], 1, n, x); }
  int Pre(int x) { return Pre(s[x + 1], 1, n, x); }
} seg[2];

void Init() {
  int k;
  cin >> n >> k;
  for (int i = 1, l, r; i <= k; i++) {
    cin >> l >> r;
    if (l > r) {
      a[0][++m[0]] = {r, l};
    } else if (l < r) {
      a[1][++m[1]] = {l, r};
    }
  }
  for (int o : {0, 1}) {
    sort(a[o] + 1, a[o] + m[o] + 1, [](A i, A j) {
      return i.r < j.r;
    });
    for (int i = n, j = m[o]; i >= 1; i--) {
      seg[o].InitS(i);
      for (; j >= 1 && a[o][j].r == i; j--) {
        seg[o].Add(i, a[o][j].l);
      }
    }
  }
}

LL Ask(int l, int r, int x, int y, int k) {
  if (l > r || x > y) {
    return 0;
  } else if (l && x) {
    return ((LL)f[r][y][k] - f[l - 1][y][k] - f[r][x - 1][k] + f[l - 1][x - 1][k]) % kMod;
  } else if (l) {
    return ((LL)f[r][y][k] - f[l - 1][y][k]) % kMod;
  } else if (x) {
    return ((LL)f[r][y][k] - f[r][x - 1][k]) % kMod;
  } else {
    return f[r][y][k];
  }
}

void Dp() {
  f[0][0][0] = f[0][1][2] = 1;
  for (int j : {0, 1, 2}) {
    for (int i = 1; i < 26; i++) {
      f[0][i][j] = ((LL)f[0][i][j] + f[0][i - 1][j]) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    int x = seg[0].Pre(i), y = seg[1].Pre(i), w = 2;
    if (x > y) {
      swap(x, y), w = 1;
    }
    for (int j = 0; j < 26; j++) {
      static LL g = 0;

      g += Ask(y, i - 1, 0, 25, 0);
      g -= Ask(y, i - 1, j, j, 0);
      g += Ask(y, i - 1, 0, j - 1, 1);
      g += Ask(y, i - 1, j + 1, 25, 2);
      f[i][j][0] = g % kMod, g = 0;

      g += Ask(x, y - 1, 0, 25, 0);
      g -= Ask(x, y - 1, j, j, 0);
      g += Ask(x, y - 1, 0, j - 1, 1);
      g += Ask(x, y - 1, j + 1, 25, 2);
      f[i][j][w] = g % kMod, g = 0;
    }
    for (int k : {0, 1, 2}) {
      f[i][0][k] = ((LL)f[i][0][k] + f[i - 1][0][k]) % kMod;
      for (int j = 1; j < 26; j++) {
        f[i][j][k] = ((LL)f[i][j][k] + f[i - 1][j][k] + f[i][j - 1][k] - f[i - 1][j - 1][k]) % kMod;
      }
    }
  }
  cout << (Ask(n, n, 0, 25, 0) + kMod) % kMod << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Dp();
  return 0;
}
