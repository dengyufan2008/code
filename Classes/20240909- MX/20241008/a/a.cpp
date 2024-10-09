#include <fstream>
#include <queue>
#define LL long long
#define PLI pair<LL, int>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 10;
int n, m;
LL ans;
priority_queue<PLI, vector<PLI>, greater<PLI>> q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    static LL x;
    cin >> x, q.push({x, 0});
  }
  for (int i = (n + m - 3) / (m - 1) * (m - 1); i >= n; i--) {
    q.push({0, 0});
  }
  for (int i = (n + m - 3) / (m - 1); i >= 1; i--) {
    LL s = 0;
    int d = 0;
    for (int j = 1; j <= m; j++) {
      s += q.top().first, d = max(d, q.top().second), q.pop();
    }
    ans += s, q.push({s, d + 1});
  }
  cout << ans << '\n' << q.top().second << '\n';
  return 0;
}
