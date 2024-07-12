#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("happy.in");
ofstream cout("happy.out");

const int kMaxN = 1e7 + 1;
int n, m, k, p, q, w, a[kMaxN], b[kMaxN];
bool c[kMaxN];
unsigned seed;
LL ans;
vector<int> v[kMaxN];

unsigned Rand() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> seed;
  for (int i = 1; i <= n; i++) {
    a[i] = 1, b[i] = Rand() % m + 1;
  }
  for (int i = 1; i <= n - 2; ++i) {
    a[Rand() % n + 1]++;
  }
  for (int i = 1; i <= n; i++) {
    v[b[i]].push_back(a[i]);
  }
  for (int i = m, t = 0; i >= 1; i--) {
    for (int j : v[i]) {
      t++, a[t] = j, b[t] = i;
    }
  }
  p = q = 1;
  for (int i = 1; i <= n; i++) {
    for (; q < i && (!a[q] || !c[q]); q++) {
    }
    for (; a[i];) {
      for (; p < q && (!a[p] || c[p]); p++) {
      }
      if (p < q && (a[i] > 1 || k == n - 2)) {
        a[i]--, a[p]--, k++, ans += 1LL * b[i] * b[p];
      } else {
        break;
      }
    }
    bool o = 0;
    if (a[i] && q < i) {
      a[i]--, a[q]--, k++, ans += 1LL * b[i] * b[q], w--, o = 1;
    }
    for (; a[i];) {
      for (; p < i && (!a[p] || c[p]); p++) {
      }
      if (p < i && (a[i] > 1 || o || k == n - 2)) {
        a[i]--, a[p]--, k++, ans += 1LL * b[i] * b[p];
      } else {
        break;
      }
    }
    if (o) {
      w += a[i], c[i] = 1;
      if (w == 1) {
        for (; q < i && (!a[q] || !c[q]); q++) {
        }
        w = c[q] = 0;
      }
    } else if (a[i] > 1) {
      w = a[i], c[i] = 1;
    }
  }
  cout << ans << '\n';
  return 0;
}
