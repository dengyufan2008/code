#include <bits/stdc++.h>
using namespace std;
int main() {
  int lh1[201], rh1[201], ans[201], jw = 0;
  char lh2[201], rh2[201];
  memset(lh1, -1, sizeof(lh1));
  memset(rh1, -1, sizeof(rh1));
  memset(ans, -1, sizeof(ans));
  scanf("%s%s", lh2, rh2);
  int start1 = 0, start2 = 0;
  for (int i = 0; i <= 200; i++) {
    if (lh2[i] == '0') {
      start1++;
    } else if (lh2[i] != '0') {
      break;
    }
  }
  for (int i = 0; i <= 200; i++) {
    if (rh2[i] == '0') {
      start2++;
    } else if (rh2[i] != '0') {
      break;
    }
  }
  for (int i = 1; (i <= 200) &&
                  (lh2[start1 + i - 1] != '\0');
       i++) {
    lh1[201 - i] = lh2[start1 + i - 1] - '0';
  }
  for (int i = 1; (i <= 200) &&
                  (rh2[start2 + i - 1] != '\0');
       i++) {
    rh1[201 - i] = rh2[start2 + i - 1] - '0';
  }
  if ((lh1[200] == -1) && (rh1[200] == -1)) {
    printf("0");
    return 0;
  }
  for (int i = 200; i >= 0; i--) {
    if ((lh1[i] == -1) && (rh1[i] != -1)) {
      ans[201 - i] = rh1[i] + jw;
    } else if ((lh1[i] != -1) && (rh1[i] == -1)) {
      ans[201 - i] = lh1[i] + jw;
    } else if ((lh1[i] != -1) && (rh1[i] != -1)) {
      ans[201 - i] = lh1[i] + rh1[i] + jw;
    } else if ((lh1[i] == -1) && (rh1[i] == -1)) {
      ans[201 - i] = jw;
    }
    if (ans[201 - i] >= 10) {
      ans[201 - i] = ans[201 - i] - 10;
      jw = 1;
    } else {
      jw = 0;
    }
  }
  for (int i = 1; i <= 200; i++) {
    if (ans[i] != -1) {
      printf("%d", ans[i]);
    } else {
      break;
    }
  }
  return 0;
}
