#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 31, kMaxM = 21, kMod = 998244353;
int n, m, o, a[kMaxN], b[kMaxN], u[kMaxN];
LL ans[kMaxN];
priority_queue<int, vector<int>, greater<int>> q;

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void S(int x) {
  if (x > n) {
    int w = 0, k = 0;
    for (int i = 1; i <= n; i++) {
      while (!q.empty() && w + q.top() <= b[i]) {
        w += q.top(), q.pop(), k++, Update(ans[k], w);
      }
      if (!q.empty()) {
        int x = q.top();
        q.pop(), q.push(x - b[i] + w);
      }
      w = b[i], q.push(a[i]);
    }
    while (!q.empty()) {
      w += q.top(), q.pop(), k++, Update(ans[k], w);
    }
    return;
  }
  for (int i = 1; i <= m; i++) {
    a[x] = i, S(x + 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  cin >> o;
  for (int i = 1; i <= o; i++) {
    cin >> u[i];
  }
  sort(b + 1, b + n + 1), S(1);
  for (int i = 1; i <= o; i++) {
    cout << ans[u[i]] << '\n';
  }
  return 0;
}
