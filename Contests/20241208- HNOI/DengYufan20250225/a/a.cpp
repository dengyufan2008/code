#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 7501, kMod = 1e9 + 7;
int n, a[kMaxN];
LL f[kMaxN];

void Right() {
  for (int i = n; i > 0; i--) {
    f[i] = (f[i - 1] * (i - 1) + f[i] * (i + 1)) % kMod;
  }
  f[0] = 0;
}

void Up() {
  for (int i = 0; i < n; i++) {
    f[i] = (f[i] * i + f[i + 1] * (i + 1)) % kMod;
  }
  f[n] = f[n] * n % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1), f[1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = a[i - 1]; j < a[i]; j++) {
      Right();
    }
    Up();
  }
  cout << f[0] << '\n';
  return 0;
}
