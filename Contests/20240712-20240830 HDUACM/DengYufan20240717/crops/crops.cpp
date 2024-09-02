#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("crops.in");
ofstream cout("crops.out");

const LL kMaxN = 2e5 + 1;
struct V {
  int f, t, w, mn;
  bool o[2];
  LL g[2];
  vector<int> e;
} v[kMaxN];
int n;
vector<int> l;

void S(int f, int x) {
  v[x].f = f;
  if (v[x].e.empty() || x > 1 && v[x].e.size() == 1) {
    v[x].g[0] = v[x].w;
    return;
  }
  int &t = v[x].t, w = 0;
  LL s = 0;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i), s += v[i].g[0];
      if (w < v[i].g[0] - v[i].g[1]) {
        w = v[i].g[0] - v[i].g[1], t = i;
      } else if (w == v[i].g[0] - v[i].g[1]) {
        t = 0;
      }
    }
  }
  v[x].mn = w, v[x].g[0] = s - max(w - v[x].w, 0), v[x].g[1] = s - w;
}

void T(int f, int x) {
  if (v[x].o[0]) {
    for (int i : v[x].e) {
      if (i != f) {
        if (i != v[x].t || v[x].mn <= v[x].w) {
          v[i].o[0] = 1;
        }
        if (v[i].g[0] - v[i].g[1] == v[x].mn && v[x].mn >= v[x].w) {
          v[i].o[1] = 1;
        }
      }
    }
  }
  if (v[x].o[1]) {
    for (int i : v[x].e) {
      if (i != f) {
        if (i != v[x].t) {
          v[i].o[0] = 1;
        }
        if (v[i].g[0] - v[i].g[1] == v[x].mn) {
          v[i].o[1] = 1;
        }
      }
    }
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  S(0, 1), v[1].o[0] = 1, T(0, 1);
  for (int i = 1; i <= n; i++) {
    if (v[i].o[0] && (v[i].w <= v[i].mn || v[i].e.empty() || i > 1 && v[i].e.size() == 1)) {
      l.push_back(i);
    }
  }
  cout << v[1].g[0] << '\n';
  cout << l.size() << '\n';
  for (int i = 0; i < l.size(); i++) {
    cout << l[i] << " \n"[i + 1 == l.size()];
  }
  return 0;
}
