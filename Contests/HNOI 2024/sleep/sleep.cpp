#include <fstream>
#include <vector>

using namespace std;

ifstream cin("sleep.in");
ofstream cout("sleep.out");

const int kMaxN = 5e5 + 1;
struct V {
  int r, s;
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, d[kMaxN];

void Add(int x, int k) {
  for (int i = x; i <= n; i += i & -i) {
    d[i] += k;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

void T(int x) {
  static int k = 0;
  v[x].r = ++k, v[x].s = 1;
  for (int i : v[x].e) {
    T(i), v[x].s += v[i].s;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> v[i].b >> x;
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      v[i].e.push_back(y);
    }
  }
  T(1);
  for (int i = 1; i <= n; i++) {
    if (!v[i].b && !v[i].e.empty()) {
      Add(v[i].r, 1), Add(v[i].r + 1, -1);
    }
  }
  for (int i = 1, o, x; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      // if (!v[x].e.empty()) {
      //   if (!v[x].b) {
      //     Add(v[x].r, -1), Add(v[x].r + 1, 1), v[x].b = 1;
      //   } else {
      //     Add(v[x].r, 1), Add(v[x].r + 1, -1), v[x].b = 0;
      //   }
      // }
    } else {
      // cout << v[x].s - Ask(v[x].r + v[x].s - 1) + Ask(v[x].r - 1) << '\n';
      cout << v[x].s << '\n';
    }
  }
  return 0;
}
