#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1, kMaxM = 20, kInf = 1e9;
int n, m, a[kMaxN];

void Solve1() {
  static LL f[kMaxN];
  static int mn[kMaxM], mx[kMaxM];
  for (int i = 1; i <= n; i++) {
    fill(&mn[1], &mn[m], kInf);
    fill(&mx[1], &mx[m], -kInf);
    for (int j = i; j >= 1; j--) {
      for (int k = 1; k < m; k++) {
        if (mn[k] > a[j]) {
          for (int l = k; l + 1 < m; l++) {
            swap(mn[l], mn[m - 1]);
          }
          mn[k] = a[j];
          break;
        }
      }
      for (int k = 1; k < m; k++) {
        if (mx[k] < a[j]) {
          for (int l = k; l + 1 < m; l++) {
            swap(mx[l], mx[m - 1]);
          }
          mx[k] = a[j];
          break;
        }
      }
      int w = 0;
      for (int k = 1; k < m; k++) {
        w = max(w, mx[k] - mn[m - k]);
      }
      f[i] = max(f[i], f[j - 1] + 1LL * w * w);
    }
    cout << f[i] << " \n"[i == n];
  }
}

void Solve2() {
  static LL f[kMaxN];
  static vector<int> mx, mn;
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1];
    for (; !mx.empty() && a[mx.back()] < a[i]; mx.pop_back()) {
    }
    mx.push_back(i);
    ;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  if (n <= 1000) {
    Solve1();
  } else {
    Solve2();
  }
  return 0;
}
