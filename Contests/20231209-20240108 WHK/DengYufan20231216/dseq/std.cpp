#include <cmath>
#include <fstream>

using namespace std;

ifstream cin("dseq.in");
ofstream cout("dseq.ans");

const int kMaxN = 2.5e5 + 1;
namespace Sub1 {

int n, m, a[kMaxN];

int main() {
  cin >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1, o, l, r, x, c; i <= m; i++) {
    cin >> o >> l >> r;
    if (o == 1) {
      cin >> x;
      for (int j = l; j <= r; j++) {
        a[j] += x;
      }
    } else if (o == 2) {
      cin >> x;
      for (int j = l; j <= r; j++) {
        a[j] = x;
      }
    } else {
      c = 0, x = a[l];
      for (int j = l + 1; j <= r; j++) {
        for (int y = a[j]; x != y;) {
          if (x < y) {
            y = sqrt(y), c++;
          } else {
            x = sqrt(x), c += j - l;
          }
        }
      }
      cout << c << '\n';
    }
  }
  return 0;
}

}  // namespace Sub1

namespace Sub2 {

struct V {
  int x, c, w, t;
} v[kMaxN << 2];
int n, m, a[kMaxN];

V Merge(V p, V q) {
  V ans = {p.x, p.c + q.c, p.w + q.w, 0};
  for (int &x = ans.x, y = q.x, &c = ans.c; x != y;) {
    if (x < y) {
      y = sqrt(y), c += q.w;
    } else {
      x = sqrt(x), c += p.w;
    }
  }
  return ans;
}

void Pushdown(int p, int l, int r) {
  int mid = l + r >> 1;
  if (v[p].t) {
    v[p << 1] = {v[p].t, 0, mid - l + 1, v[p].t};
    v[p << 1 | 1] = {v[p].t, 0, r - mid, v[p].t};
  }
}

void Init(int p, int l, int r) {
  if (l == r) {
    v[p] = {a[l], 0, r - l + 1, 0};
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

void Change(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    v[p] = {k, 0, r - l + 1, k};
    return;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Change(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Change(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

V Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p];
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l && mid < _r) {
    return Merge(Ask(p << 1, l, mid, _l, _r), Ask(p << 1 | 1, mid + 1, r, _l, _r));
  } else if (mid >= _l) {
    return Ask(p << 1, l, mid, _l, _r);
  } else if (mid < _r) {
    return Ask(p << 1 | 1, mid + 1, r, _l, _r);
  } else {
    cout << "SB DYF!\n";
    exit(0);
  }
}

int main() {
  cin >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Init(1, 1, n);
  for (int i = 1, o, l, r, x; i <= m; i++) {
    cin >> o >> l >> r;
    if (o == 1) {
      cin >> x;
      cout << "Shit! I Can't Solve This Hard Problem!\n";
      return 0;
    } else if (o == 2) {
      cin >> x;
      Change(1, 1, n, l, r, x);
    } else {
      cout << Ask(1, 1, n, l, r).c << '\n';
    }
  }
  return 0;
}

}  // namespace Sub2
int n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  Sub1::n = n;
  return Sub1::main();
}
