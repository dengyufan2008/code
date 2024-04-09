#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1;
struct V {
  int d;
  bool o, s[2], f[2];
  vector<int> e;
} v[kMaxN];
int t, n;

bool C1() {
  for (int i = 1; i <= n; i++) {
    if (v[i].e.size() == 1 && v[i].o) {
      return 1;
    }
  }
  return 0;
}

bool C2() {
  for (int i = 1; i <= n; i++) {
    if (v[i].o) {
      return n & 1 ^ 1;
    }
  }
  return 0;
}

void S(int f, int x) {
  v[x].d = v[f].d + 1;
  v[x].s[v[x].d & 1] |= v[x].o;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i);
      v[x].s[0] |= v[i].s[0];
      v[x].s[1] |= v[i].s[1];
    }
  }
}

bool C3() { return S(0, 1), v[1].s[0] && v[1].s[1]; }

void T(int f, int x) {
  bool b[2] = {};
  for (int o = 0; o < v[x].e.size(); o++) {
    int i = v[x].e[o];
    if (i != f) {
      v[i].f[0] |= b[0];
      v[i].f[1] |= b[1];
      b[0] |= v[i].s[0];
      b[1] |= v[i].s[1];
    }
  }
  b[0] = b[1] = 0;
  for (int o = v[x].e.size() - 1; o >= 0; o--) {
    int i = v[x].e[o];
    if (i != f) {
      v[i].f[0] |= b[0];
      v[i].f[1] |= b[1];
      b[0] |= v[i].s[0];
      b[1] |= v[i].s[1];
    }
  }
  for (int i : v[x].e) {
    if (i != f) {
      v[i].f[0] |= v[x].f[0];
      v[i].f[1] |= v[x].f[1];
      v[i].f[v[x].d & 1] |= v[x].o;
      T(x, i);
    }
  }
}

bool R(int f, int x) {
  for (int i : v[x].e) {
    if (i != f && R(x, i)) {
      return 1;
    }
  }
  int s = v[x].f[v[x].d & 1];
  for (int i : v[x].e) {
    if (i != f) {
      s += v[i].s[v[x].d & 1];
    }
  }
  return s >= 3;
}

bool C4() { return T(0, 1), R(0, 1); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].o;
      v[i].e.clear();
      v[i].s[0] = v[i].s[1] = 0;
      v[i].f[0] = v[i].f[1] = 0;
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    if (C1() || C2() || C3() || C4()) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }
  return 0;
}
