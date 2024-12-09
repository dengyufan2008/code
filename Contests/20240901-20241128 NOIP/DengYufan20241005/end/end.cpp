#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("end.in");
ofstream cout("end.out");

const int kMaxN = 21, kMaxT = 2e5 + 1;
const int kMaxP = 8, kPrime[8] = {2, 3, 5, 7, 11, 13, 17, 19};
struct Q {
  int n, o;
  LL m;
} q[kMaxT];
int t, c[kMaxP];
vector<LL> l, ans[kMaxT];

void S(int x, LL w) {
  if (x == kMaxP) {
    return l.push_back(w);
  }
  S(x + 1, w);
  for (int i = 1; i <= c[x]; i++) {
    w *= kPrime[x], S(x + 1, w);
  }
}

void CalcL(int n) {
  for (int i = 0; i < kMaxP; i++) {
    c[i] = 0;
    for (int j = n / kPrime[i]; j; j /= kPrime[i]) {
      c[i] += j;
    }
  }
  l.clear(), S(0, 1), sort(l.begin(), l.end());
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  CalcL(50), cout << l.size() << '\n';
  return 0;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> q[i].n >> q[i].m, q[i].o = i;
  }
  sort(q + 1, q + t + 1, [](Q i, Q j) {
    return i.n < j.n;
  });
  for (int i = 1, j = 1; i < kMaxN; i++) {
    CalcL(i);
    for (; j <= t && q[j].n == i; j++) {
      LL m = q[j].m;
      while (m) {
        LL p = *--upper_bound(l.begin(), l.end(), m);
        m -= p, ans[q[j].o].push_back(p);
      }
    }
  }
  for (int i = 1; i <= t; i++) {
    cout << ans[i].size() << '\n';
    for (int j = 0; j < ans[i].size(); j++) {
      cout << ans[i][j] << " \n"[j + 1 == ans[i].size()];
    }
  }
  return 0;
}
