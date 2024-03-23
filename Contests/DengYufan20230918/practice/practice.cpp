#include <fstream>
#define LL long long

using namespace std;

ifstream cin("practice.in");
ofstream cout("practice.out");

LL n, dl, dr, hl, hr, w, ans;

LL Calc1(LL l, LL r) {
  return l <= r ? (r - l + 1) * (hr - hl + 1) : 0;
}

LL Calc2(LL l, LL r) {
  return l <= r ? (r - l + 1) * (hr + 1) - (l + r) * (r - l + 1) / 2 : 0;
}

LL Calc3(LL l, LL r) {
  return l <= r ? -(r - l + 1) * hl + (l + r) * (r - l + 1) / 2 + (l / w == r / w ? (r - l + 1) * (l / w * w) : (l / w * w + w - l) * (l / w * w) + (r - r / w * w + 1) * (r / w * w) + (l / w * w + r / w * w) * (r / w - l / w - 1) / 2 * w) : 0;
}

LL Calc4(LL l, LL r) {
  return l <= r ? (l / w == r / w ? (r - l + 1) * (l / w * w) : (l / w * w + w - l) * (l / w * w) + (r - r / w * w + 1) * (r / w * w) + (l / w * w + r / w * w) * (r / w - l / w - 1) / 2 * w) : 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> dl >> dr >> hl >> hr >> w;
    ans = 0;
    if ((hr + 1) / w & 1) {
      ans += Calc1(max(dl, (hr + 1) / (2 * w) * w + w), min(dr, hl));
      ans += Calc2(max(dl, max(hl + 1, (hr + 1) / (2 * w) * w + w)), min(dr, hr + 1));
      if (hl / w & 1) {
        ans += Calc3(max(dl, hl / (2 * w) * w + w), min(dr, min(hl, (hr + 1) / (2 * w) * w + w - 1)));
      } else {
        ans += Calc3(max(dl, hl / (2 * w) * w + hl % (2 * w)), min(dr, min(hl, (hr + 1) / (2 * w) * w + w - 1)));
      }
      ans += Calc4(max(dl, hl + 1), min(dr, (hr + 1) / (2 * w) * w + w - 1));
    } else {
      ans += Calc1(max(dl, (hr + 1) / (2 * w) * w + (hr + 1) % (2 * w)), min(dr, hl));
      ans += Calc2(max(dl, max(hl + 1, (hr + 1) / (2 * w) * w + (hr + 1) % (2 * w))), min(dr, hr + 1));
      if (hl / w & 1) {
        ans += Calc3(max(dl, hl / (2 * w) * w + w), min(dr, min(hl, (hr + 1) / (2 * w) * w + (hr + 1) % (2 * w) - 1)));
      } else {
        ans += Calc3(max(dl, hl / (2 * w) * w + hl % (2 * w)), min(dr, min(hl, (hr + 1) / (2 * w) * w + (hr + 1) % (2 * w) - 1)));
      }
      ans += Calc4(max(dl, hl + 1), min(dr, (hr + 1) / (2 * w) * w + (hr + 1) % (2 * w) - 1));
    }
    cout << ans << '\n';
  }
  return 0;
}
