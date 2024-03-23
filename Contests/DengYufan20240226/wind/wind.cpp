#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("wind.in");
ofstream cout("wind.out");

const int kMaxN = 3001;
int n;
bitset<kMaxN * kMaxN> f;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i <= n * (n - 1) / 2; i++) {
    f.set(i, (n + i - 1 & i) == i);
  }
  for (int i = 1; i <= n; i++) {
    f ^= f << i;
  }
  for (int i = 0; i <= n * (n - 1) / 2; i++) {
    cout << f[i];
  }
  cout << '\n';
  return 0;
}
