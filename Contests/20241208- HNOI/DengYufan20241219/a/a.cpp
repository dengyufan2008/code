#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMaxL = 72;
struct V {
  int d, f, l, s[2];
  LL w, mn[kMaxL], mx[kMaxL];
  bool ans;
} v[kMaxN];
int n, m, u;

void Pushup(int x) {
  int l = v[x].s[0], r = v[x].s[1];
  v[x].mn[0] = v[x].mx[0] = v[x].w = v[l].w + v[r].w;
  v[x].ans = v[l].ans && v[r].ans;
  for (int i = 0; i < v[l].l && i < v[r].l; i++) {
    v[x].mn[i + 1] = min(v[l].mn[i], v[r].mn[i]);
    v[x].mx[i + 1] = max(v[l].mx[i], v[r].mx[i]);
  }
  if (v[l].l < v[r].l) {
    for (int i = v[l].l; i < v[r].l; i++) {
      v[x].mn[i + 1] = v[r].mn[i];
      v[x].mx[i + 1] = v[r].mx[i];
    }
  } else {
    for (int i = v[r].l; i < v[l].l; i++) {
      v[x].mn[i + 1] = v[l].mn[i];
      v[x].mx[i + 1] = v[l].mx[i];
    }
  }
  if (v[x].ans) {
    bool le = 1, ge = 1;
    for (int i = 0; i < v[l].l && i < v[r].l; i++) {
      le &= v[l].mx[i] <= v[r].mn[i];
      ge &= v[l].mn[i] >= v[r].mx[i];
    }
    v[x].ans &= le || ge;
  }
}

void T(int x) {
  v[x].d = v[v[x].f].d + 1;
  if (x > n) {
    T(v[x].s[0]), T(v[x].s[1]);
    v[x].l = max(v[v[x].s[0]].l, v[v[x].s[1]].l) + 1;
    if (v[x].l > kMaxL) {
      for (int i = 1; i <= m; i++) {
        cout << "NO\n";
      }
      exit(0);
    }
    Pushup(x);
  } else {
    v[x].l = 1;
    v[x].mn[0] = v[x].mx[0] = v[x].w, v[x].ans = 1;
  }
}

bool Check() {
  for (int i = 1; i < v[u].l; i++) {
    if (v[u].mn[i - 1] < v[u].mx[i]) {
      return 0;
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, u = (n << 1) - 1;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = n + 1; i < n << 1; i++) {
    cin >> v[i].s[0] >> v[i].s[1];
    v[v[i].s[0]].f = v[v[i].s[1]].f = i;
  }
  T(u);
  cout << (v[u].ans && Check() ? "YES\n" : "NO\n");
  for (int i = 1, x; i < m; i++) {
    cin >> x >> v[x].w;
    v[x].mn[0] = v[x].mx[0] = v[x].w;
    for (int j = v[x].f; j; j = v[j].f) {
      Pushup(j);
    }
    cout << (v[u].ans && Check() ? "YES\n" : "NO\n");
  }
  return 0;
}
