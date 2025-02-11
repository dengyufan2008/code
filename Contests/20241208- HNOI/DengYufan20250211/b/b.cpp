#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 3001, kMod = 1e9 + 7;
const int kC[4][4] = {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}};
int n, m, t, s[kMaxN], a[kMaxN];
bool b[kMaxN];
LL ans, f[kMaxN][kMaxN * 3][3];  // 考虑完了 >= i 的位, 选了 j 个数, 后面应当进 k 位到 i

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void Dp(int x) {
  for (; t >= 0; t--) {
    for (int i = 0; i <= s[t]; i++) {
      for (int j = 0; j < 3; j++) {
        f[t][i][j] = 0;
        for (int k = b[t] - j & 1; k <= a[t] && k <= i; k += 2) {
          Update(f[t][i][j], f[t + 1][i - k][j + k >> 1] * kC[a[t]][k]);
        }
      }
    }
  }
  Update(ans, f[0][x][0]);
}

void Add() {
  for (t = 0; t < m && b[t]; t++) {
  }
  b[t] = 1, t == m && (m++, f[m][0][0] = 1);
  for (int i = 0; i < t; i++) {
    b[i] = 0;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, f[m][0][0] = 1;
  for (int i = 0; i < m; i++) {
    static char c;
    cin >> c, b[i] = c == '1';
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  s[n] = a[n];
  for (int i = n - 1; i >= 0; i--) {
    s[i] = s[i + 1] + a[i];
  }
  t = m - 1;
  for (int i = 0; i <= s[1]; i++) {
    Dp(i), Add();
  }
  cout << ans << '\n';
  return 0;
}
