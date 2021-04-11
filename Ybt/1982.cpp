#include <cstdio>
using namespace std;
int main() {
  char str[8];
  int ans = 0;
  scanf("%s", str);
  for (int i = 0; i <= 7; i++) {
    if (str[i] == '1') {
      ans++;
    }
  }
  printf("%d", ans);
  return 0;
}
