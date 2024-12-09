#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("cover.in");
ofstream cout("cover.out");

const int kMaxN = 1e5 + 1;
struct V {
  int l, r;
  LL w;
} vl[kMaxN], vr[kMaxN];
int n, m, k, a[kMaxN << 1 | 1];
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> a[n * 2 + 2] >> m;
  for (int i = 1, l, r, w; i <= n; i++) {
    cin >> l >> r >> w, ans += w;
    a[i << 1] = l, a[i << 1 | 1] = r;
    vl[i] = vr[i] = {l, r, w};
  }
  sort(a + 1, a + n * 2 + 3);
  k = unique(a + 1, a + n * 2 + 3) - a - 1;
  sort(vl + 1, vl + n + 1, [](V i, V j) {
    return i.l < j.l;
  });
  sort(vr + 1, vr + n + 1, [](V i, V j) {
    return i.r < j.r;
  });
  for (int i = 1; i <= n; i++) {
    vl[i].w += vl[i - 1].w, vr[i].w += vr[i - 1].w;
  }
  for (int i = 1; i <= k; i++) {
    int j = lower_bound(a + 1, a + k + 1, a[i] + m) - a;
    if (j <= k) {
      int l = lower_bound(vl + 1, vl + n + 1, V{a[j], 0, 0}, [](V i, V j) {
                return i.l < j.l;
              }) -
              vl - 1;
      int r = upper_bound(vr + 1, vr + n + 1, V{0, a[i], 0}, [](V i, V j) {
                return i.r < j.r;
              }) -
              vr - 1;
      ans = min(ans, vl[l].w - vr[r].w);
    }
  }
  cout << ans << '\n';
  return 0;
}
