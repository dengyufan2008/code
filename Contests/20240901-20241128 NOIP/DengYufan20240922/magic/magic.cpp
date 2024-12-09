#include <fstream>
#include <queue>
#define PII pair<int, int>

using namespace std;

ifstream cin("magic.in");
ofstream cout("magic.out");

const int kMaxN = 1e6 + 1;
int t, n, m, a[kMaxN], nt[kMaxN], lt[kMaxN], d[kMaxN];
bool b[kMaxN], c[kMaxN];
priority_queue<PII, vector<PII>, greater<PII>> q1, q2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    fill(&b[1], &b[n] + 1, 0);
    fill(&c[1], &c[n] + 1, 0);
    fill(&d[1], &d[m] + 1, 0);
    while (!q1.empty()) {
      q1.pop();
    }
    while (!q2.empty()) {
      q2.pop();
    }
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = n; i >= 1; i--) {
      nt[i] = d[a[i]], d[a[i]] = i;
      !nt[i] && (nt[i] = n + 1, lt[a[i]] = i);
    }
    for (int i = 1; i <= m; i++) {
      c[lt[i]] = 1;
    }
    for (int o = 1, i = 1, j = 1; o <= m; o++) {
      for (; !c[j - 1]; j++) {
        !b[a[j]] ? q1.push({a[j], j}) : void();
      }
      int x = q1.top().second;
      cout << a[x] << " \n"[o == m];
      b[a[x]] = 1, c[lt[a[x]]] = 0;
      for (; i < x; i++) {
        !b[a[i]] ? q2.push({a[i], i}) : void();
      }
      for (int k = i; k < j; k = nt[k]) {
        q2.push({a[k], k});
      }
      while (!q2.empty() && q1.top() == q2.top()) {
        q1.pop(), q2.pop();
      }
    }
  }
  return 0;
}
