#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL w, v;
} e[101];
LL n, w, f[100001];  //f[i]:v值为i时w的值

int main() {
  cin >> n >> w;
  for (LL i = 1; i <= n; i++) {
    cin >> e[i].w >> e[i].v;
  }
  fill(&f[1], &f[100000] + 1, 1145141919810);
  for (LL i = 1; i <= n; i++) {
    for (LL j = 100000; j >= e[i].v; j--) {
      f[j] = min(f[j], f[j - e[i].v] + e[i].w);
    }
  }
  for (LL i = 100000; i; i--) {
    if (f[i] <= w) {
      cout << i << endl;
      break;
    }
  }
  return 0;
}
