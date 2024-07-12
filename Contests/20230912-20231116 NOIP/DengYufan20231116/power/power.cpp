#include <fstream>

using namespace std;

ifstream cin("power.in");
ofstream cout("power.out");

const int kMaxN = 1e5 + 1;
int n, k, a[kMaxN], p[kMaxN], f[kMaxN], ans[kMaxN];
string s;

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

void Merge(int x, int y) {
  if (GetRoot(x) != GetRoot(y)) {
    f[GetRoot(x)] = GetRoot(y);
  }
}

int M(int i) {
  for (int j = 2; a[i] * j <= n; j++) {
    if (s[p[a[i] * j]] == 'M') {
      return p[a[i] * j];
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k >> s;
  s = '~' + s;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[a[i]] = f[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'S') {
      for (int j = 1; j <= k; j++) {
        if ((a[i] ^ j) >= 1 && (a[i] ^ j) <= n && s[p[a[i] ^ j]] == 'S') {
          Merge(i, p[a[i] ^ j]);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'S' && !ans[GetRoot(i)]) {
      ans[GetRoot(i)] = M(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'S') {
      if (ans[GetRoot(i)]) {
        cout << "Connected to " << ans[GetRoot(i)] << '\n';
      } else {
        cout << "Not connected to any Master Station\n";
      }
    } else {
      cout << "Master Station\n";
    }
  }
  return 0;
}
