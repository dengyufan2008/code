#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kInf = 1e9;
struct V {
  int x, y, o;
} v[kMaxN];
int n, m, ans;
char c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {  // 旋转坐标系
    cin >> v[i].x >> v[i].y >> c;
    v[i].y += v[i].x << 1;
    v[i].x = v[i].y - (v[i].x << 2);
    v[i].o = (c == 'P') - (c == 'N');
  }
  sort(v + 1, v + n + 1, [](V i, V j) {
    return i.x < j.x || i.x == j.x && i.y < j.y;
  });
  for (int i = 1, j = kInf; i <= n; i++) {  // 删去被 N 覆盖的点
    if (v[i].o == -1) {
      j = min(j, v[i].y);
    } else if (v[i].y < j) {
      v[++m] = v[i];
    } else if (v[i].o == 1) {
      cout << "impossible\n";
      return 0;
    }
  }
  n = m, m = 0, reverse(v + 1, v + n + 1);
  for (int i = 1, j = -kInf; i <= n; i++) {  // 删去覆盖了 P 的点
    if (v[i].y > j) {
      v[++m] = v[i];
      if (v[i].o == 1) {
        j = v[i].y;
      }
    }
  }
  n = m, m = 0;
  for (int i = 1, p = -kInf, j = -kInf; i <= n; i++) {  // 选一个点覆盖的是一个区间, 故贪心地选
    j = max(j, v[i].y);
    if (v[i].o == 1 && v[i].y > p) {
      p = j, ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}
