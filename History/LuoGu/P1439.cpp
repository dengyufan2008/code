#include <iostream>
#define LL long long

using namespace std;

int n, ans, a[100001], b[100001], d[100001], f[100001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    d[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  fill(&f[1], &f[100000] + 1, 1919810);
  for (int i = 1; i <= n; i++) {
    if (d[b[i]] > f[ans]) {
      f[++ans] = d[b[i]];
    } else {
      int l = 0, r = ans, mid;
      while (l <= r) {
        mid = (l + r) >> 1;
        if (f[mid] <= d[b[i]]) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      f[l] = min(d[b[i]], f[l]);
    }
  }
  cout << ans << endl;
  return 0;
}
