#include <algorithm>
#include <ctime>
#include <fstream>
#include <random>
#define LL long long

using namespace std;

ifstream cin("train.in");
ofstream cout("train.out");

const int kMaxN = 2e6 + 1;
struct E {
  int p, d;
} e[kMaxN];
struct V {
  int s = 1, et;
} v[kMaxN];
int n, s[kMaxN];
LL ans;

void T(int x) {
  if (!v[x].et) {
    return;
  }
  int o = 0, a = 0, b = 0;
  LL c;
  for (int i = v[x].et; i; i = e[i].p) {
    T(e[i].d), v[x].s += v[e[i].d].s;
  }
  for (int i = v[x].et; i; i = e[i].p) {
    s[++o] = v[e[i].d].s;
  }
  sort(s + 1, s + o + 1);
  for (int i = o; i >= 1; i--) {
    if (a > b) {
      swap(a, b);
    }
    a += s[i];
  }
  c = (LL)a * b, a = b = 0;
  for (int t = 0; t < 450; t++) {
    random_shuffle(s + o / 3 + 1, s + o + 1);
    for (int i = o; i >= 1; i--) {
      if (a > b) {
        swap(a, b);
      }
      a += s[i];
    }
    c = max(c, (LL)a * b), a = b = 0;
  }
  ans += c;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2, x; i <= n; i++) {
    cin >> x;
    e[i] = {v[x].et, i}, v[x].et = i;
  }
  T(1);
  cout << ans;
  return 0;
}
