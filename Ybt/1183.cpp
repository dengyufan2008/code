#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  string id;
  int age;
} e1[101], e2[101];

int n, e1l, e2l;
string tmp;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, age; i <= n; i++) {
    cin >> tmp >> age;
    if (age >= 60) {
      e1[++e1l] = {tmp, age};
    } else {
      e2[++e2l] = {tmp, age};
    }
  }
  for (int i = 1; i <= e1l; i++) {
    for (int j = i; j < e1l; j++) {
      if (e1[j].age < e1[j + 1].age) {
        swap(e1[j], e1[j + 1]);
      }
    }
  }
  for (int i = 1; i <= e1l; i++) {
    cout << e1[i].id << endl;
  }
  for (int i = 1; i <= e2l; i++) {
    cout << e2[i].id << endl;
  }
  return 0;
}
