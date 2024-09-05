#include <fstream>

using namespace std;

ifstream cin("jkp.in");
ofstream cout("jkp.out");

const int kMaxN = 2e5 + 1;
struct V {
  int d[2][3], t[3];
} v[kMaxN << 2];
int n, m, a[3], t[3], u[3][3];
string s;

void Tag(int p) {
  int c = (t[0] == 0) + (t[1] == 1) + (t[2] == 2);
  V ans = {};
  for (int i : {0, 1, 2}) {
    ans.t[i] = t[v[p].t[i]];
  }
  if (c == 0) {
    for (int i : {0, 1}) {
      for (int j : {0, 1, 2}) {
        ans.d[i][j] = v[p].d[i][u[j][t[0]]];
      }
    }
  } else if (c == 1) {
    int d = (t[1] != 1 ? 1 : 0) ^ (t[2] != 2 ? 2 : 0);
    for (int i : {0, 1}) {
      for (int j : {0, 1, 2}) {
        ans.d[i][j] = v[p].d[i ^ 1][t[j] == j ? j : j ^ d];
      }
    }
  } else {
    return;
  }
  v[p] = ans;
}

void Pushdown(int p) {
  t[0] = v[p].t[0], t[1] = v[p].t[1], t[2] = v[p].t[2];
  Tag(p << 1), Tag(p << 1 | 1);
  v[p].t[0] = 0, v[p].t[1] = 1, v[p].t[2] = 2;
}

V Merge(V x, V y) {
  V ans = {};
  ans.t[0] = 0, ans.t[1] = 1, ans.t[2] = 2;
  for (int i : {0, 1}) {
    for (int j : {0, 1, 2}) {
      int d = x.d[i][j];
      ans.d[i][j] = (d + y.d[i][u[j][i ? (3 - d) % 3 : d]]) % 3;
    }
  }
  return ans;
}

void Init(int p, int l, int r) {
  v[p].t[0] = 0, v[p].t[1] = 1, v[p].t[2] = 2;
  if (l == r) {
    v[p].d[0][s[l] - 'A'] = v[p].d[1][s[l] - 'A'] = 1;
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

void Swap(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    t[0] = a[0], t[1] = a[1], t[2] = a[2], Tag(p);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Swap(p << 1, l, mid, _l, _r);
  }
  if (mid < _r) {
    Swap(p << 1 | 1, mid + 1, r, _l, _r);
  }
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

V Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p];
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l && mid < _r) {
    V x = Ask(p << 1, l, mid, _l, _r);
    V y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
    return Merge(x, y);
  } else if (mid >= _l) {
    return Ask(p << 1, l, mid, _l, _r);
  } else {
    return Ask(p << 1 | 1, mid + 1, r, _l, _r);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  u[0][0] = 0, u[1][0] = 1, u[2][0] = 2;
  u[0][1] = 2, u[1][1] = 0, u[2][1] = 1;
  u[0][2] = 1, u[1][2] = 2, u[2][2] = 0;
  cin >> n >> m >> s, s = '~' + s;
  Init(1, 1, n);
  for (int i = 1, o, l, r; i <= m; i++) {
    static char x, y;
    cin >> o >> l >> r >> x;
    if (o == 0) {
      cin >> y, a[0] = 0, a[1] = 1, a[2] = 2;
      swap(a[x - 'A'], a[y - 'A']);
      Swap(1, 1, n, l, r);
    } else {
      V w = Ask(1, 1, n, l, r);
      int d = w.d[0][u[x - 'A'][1]];
      cout << char('A' + u[x - 'A'][d]) << '\n';
    }
  }
  return 0;
}
