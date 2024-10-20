#include <fstream>
#include <vector>

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const int kMaxN = 1e6 + 1;
struct V {
  int w, p, s, c;
  vector<int> e;
} v[kMaxN];
int n, d[kMaxN], c[kMaxN];
long long ans;

void T(int x) {
  v[x].p = d[v[x].w], d[v[x].w] = x, v[x].s = 1;
  for (int i : v[x].e) {
    T(i), v[x].s += v[i].s;
  }
  d[v[x].w] = v[x].p, v[x].c = v[x].s;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2, x; i <= n; i++) {
    cin >> x >> v[i].w, v[x].e.push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    d[i] = 1, c[i] = n;
  }
  T(1);
  for (int i = 2; i <= n; i++) {
    if (v[i].p == 1) {
      c[v[i].w] -= v[i].s;
    } else {
      v[v[i].p].c -= v[i].s;
    }
  }
  for (int i = 2; i <= n; i++) {
    ans += 1LL * v[i].c * (n - v[i].s);
    if (v[i].p == 1) {
      ans += 1LL * v[i].s * c[v[i].w];
    } else {
      ans += 1LL * v[i].s * v[v[i].p].c;
    }
  }
  ans >>= 1, cout << ans << '\n';
  return 0;
}
