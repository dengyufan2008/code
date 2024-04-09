#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1;
struct V {
  int d, s, r;
  bool o;
  vector<int> e;
} v[kMaxN];
int t, n, k, l[kMaxN];
bool sub3;
vector<int> shit;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

bool Sub1() {
  for (int i = 1; i <= n; i++) {
    if (v[i].e.size() == 1 && v[i].o) {
      return 1;
    }
  }
  return 0;
}

bool Sub2() {
  return n & 1 ^ 1;
}

bool Sub3() {
  return sub3;
}

void T(int f, int x) {
  v[x].d = v[f].d + 1, v[x].s = 1, v[x].r = ++k;
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
      v[x].s += v[i].s;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    sub3 = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].o;
      v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      sub3 &= x == i && y == i + 1;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    if (Sub1()) {
      cout << "Alice\n";
    } else if (Sub2()) {
      bool o = 0;
      for (int i = 1; i <= n; i++) {
        o |= v[i].o;
      }
      cout << (o ? "Alice\n" : "Bob\n");
    } else if (Sub3()) {
      bool o = v[1].o || v[n].o;
      for (int i = 2; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (v[i].o && v[j].o && (i + j & 1)) {
            o = 1;
          }
        }
      }
      cout << (o ? "Alice\n" : "Bob\n");
    } else {
      k = 0;
      T(0, 1);
      shit.clear();
      for (int i = 1; i <= n; i++) {
        if (v[i].o) {
          shit.push_back(i);
        }
      }
      bool fuck[2] = {};
      for (int i : shit) {
        fuck[v[i].d & 1] = 1;
      }
      cout << (fuck[0] && fuck[1] ? "Alice\n" : "Bob\n");
    }
  }
  return 0;
}
