#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct A {
  int x, y, z, o;
} a[kMaxN];
struct V {
  LL x, z;
} v[kMaxN << 2];
int n, m;
LL ans;
priority_queue<int> q;

void Change(int p, int l, int r, int o, int x, int z) {
  if (l == r) {
    v[p] = {x, z};
    return;
  }
  int mid = l + r >> 1;
  if (mid >= o) {
    Change(p << 1, l, mid, o, x, z);
  } else {
    Change(p << 1 | 1, mid + 1, r, o, x, z);
  }
  v[p].x = max(v[p << 1].x, v[p << 1 | 1].x - v[p << 1].z);
  v[p].z = v[p << 1].z + v[p << 1 | 1].z;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y >> a[i].z;
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.x < j.x || i.x == j.x && i.z > j.z;
  });
  for (int i = 1; i <= n; i++) {
    a[i].o = i;
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.y < j.y;
  });
  for (int i = 1; i <= m; i++) {
    q.push(a[i].o), Change(1, 1, n, a[i].o, a[i].x, a[i].z);
  }
  ans = a[m].y + v[1].x;
  for (int i = m + 1; i <= n; i++) {
    q.push(a[i].o), Change(1, 1, n, a[i].o, a[i].x, a[i].z);
    Change(1, 1, n, q.top(), 0, 0), q.pop();
    ans = min(ans, a[i].y + v[1].x);
  }
  cout << ans << '\n';
  return 0;
}
