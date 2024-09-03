#include <fstream>
#include <unordered_map>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 1e7 + 1;
int o, n, m, s[kMaxN];
LL ans, t[kMaxN];
bool b[kMaxN];
vector<int> v;
unordered_map<int, int> ans1;
unordered_map<int, LL> ans2;

int Calc1(int n) {
  if (n < kMaxN) {
    return s[n];
  } else if (ans1.count(n)) {
    return ans1[n];
  }
  int ans = 1;
  for (int l = 2, r; l <= n; l = r + 1) {
    r = min(n / (n / l), n);
    ans -= 1LL * (r - l + 1) * Calc1(n / l);
  }
  return ans1[n] = ans;
}

LL Calc2(int n) {
  if (n < kMaxN) {
    return t[n];
  } else if (ans2.count(n)) {
    return ans2[n];
  }
  LL ans = 1;
  for (int l = 2, r; l <= n; l = r + 1) {
    r = min(n / (n / l), n);
    ans -= 1LL * (l + r) * (r - l + 1) / 2 * Calc2(n / l);
  }
  return ans2[n] = ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  b[1] = s[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      v.push_back(i), s[i] = -1;
    }
    for (int j : v) {
      int x = i * j;
      if (x < kMaxN) {
        b[x] = 1, s[x] = -s[i];
        if (!(i % j)) {
          s[x] = 0;
          break;
        }
      } else {
        break;
      }
    }
  }
  for (int i = 1; i < kMaxN; i++) {
    t[i] = t[i - 1] + s[i] * i;
    s[i] += s[i - 1];
  }
  cin >> o;
  while (o--) {
    cin >> n >> m;
    ans = 1LL * m * Calc1(n), n = min(n, m);
    for (int l = 1, r; l <= n; l = r + 1) {
      r = min(m / (m / l), n);
      ans -= (m / l) * (Calc2(r) - Calc2(l - 1));
    }
    cout << ans << '\n';
  }
  return 0;
}
