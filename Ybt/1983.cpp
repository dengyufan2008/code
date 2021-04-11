#include <cstdio>
using namespace std;
const int N = 100001;
int main() {
  int n, total = 0, yx = 0, gj[N], price[N], time[N], used[N] = {};
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", &gj[i], &price[i], &time[i]);
    if (gj[i]) {
      used[i] = 1;
    }
    if (gj[i]) {
      for (int j = yx + 1; j <= i; j++) {
        if (!used[j] && price[j] >= price[i] && time[j] + 45 >= time[i]) {
          used[j] = 1;
          total = total - price[i];
          break;
        } else if (time[j] + 45 < time[i]) {
          used[j] = 1;
          yx = j;
        }
      }
    }
    total = total + price[i];
  }
  printf("%d", total);
  return 0;
}
