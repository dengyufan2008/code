//链表写法
#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int d;
  int p;
} e[200002];

struct B {
  int et;     //链表尾
  int mx;     //最大儿子子树的节点数
  int d = 1;  //所有子树节点数和
} v[100001];

int n, m;

int T(int f, int x) {  //父亲是f,求x及子树的节点之和
  int tmp;
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f) {
      tmp = T(x, e[i].d);
      v[x].mx = max(v[x].mx, tmp);
      v[x].d += tmp;
    }
  }
  return v[x].d;
}

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    e[++m * 2] = {y, v[x].et};
    v[x].et = m * 2;
    e[m * 2 + 1] = {x, v[y].et};
    v[y].et = m * 2 + 1;
  }
  T(0, 1);  //父亲是0,正在处理1
  for (int i = 1; i <= n; i++) {
    if (v[i].mx <= n / 2 && n - v[i].d <= n / 2) {
      cout << i << " ";
    }
  }
  return 0;
}
/*
vector写法

#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int mx;     //最大儿子子树的节点数
  int d = 1;  //所有子树节点数和
  vector<int> s;
} v[100001];

int n;

int T(int f, int x) {  //父亲是f,求x及子树的节点之和
  int tmp;
  for(int i = 0; i < v[x].s.size(); i++) {
    if(v[x].s[i] != f) {
      tmp = T(x, v[x].s[i]);
      v[x].mx = max(v[x].mx, tmp);
      v[x].d += tmp;
    }
  }
  return v[x].d;
}

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].s.push_back(y);
    v[y].s.push_back(x);
  }
  T(0, 1);  //父亲是0,正在处理1
  for(int i = 1; i <= n; i++) {
    if(v[i].mx <= n / 2 && n - v[i].d <= n / 2) {
      cout << i << " ";
    }
  }
  return 0;
}
*/
