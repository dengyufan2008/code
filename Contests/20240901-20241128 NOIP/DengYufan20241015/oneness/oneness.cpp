// wrong algorithm
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("oneness.in");
ofstream cout("oneness.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
struct V {
  int d, w, c, p[kMaxL];
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, l, r, lg[kMaxN];

int F(int x, int y) {
  for (int i = lg[y]; i >= 0; i--) {
    if (y >> i & 1) {
      x = v[x].p[i];
    }
  }
  return x;
}

void T(int x) {
  for (int i : v[x].e) {
    if (!v[i].b) {
      v[i].d = v[x].d + 1, T(i);
    }
  }
}

void Init() {
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      v[j].p[i] = v[v[j].p[i - 1]].p[i - 1];
    }
  }
  for (int i = 1; i <= n; i++) {
    v[F(i, n)].b = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].b) {
      T(i);
      if (!v[i].c) {
        int c = 1;
        for (int j = v[i].p[0]; j != i; j = v[j].p[0]) {
          c++;
        }
        int w = v[i].w = c - 1;
        v[i].c = c;
        for (int j = v[i].p[0]; j != i; j = v[j].p[0]) {
          v[j].w = --w, v[j].c = c;
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  lg[0] = -1;
  for (int i = 1; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n >> l >> r;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].p[0], v[v[i].p[0]].e.push_back(i);
  }
  Init();
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    int xs = F(x, v[x].d), ys = F(y, v[y].d);
    if (F(xs, v[xs].w) != F(ys, v[ys].w)) {
      cout << -1 << '\n';
      continue;
    } else if (!v[y].b && (v[x].d < v[y].d || F(x, v[x].d - v[y].d) != y)) {
      cout << -1 << '\n';
      continue;
    }
    if (v[y].b) {
      int c = v[xs].c, d = v[x].d + (v[xs].w - v[ys].w + c) % c;
      long long shit1 = d + r - 1, shit2 = d;
      long long shit3 = -d + c - 1, shit4 = -d;
      bool o = 1;
      for (int j = 0; j < 350; j++) {  // here
        if (shit1 / r <= shit2 / l) {
          cout << shit1 / r << '\n';
          o = 0;
          break;
        } else if (shit4 >= 0 && shit3 / c <= shit4 / c) {
          cout << (d + shit3 / c * c + r - 1) / r << '\n';
          o = 0;
          break;
        }
        shit1 += c, shit2 += c, shit3 += l, shit4 += r;
      }
      if (o) {
        cout << -1 << '\n';
      }
    } else {
      int d = v[x].d - v[y].d;
      if (!(d % r) || d / l > d / r) {
        cout << (d + r - 1) / r << '\n';
      } else {
        cout << -1 << '\n';
      }
    }
  }
  return 0;
}
