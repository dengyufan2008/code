#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const LL kMaxN = 401, kInf = 1e18;
struct V {
  int s;
  LL w, f[kMaxN][kMaxN];
  vector<int> e;
} v[kMaxN];
int n;

void Update(LL &x, LL y) { x = max(x, y); }

void Trans(int x) {
  static LL shit, f[kMaxN][kMaxN];
  if (!shit) {
    shit = 1;
    fill(&f[0][0], &f[kMaxN][0], -kInf);
  }

  v[x].s = 1;
  for (int i : v[x].e) {
    for (int j = 1; j <= v[x].s; j++) {
      for (int k = 1; k <= v[i].s; k++) {
        for (int s = 0; s <= n; s++) {
          Update(f[j + k][s - k], v[x].f[j][s] + v[i].f[k][0]);
          Update(f[j][s], v[x].f[j][s] + v[i].f[k][j + s]);
        }
      }
    }
    v[x].s += v[i].s;
    for (int j = 1; j <= v[x].s; j++) {
      for (int s = 0; s <= n; s++) {
        v[x].f[j][s] = f[j][s], f[j][s] = -kInf;
      }
    }
  }
  for (int j = 1; j <= v[x].s; j++) {
    for (int s = 0; s <= n; s++) {
      v[x].f[j][s] += v[x].w * (j + s);
    }
  }
}

void Dp(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    Dp(x, i);
  }
  Trans(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Dp(0, 1);
  LL ans = -kInf;
  for (int j = 1; j <= n; j++) {
    Update(ans, v[1].f[j][0]);
  }
  cout << ans << '\n';
  return 0;
}
