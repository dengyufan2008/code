#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2.5e5 + 2, kMaxL = 18;
int n, m, q, a[kMaxN], l[kMaxN], d[kMaxN], ans[kMaxN];
vector<int> w[kMaxN];

class ST {
  int lg[kMaxN], mx[kMaxL][kMaxN];

 public:
  void Init() {
    for (int i = 2; i <= n; i++) {
      lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
      mx[0][i] = l[i];
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        mx[i][j] = mx[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          mx[i][j] = max(mx[i][j], mx[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  int Max(int l, int r) {
    int o = lg[r - l + 1];
    return max(mx[o][l], mx[o][r - (1 << o) + 1]);
  }
} st;

void Init() {
  static int o[kMaxN];
  static vector<int> v;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> d[i], o[i] = i;
  }
  sort(o + 1, o + n + 1, [](int i, int j) {
    return d[i] < d[j];
  });
  for (int i = 1; i <= n; i++) {
    a[o[i]] = a[o[i - 1]] + (d[o[i - 1]] < d[o[i]]);
  }
  sort(d + 1, d + n + 1);
  m = unique(d + 1, d + n + 1) - d - 1;
  for (int i = n; i >= 1; i--) {
    for (; !v.empty() && a[i] >= v.back(); v.pop_back()) {
    }
    v.push_back(a[i]);
    l[i] = v.size(), w[l[i]].push_back(i);
  }
}

void CalcAns() {
  st.Init(), seg1.Init(), seg2.Init();
  ans[m + 1] = l[1];
  for (int i = m, p; i >= 1; i--) {
    int ans1 = seg1.Ask(1, n);
    if (i == m || ans1 != p) {
      p = ans1;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), CalcAns();
  for (int i = 1, x; i <= q; i++) {
    cin >> x;
    cout << ans[lower_bound(d + 1, d + m + 1, x) - d] << '\n';
  }
  return 0;
}
