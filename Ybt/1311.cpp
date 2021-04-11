#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, a[100001], ans;

void Sort(int l, int r) {  //�鲢����
  if (l >= r) {
    return;
  }
  int mid = (l + r) / 2, b[100001] = {}, start = 0, i, j;
  Sort(l, mid), Sort(mid + 1, r);
  for (i = l, j = mid + 1; i <= mid && j <= r;) {
    if (a[i] <= a[j]) {
      b[++start] = a[i++];
    } else {
      b[++start] = a[j++];
      ans += mid - i + 1;
    }
  }
  for (; i <= mid; i++) {
    b[++start] = a[i];
  }
  for (; j <= r; j++) {
    b[++start] = a[j];
  }
  copy(&b[0], &b[start] + 1, &a[l]);
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Sort(1, n);
  cout << ans;
  return 0;
}
