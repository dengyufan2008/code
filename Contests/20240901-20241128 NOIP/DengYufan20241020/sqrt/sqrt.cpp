#include <fstream>
#include <vector>

using namespace std;

ifstream cin("sqrt.in");
ofstream cout("sqrt.out");

const int kMaxN = 2e6 + 1;
int n, m, k, ans, prime[kMaxN], c[kMaxN];
bool b[kMaxN];
vector<int> v[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      prime[++k] = i, v[i].push_back(i);
    }
    for (int j = 1; j <= k; j++) {
      int w = i * prime[j];
      if (w < kMaxN) {
        b[w] = 1, v[w] = v[i], v[w].push_back(prime[j]);
        if (!(i % prime[j])) {
          break;
        }
      } else {
        break;
      }
    }
  }
  for (int i = 1; i * i < kMaxN; i++) {
    c[i * i]++;
  }
  for (int i = 1; i < kMaxN; i++) {
    c[i] += c[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    int w = 1;
    for (int l = 0, r = 0; l < v[i].size(); l = r) {
      for (; r < v[i].size() && v[i][l] == v[i][r]; r++) {
      }
      if (r - l & 1) {
        w *= v[i][l];
      }
    }
    ans += c[m / w];
  }
  cout << ans << '\n';
  return 0;
}
