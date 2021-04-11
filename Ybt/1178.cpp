#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  string name;
  int mark;
} e[21];

int n;

bool P(A a, A b) {
  return a.mark > b.mark || a.mark == b.mark && a.name < b.name;
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].name >> e[i].mark;
  }
  sort(e + 1, e + 1 + n, P);
  for (int i = 1; i <= n; i++) {
    cout << e[i].name << " " << e[i].mark << "\n";
  }
  return 0;
}
