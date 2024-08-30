// P5853
#include <fstream>

using namespace std;

ifstream cin("sum.in");
ofstream cout("sum.out");

const int kN = 300, kMaxM = kN * (kN - 1) / 2 + 1;
int n, k, p, f[kMaxM], ans[kMaxM];

inline void Add(int &x, int y) { x += y, x >= p && (x -= p); }
inline void Del(int &x, int y) { x -= y, x < 0 && (x += p); }

void Add(int x) {
  for (int i = 1; i <= k; i++) {
    Add(f[i], f[i - 1]);
  }
  for (int i = k; i >= x; i--) {
    Del(f[i], f[i - x]);
  }
}

void Del(int x) {
  for (int i = k; i >= 1; i--) {
    Del(f[i], f[i - 1]);
  }
  for (int i = x; i <= k; i++) {
    Add(f[i], f[i - x]);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k >> p, f[0] = 1;
  for (int i = 1; i < n; i++) {
    Add(i + 1);
  }
  ans[1] = f[k];
  for (int i = 1; i < n; i++) {
    Del(i + 1), Add(ans[i + 1], f[k]);
    if (i <= k) {
      Add(ans[1], f[k - i]), Del(ans[n - i + 1], f[k - i]);
    }
    Add(i + 1);
  }
  for (int i = 1; i <= n; i++) {
    Add(ans[i], ans[i - 1]);
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
