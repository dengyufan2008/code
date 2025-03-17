#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 1;
int n, m, a[kMaxN], b[kMaxN], pa[kMaxN], pb[kMaxN];
vector<int> l;

int W(int x, int y) {
  return a[x] > b[y] ? pa[x] + y : x + pb[y];
}

bool Check(int x1, int y1, int x2, int y2) {
  if ((a[x1] > b[y1]) == (a[x2] > b[y2])) {
    if (a[x1] > b[y1]) {
      return y1 == y2 && max(pa[x1], pa[x2]) <= min(x1, x2);
    } else {
      return x1 == x2 && max(pb[y1], pb[y2]) <= min(y1, y2);
    }
  } else {  // 平面图只需判端点相交
    return x1 == x2 && y1 == y2;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    for (; !l.empty() && a[l.back()] > a[i]; l.pop_back()) {
    }
    pa[i] = l.empty() ? 0 : l.back();
    l.push_back(i);
  }
  l.clear();
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    for (; !l.empty() && b[l.back()] > b[i]; l.pop_back()) {
    }
    pb[i] = l.empty() ? 0 : l.back();
    l.push_back(i);
  }
  l.clear();
  cin >> m;
  for (int i = 1, x1, y1, x2, y2; i <= m; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    int ans = 0;
    for (;;) {
      if (W(x1, y1) < W(x2, y2)) {
        swap(x1, x2), swap(y1, y2);
      }
      if (Check(x1, y1, x2, y2)) {
        ans += abs(x1 - x2) + abs(y1 - y2);
        break;
      } else if (a[x1] > b[y1]) {
        ans += x1 - pa[x1], x1 = pa[x1];
      } else {
        ans += y1 - pb[y1], y1 = pb[y1];
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
