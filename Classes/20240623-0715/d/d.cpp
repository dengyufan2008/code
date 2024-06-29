#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int n, m, a[kMaxN], c[kMaxN], d[kMaxN], q[kMaxN];
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  ans = 1, cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], d[a[i]]++;
  }
  for (int i = 1; i <= n; i++) {
    c[i] = d[i], !d[i] ? q[++m] = i : 0;
  }
  for (int i = 1, x; i <= m; i++) {
    x = q[i], ans = ans * (c[x] + 1) % kMod;  // 计算 深度>2 的点的贡献
    !--d[a[x]] ? q[++m] = a[x] : 0;
  }
  for (int i = 1, j, p; i <= n; i++) {
    if (d[i]) {
      LL w = c[i], s = c[i] + 1;  // 计算一个太阳图
      for (j = a[i]; j != i; j = a[j]) {
        d[j] = 0, w = (w + c[j]) % kMod, s = s * (c[j] + 1) % kMod;
      }
      ans = ans * (s - w + kMod) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
