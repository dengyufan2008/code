#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxL = 60;
const LL kBase = ~((LL)-1 << kMaxL);
struct V {
  LL w, h, l;
  V operator+(const V &v) const {
    return {w, (((h ^ v.h ^ (l | v.l)) & (h ^ v.h)) | (l & v.l & (h ^ v.h ^ kBase))), ((l ^ v.l) & (h ^ v.h ^ kBase)) | (h & v.h)};
  }
} v, p[kMaxL];
int n;
LL ans;

void Insert() {
  for (int j = kMaxL - 1; j >= 0; j--) {
    if ((v.h >> j & 1) || (v.l >> j & 1)) {
      if ((p[j].h >> j & 1) || (p[j].l >> j & 1)) {
        if (p[j].w < v.w) {
          ans += v.w - p[j].w, swap(p[j], v);
        }
        if ((v.h >> j & 1) ^ (p[j].h >> j & 1)) {
          v = v + p[j];
        } else {
          v = v + p[j] + p[j];
        }
      } else {
        ans += v.w, p[j] = v;
        break;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v.l >> v.w;
    v.h = 0, v.l ^= ans, Insert();
    cout << ans << '\n';
  }
  return 0;
}
