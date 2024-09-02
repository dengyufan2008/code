#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const LL kMaxN = 1e5 + 1, kInf = 1e9 + 1;
struct V {
  LL w;
  vector<pair<int, LL>> e;
} v[kMaxN];
int t, n, s;
LL mx, ans;

void T(int x) {
  if (v[x].e.empty()) {
    return;
  }
  for (auto i : v[x].e) {
    T(i.first);
    v[x].w = min(v[x].w + v[i.first].w * i.second, kInf);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    mx = ans = 0;
    for (int i = 1; i <= n; i++) {
      v[i].w = 0, v[i].e.clear();
    }
    cin >> n >> s;
    for (int i = 1, o, x; i <= n; i++) {
      cin >> o >> x;
      if (o) {
        for (int j = 1, y, z; j <= x; j++) {
          cin >> y >> z;
          v[i].e.push_back({z, y});
        }
      } else {
        v[i].w = x;
      }
    }
    T(s);
    for (auto i : v[s].e) {
      LL w = min(v[i.first].w * i.second, kInf);
      if (w > mx) {
        ans = min(ans + mx, kInf), mx = w;
      } else {
        ans = min(ans + w, kInf);
      }
    }
    if (ans == kInf) {
      cout << "Impossible\n";
    } else {
      cout << ans << '\n';
    }
  }
  return 0;
}
