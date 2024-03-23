#include <fstream>

using namespace std;

ifstream cin("dingdingcar.in");
ofstream cout("dingdingcar.out");

const int kMaxN = 12001;
int n, m, ans, l[kMaxN], r[kMaxN];

int Init(int *a) {
  int n, m = 0, b[kMaxN];
  string s;
  cin >> s;
  n = s.size();
  for (int i = 0; i < n; i++) {
    b[i] = s[n - i - 1] - '0';
  }
  for (int &i = m; n; i++) {
    for (int j = 0, w = 1; j < n; j++) {
      a[i] = (a[i] + b[j] * w) % 7;
      w = w * 3 % 7;
    }
    for (int j = n - 1, w = 0; j >= 0; j--) {
      w = w * 10 + b[j];
      b[j] = w / 7, w %= 7;
    }
    !b[n - 1] && n--;
  }
  return m;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(l), m = Init(r);
  for (int i = 0, w = 0; i < m; i++) {
    w = (r[i] * 2 + w) / 7, ans += w;
  }
  for (int i = m - 1; i >= 0; i--) {
    if (l[i] != r[i]) {
      n = i;
      break;
    }
  }
  for (int i = 1, c; i <= n; i++) {
    c = i, r[i]--;
    for (int j = i, w = 1; j < m; j++) {
      w = (r[j] * 2 + w) / 7, c += w;
    }
    r[i]++, ans = max(ans, c);
  }
  cout << ans << '\n';
  return 0;
}
