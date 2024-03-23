#include <iostream>
#include <queue>
#define PII pair<int, int>

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 801, kMaxM = 1e5 + 1, kMove[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n, m, k, t, w[16], a[kMaxN * kMaxN], s[kMaxM << 1], b[kMaxN * kMaxN], d[kMaxN * kMaxN];
pair<int, int> f[kMaxN * kMaxN], p[kMaxN * kMaxN];
vector<pair<int, int>> v;

int R(int x, int y) { return (x - 1) * m + y; }

int R(PII x) { return R(x.first, x.second); }

void Input() {
  int r[128];
  char c;
  r['N'] = 0, r['S'] = 1, r['W'] = 2, r['E'] = 3;
  cin >> k >> n >> m;
  for (int i = 1; i <= k; i++) {
    cin >> c;
    s[i] = r[c], s[i + k] = s[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[R(i, j)];
    }
  }
}

void Init() {
  for (int i = 0; i < 16; i++) {
    for (int l = 1, r = 1; l <= (k << 1);) {
      for (l = r; l <= (k << 1) && !(i >> s[l] & 1); l++) {
      }
      for (r = l; r <= (k << 1) && (i >> s[r] & 1); r++) {
      }
      w[i] = max(w[i], r - l);
    }
    if (w[i] >= k) {
      w[i] = kMaxM;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[R(i, j)]) {
        d[R(i, j)] = 1, f[R(i, j)] = {i, j}, v.push_back({i, j});
      }
    }
  }
}

PII GetRoot(PII x) { return f[R(x)] == x ? x : f[R(x)] = GetRoot(f[R(x)]); }

bool C(PII x) { return x.first >= 1 && x.first <= n && x.second >= 1 && x.second <= m; }

int T(PII x) {
  int ans = 0;
  for (int i = 0; i < 4; i++) {
    PII _x = {x.first + kMove[i][0], x.second + kMove[i][1]};
    ans |= (C(_x) && b[R(_x)] == t) << i;
  }
  return ans;
}

int S(int x, int y, bool o) {
  int c = 1;
  queue<PII> q;
  for (q.push({x, y}), b[R(x, y)] = t, p[R(x, y)] = {1, 0}; !q.empty(); q.pop()) {
    PII z = q.front();
    for (int i = 0; i < 4; i++) {
      PII _z = {z.first + kMove[i][0], z.second + kMove[i][1]};
      if (C(_z) && a[R(_z)] && b[R(_z)] != t && w[T(_z)] >= a[R(_z)]) {
        q.push(_z), b[R(_z)] = t, c++;
        if (o && GetRoot({x, y}) != GetRoot(_z)) {
          p[R(x, y)] = _z;
          return 114514;
        }
      }
    }
  }
  return c;
}

void Walk() {
  vector<pair<int, int>> _v;
  for (bool o = 1; o;) {
    o = 0;
    for (PII i : v) {
      t++, S(i.first, i.second, 1), o |= R(p[R(i)]);
    }
    for (PII i : v) {
      if (R(p[R(i)]) && GetRoot(i) != GetRoot(p[R(i)])) {
        d[R(GetRoot(p[R(i)]))] += d[R(GetRoot(i))];
        f[R(GetRoot(i))] = GetRoot(p[R(i)]);
      }
    }
    for (PII i : v) {
      if (GetRoot(i) == i) {
        _v.push_back(i);
      }
    }
    v.swap(_v), _v.clear();
  }
}

void CalcAns() {
  int x, ans1 = kMaxN * kMaxN, ans2 = 0;
  for (PII i : v) {
    t++, x = S(i.first, i.second, 0);
    if (x < ans1) {
      ans1 = ans2 = x;
    } else if (x == ans1) {
      ans2 += x;
    }
  }
  cout << ans1 << '\n'
       << ans2 << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Init(), Walk(), CalcAns();
  return 0;
}
