#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 1e6 + 1;
struct V {
  int d, c;
  vector<int> e;
} v[kMaxN];
int n, l, ans, d[kMaxN];
queue<int> q;

int main() {
  cin >> n >> l;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
    v[x].c++, v[y].c++;
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].c == 1) {
      q.push(i), d[v[i].d = 1]++;
    }
  }
  for (; !q.empty(); q.pop()) {
    for (int i : v[q.front()].e) {
      if (!v[i].d && --v[i].c == 1) {
        q.push(i), d[v[i].d = v[q.front()].d + 1]++;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans += min(d[i], l << 1);
  }
  cout << ans << '\n';
  return 0;
}
