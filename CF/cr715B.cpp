#include <bits/stdc++.h>
#define LL long long

using namespace std;

int x, n, t, m;
bool a[100001];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> x;
  while (x--) {
    t = m = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> ch;
      a[i] = ch == 'T';
      a[i] ? t++ : m++;
    }
    if (t != m * 2) {
      cout << "NO" << endl;
      continue;
    }
    
  }
  return 0;
}
