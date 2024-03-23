#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 5e5 + 1;
struct V {
  int d, l, r;
  bool b, _b;
  vector<int> e;
} v[kMaxN];
int n, m, k;
bool ans;
vector<int> l;

void T(int x) {
  v[x].d = v[x].l = ++k;
  l.push_back(x);
  for (int i : v[x].e) {
    if (v[i].d) {
      if (!v[i].r) {
        v[x].l = min(v[x].l, v[i].d);
      }
    } else {
      T(i);
      v[x].l = min(v[x].l, v[i].l);
    }
    if (i != x) {
      v[x]._b |= v[i].b | v[i]._b;
    }
  }
  if (v[x].b && v[x]._b) {
    cout << "Yes";
    exit(0);
  } else if (v[x].d == v[x].l) {
    int c = 0;
    while (l.back() != x) {
      v[l.back()].r = x, l.pop_back(), c++;
    }
    v[l.back()].r = x, l.pop_back(), c++;
    ans |= c > 1;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    if (x == y) {
      if (v[x].b) {
        cout << "Yes";
        return 0;
      }
      v[x].b = 1;
    }
    v[x].e.push_back(y);
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].d) {
      T(i);
    }
  }
  cout << (ans ? "Yes" : "No");
  return 0;
}
