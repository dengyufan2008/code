#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int n, m, k, l[26], p[26];
LL w[26], f[kMaxN * 2];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k >> s, m = s.size(), f[0] = 1;
  for (int i = 1; i <= m; i++) {
    int c = s[i - 1] - 'a';
    f[i] = (f[i - 1] * 2 - w[c] + kMod) % kMod;
    p[c] = i, w[c] = f[i - 1];
  }
  for (int i = 0; i < k; i++) {
    l[i] = i;
  }
  sort(l, l + k, [](int i, int j) {
    return p[i] < p[j];
  });
  for (int i = m + 1; i <= m + n; i++) {
    int c = l[(i - m - 1) % k];
    f[i] = (f[i - 1] * 2 - w[c] + kMod) % kMod;
    p[c] = i, w[c] = f[i - 1];
  }
  cout << f[m + n] << '\n';
  return 0;
}
