#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e5 + 1;
int n, m, a[kMaxN];

int S(int w, vector<int> &s) {
  if (w == n) {
    for (int i = 1; i <= n - s.size(); i++) {
      cout << 1 << ' ';
    }
    for (int i = 0; i < s.size(); i++) {
      cout << s[i] << ' ';
      s[i] = n - s.size() + i;
    }
    cout << '\n';
    return 1;
  }
  int m = n - w + 1;
  if (a[m - 1] - a[m] == 1) {
    int d = S(w + 1, s);
    if (d) {
      cout << d << '\n';
      return d + 1;
    }
    return 0;
  }
  vector<int> t, pre, suf = s;
  for (int i : s) {
    pre.push_back(i), suf.erase(suf.begin());
    for (int j = 2; j * j <= i; j++) {
      if (!(i % j) && a[m] - i + j + i / j == a[m - 1]) {
        t = pre, t.pop_back(), t.push_back(j), t.push_back(i / j);
        t.insert(t.end(), suf.begin(), suf.end());
        int d = S(w + 1, t);
        if (d) {
          cout << t[pre.size()] << '\n';
          for (int k = 0; k < pre.size(); k++) {
            s[k] = t[k];
          }
          for (int k = pre.size(); k < s.size();k ++) {
            s[k] = t[k + 1];
          }
          return d;
        }
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i - 1] - a[i] > 1) {
      cout << -1 << '\n';
      return 0;
    }
  }
  vector<int> s = {a[n]};
  if (!S(1, s)) {
    cout << -1 << '\n';
  }
  return 0;
}
