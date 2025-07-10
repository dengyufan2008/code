#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct V {
  int s;
  vector<int> e;
} v[kMaxN];
int t, o, n, c, r1, r2;
string s;
vector<int> l[kMaxN];

void FindR1(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      FindR1(x, i), v[x].s += v[i].s;
      mx = max(mx, v[i].s);
    }
  }
  if (max(mx, n - v[x].s) <= n >> 1) {
    c++, r1 = x;
  }
}

void FindR2(int f, int x) {
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      FindR2(x, i), v[x].s += v[i].s;
    }
  }
  if (v[x].e.size() > 2 && (!r2 || v[r2].s < v[x].s)) {
    r2 = x;
  }
}

void CalcS(int f, int x) {
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      CalcS(x, i), v[x].s += v[i].s;
    }
  }
}

void Add(int f, int x, vector<int> &l) {
  l.push_back(x);
  for (int i : v[x].e) {
    if (i != f) {
      Add(x, i, l);
    }
  }
}

void Construct() {
  static vector<int> l1, l2;
  int g = v[r2].e.size() - 1;
  CalcS(0, r2);
  for (int &i : v[r2].e) {
    if (v[i].s > v[v[r2].e[0]].s) {
      swap(i, v[r2].e[0]);
    }
  }
  swap(v[r2].e[0], v[r2].e[g]);
  for (int i = 0; i <= g; i++) {
    l[i].clear();
    Add(r2, v[r2].e[i], l[i]);
    reverse(l[i].begin(), l[i].end());
  }
  l[g].pop_back(), l1 = l[g], l2.clear();
  for (int i = g; i > 0;) {
    for (int j = 0; j < i; j++) {
      l2.push_back(l[j].back()), l[j].pop_back();
    }
    int _i = 0;
    for (int j = 0; j < i; j++) {
      if (!l[j].empty()) {
        swap(l[_i++], l[j]);
      }
    }
    i = _i;
  }
  reverse(l2.begin(), l2.end());
  cout << "YES\n";
  cout << r2 << ' ' << v[r2].e[g] << ' ';
  for (int i = 4; i <= n; i += 2) {
    if (l1.empty() || !l2.empty() && s[i - 2] == '0') {
      cout << l2.back() << ' ', l2.pop_back();
    } else {
      cout << l1.back() << ' ', l1.pop_back();
    }
    if (l2.empty() || !l1.empty() && s[i] == '0') {
      cout << l1.back() << ' ', l1.pop_back();
    } else {
      cout << l2.back() << ' ', l2.pop_back();
    }
  }
  if (n & 1) {
    cout << (l1.empty() ? l2.back() : l1.back()) << ' ';
  }
  cout << '\n';
}

void Solve0() {
  for (int i = 2; i <= n; i += 2) {
    if (s[i] == '1') {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    cout << i << ' ';
  }
  cout << '\n';
}

void Solve1() {
  int g = v[r2].e.size() - 1;
  CalcS(0, r2);
  for (int &i : v[r2].e) {
    if (v[i].s > v[v[r2].e[0]].s) {
      swap(i, v[r2].e[0]);
    }
  }
  swap(v[r2].e[0], v[r2].e[g]);
  for (int i = 2; i <= n; i += 2) {
    if (i > v[v[r2].e[g]].s << 1 && s[i] == '0') {
      cout << "NO\n";
      return;
    }
  }
  Construct();
}

void Solve2() {
  int w = v[r2].s << 1;
  for (int i = 2; i <= n; i += 2) {
    if (i >= w && s[i] == '1') {
      cout << "NO\n";
      return;
    }
  }
  Construct();
}

void Solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    v[i].e.clear();
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  cin >> s, s = '~' + s;
  c = r1 = r2 = 0, FindR1(0, 1), FindR2(0, r1);
  if (n >= 2 && s[2] == '1') {
    cout << "NO\n";
    return;
  } else if (c == 2 && s[n] == '1') {
    cout << "NO\n";
    return;
  }
  for (int i = 1; i <= n; i += 2) {
    if (s[i] == '0') {
      cout << "NO\n";
      return;
    }
  }
  if (!r2) {  // 链
    Solve0();
  } else if (v[r2].s << 1 >= n) {  // r2 为重心
    Solve1();
  } else {  // r2 不为重心
    Solve2();
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> o;
  while (t--) {
    Solve();
  }
  return 0;
}
