#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ifstream cout("b.out");
ofstream cans("b.ans");

const int kMaxN = 5e5 + 1;
int n, s, t, a[kMaxN], b[kMaxN], c[kMaxN], d[kMaxN];
vector<pair<int, int>> les, mor, wro;

int R(int x, int y) { return (x - 1) * s + y; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s >> t;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= s; j++) {
      cin >> a[R(i, j)];
      cout >> b[R(i, j)];
      c[a[R(i, j)]]++;
    }
    int _a[kMaxN], _b[kMaxN];
    copy(a + R(i, 1), a + R(i, s) + 1, _a);
    copy(b + R(i, 1), b + R(i, s) + 1, _b);
    sort(_a, _a + s);
    sort(_b, _b + s);
    for (int j = 0; j < s; j++) {
      if (_a[j] != _b[j]) {
        if (_a[j] < _b[j]) {
          les.push_back({i, _a[j]});
        } else {
          mor.push_back({i, _b[j]});
        }
      }
    }
  }
  for (int i = 1; i <= s; i++) {
    for (int j = 1; j <= n; j++) {
      d[b[R(j, i)]] = 0;
    }
    for (int j = 1; j <= n; j++) {
      d[b[R(j, i)]]++;
    }
    for (int j = 1; j <= n; j++) {
      if (d[b[R(j, i)]] != c[b[R(j, i)]] / s && (!(c[b[R(j, i)]] % s) || d[b[R(j, i)]] != c[b[R(j, i)]] / s + 1)) {
        wro.push_back({i, b[R(j, i)]});
      }
    }
  }
  if (!les.empty()) {
    cans << "Less:\n";
    sort(les.begin(), les.end());
    les.resize(unique(les.begin(), les.end()) - les.begin());
    for (auto i : les) {
      cans << i.first << ' ' << i.second << '\n';
    }
  }
  if (!mor.empty()) {
    cans << "More:\n";
    sort(mor.begin(), mor.end());
    mor.resize(unique(mor.begin(), mor.end()) - mor.begin());
    for (auto i : mor) {
      cans << i.first << ' ' << i.second << '\n';
    }
  }
  if (!wro.empty()) {
    cans << "Wrong Num\n";
    sort(wro.begin(), wro.end());
    wro.resize(unique(wro.begin(), wro.end()) - wro.begin());
    for (auto i : wro) {
      cans << i.first << ' ' << i.second << '\n';
    }
  }
  if (les.empty() && mor.empty() && wro.empty()) {
    cans << "Accepted\n";
  }
  return 0;
}
