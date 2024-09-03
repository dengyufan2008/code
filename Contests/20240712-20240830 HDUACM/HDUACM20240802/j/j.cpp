#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 2e5 + 1, kMaxL = 18;
struct V {
  int p, w, f[kMaxL];
  bool b;
  vector<int> e;
} v[kMaxN];
int t, n, w;
LL ans;

int FindMax(int x) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (!v[v[x].f[i]].b) {
      x = v[x].f[i];
    }
  }
  return x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    v[0].e.clear(), v[0].b = 0;
    cin >> n >> v[0].p >> v[0].w;
    for (int i = 1, o, x, y; i <= n; i++) {
      cin >> o >> x;
      if (o == 1) {
        cin >> y >> v[x].p >> v[x].w;
        v[x].e.clear(), v[x].b = 0, v[x].f[0] = y;
        for (int j = 1; j < kMaxL; j++) {
          v[x].f[j] = v[v[x].f[j - 1]].f[j - 1];
        }
      } else if (o == 2) {
        cin >> y;
        w = ans = 0;
        while (!v[x].b) {
          int z = FindMax(x);
          if (v[z].w <= y - w) {
            ans += 1LL * v[z].p * v[z].w, v[z].b = 1, w += v[z].w;
          } else {
            ans += 1LL * v[z].p * (y - w), v[z].w -= y - w, w = y;
            break;
          }
        }
        cout << w << ' ' << ans << '\n';
      } else {
        v[x].w = 0;
      }
    }
  }
  return 0;
}
