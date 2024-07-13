#include <cstdio>
#define LL long long

using namespace std;

const int maxn = 1e6 + 1;
int a[maxn], r[maxn], n;
LL ans = 0;

void msort(int s, int t) {
  if (s == t) {
    return;
  }
  int mid = (s + t) >> 1;
  msort(s, mid), msort(mid + 1, t);
  int i = s, j = mid + 1, k = s;
  while (i <= mid && j <= t) {
    if (a[i] <= a[j]) {
      r[k++] = a[i++];
    } else {
      r[k++] = a[j++], ans += (LL)mid - i + 1;
    }
  }
  while (i <= mid) {
    r[k] = a[i];
    k++, i++;
  }
  while (j <= t) {
    r[k] = a[j];
    k++, j++;
  }
  for (int i = s; i <= t; i++) {
    a[i] = r[i];
  }
}

inline int read() {  //���
  char ch = getchar();
  int x = 0, f = 1;
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch ^ 48), ch = getchar();
  }
  return x * f;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    a[i] = read();
  }
  msort(1, n);
  printf("%lld\n", ans);
  return 0;
}
