#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxN = 1e5 + 1;
struct E {
  int a, h;
} e[kMaxN];
int n, d;

void Print(LLL x) {
  if (x > 9) {
    Print(x / 10);
  }
  putchar(x % 10 + 48);
}

namespace Sub1 {
LLL Exgcd(LLL n, LLL a, LLL b, LLL c) {
  if (!a) {
    return 0;
  }
  LLL g = (a * n + b) / c;
  LLL ans = g * (n + 1) - c / a * g * (g + 1) / 2;
  b = a - b - 1;
  if (b < 0) {
    LLL t = -(b - a + 1) / a;
    b += a * t, ans += g * t;
  }
  return ans - Exgcd(g, c % a, b, a);
}

int main() {
  LLL ans = Exgcd(e[1].a, e[1].h, d - 1, d) - e[1].a;
  Print(ans), putchar(10);
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
LLL ans;
vector<pair<int, int>> v[kMaxN];

int main() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= (e[i].a * e[i].h + d - 1) / d; j++) {
      int c = 1, w = min(j * d, e[i].a * e[i].h) / e[i].h - (j - 1) * d / e[i].h;
      for (; !v[i].empty() && 1LL * v[i].back().second * c < 1LL * v[i].back().first * w; v[i].pop_back()) {
        ans += 1LL * v[i].back().first * w;
        c += v[i].back().first, w += v[i].back().second;
      }
      v[i].push_back({c, w});
    }
    v[0].insert(v[0].end(), v[i].begin(), v[i].end());
  }
  sort(v[0].begin(), v[0].end(), [](pair<int, int> i, pair<int, int> j) {
    return i.second * j.first > j.second * i.first;
  });
  for (; v[0].size() > 1;) {
    int c = v[0].back().first, w = v[0].back().second;
    v[0].pop_back();
    ans += 1LL * v[0].back().first * w;
    v[0].back().first += c, v[0].back().second += w;
  }
  Print(ans), putchar(10);
  return 0;
}
}  // namespace Sub2

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> d;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].h;
  }
  if (n == 1) {
    return Sub1::main();
  } else {
    return Sub2::main();
  }
}
