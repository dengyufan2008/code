#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int a[2], b[2];
} e[100001];
int h, w, n;

void M() {
  int m = 0, l[100001] = {};
  for (int i = 1; i <= n; i++) {
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return e[i].a[0] < e[j].a[0]; 
  });
  for (int i = 1; i <= n; i++) {
    e[l[i]].b[1] = (m += (e[l[i]].a[0] != e[l[i - 1]].a[0]));
  }
}

int main() {
  cin >> h >> w >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a[0] >> e[i].a[1];
  }
  M();
  for (int i = 1; i <= n; i++) {
    swap(e[i].a[0], e[i].a[1]), swap(e[i].b[0], e[i].b[1]);
  }
  M();
  for (int i = 1; i <= n; i++) {
    cout << e[i].b[0] << " " << e[i].b[1] << endl;
  }
  return 0;
}
