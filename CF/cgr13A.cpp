#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, q, num;
char tmp;
bool ch[100001];

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> tmp;
    ch[i] = (tmp == '1');
    num += ch[i];
  }
  for (int i = 1, t, k; i <= q; i++) {
    cin >> t >> k;
    if (t == 1) {
      if (!ch[k]) {
        num++;
      } else {
        num--;
      }
      ch[k] = !ch[k];
    } else {
      cout << (num >= k) << "\n";
    }
  }
  return 0;
}
