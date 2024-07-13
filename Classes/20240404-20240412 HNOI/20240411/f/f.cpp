#include <fstream>
#include <vector>

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 1e5 + 1, kMaxV = 16, kInf = 1e9;
int n, w[kMaxN], c[kMaxV], f[1 << kMaxV], pop[1 << kMaxV];
vector<int> v[1 << kMaxV];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int s = 1; s < 1 << kMaxV; s++) {
    int o = 0;
    for (int i = 0; i < kMaxV; i++) {
      if (s >> i & 1) {
        o ^= i;
      }
    }
    if (!o) {
      for (int t = s; t < 1 << kMaxV; t = t + 1 | s) {
        v[t].push_back(s);
      }
    }
    pop[s] = pop[s ^ (s & -s)] + 1;
  }
  cin >> n;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    w[x + 1] ^= z, w[y + 1] ^= z;
  }
  for (int i = 1; i <= n; i++) {
    f[0] += w[i] && c[w[i]], c[w[i]] ^= 1;
  }
  fill(&f[1], &f[1 << kMaxV], kInf);
  for (int s = 1; s < 1 << kMaxV; s++) {
    for (int t : v[s]) {
      f[s] = min(f[s], f[s ^ t] + pop[t] - 1);
    }
  }
  for (int i = 0, s = 0; i < kMaxV; i++) {
    c[i] && (s |= 1 << i);
    if (i == kMaxV - 1) {
      cout << f[s] << '\n';
    }
  }
  return 0;
}
