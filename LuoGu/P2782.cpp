#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int a, b;
} e[200001];
int n;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b;
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.a < j.a;
  });
  
  return 0;
}
