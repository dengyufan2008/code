#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#define INF 1000000000
#define M 10005
using namespace std;
struct E {
  int to, nx, id;
} edge[M * 100];
int tot, head[M];
void Addedge(int a, int b, int id) {
  edge[++tot].to = b;
  edge[tot].nx = head[a];
  edge[tot].id = id;
  head[a] = tot;
}
struct Lim_node {
  int op, a, b, d, val;
  bool check(int x, int y) {
    if (op == 0) return 1ll * a * x + b * y <= d;
    if (op == 1) return 1ll * a * x + b * y >= d;
    return false;
  }
};
vector<Lim_node> Lim[M * 50];
int fa[M];
struct node {
  int pc;
  long long val;
  bool operator<(const node &_) const {
    return pc < _.pc;
  }
};
int n, K;
vector<node> Val[M];
#define eps 1e-8
vector<int> Get_point(int id, int op) {  // 0->y 1->x
  int rev = (id < 0) ^ op;
  vector<Lim_node> now = Lim[abs(id)];
  if (rev)
    for (int i = 0; i < (int)now.size(); i++) swap(now[i].a, now[i].b);
  vector<int> num;
  now.push_back((Lim_node){0, 0, 1, 0, 0});
  now.push_back((Lim_node){0, 1, 0, 0, 0});
  now.push_back((Lim_node){0, 0, 1, K, 0});
  now.push_back((Lim_node){0, 1, 0, K, 0});
  for (int i = 0; i < (int)now.size(); i++) {
    for (int j = i + 1; j < (int)now.size(); j++) {
      if (1ll * now[i].a * now[j].b == 1ll * now[j].a * now[i].b) continue;
      long long mid = (1ll * now[i].d * now[j].a - 1ll * now[j].d * now[i].a) / (1ll * now[i].b * now[j].a - 1ll * now[i].a * now[j].b);
      long long Ly = mid - 1, Ry = mid + 1;
      mid = min(mid, 1ll * K);
      mid = max(mid, 0ll);
      Ly = min(Ly, 1ll * K);
      Ly = max(Ly, 0ll);
      Ry = min(Ry, 1ll * K);
      Ry = max(Ry, 0ll);
      num.push_back(Ly);
      num.push_back(mid);
      num.push_back(Ry);
    }
  }
  sort(num.begin(), num.end());
  num.erase(unique(num.begin(), num.end()), num.end());
  return num;
}
vector<node> Get_val(vector<int> A, int id) {
  vector<Lim_node> now = Lim[abs(id)];
  if (id < 0)
    for (int i = 0; i < (int)now.size(); i++) swap(now[i].a, now[i].b);
  vector<node> res;
  for (int i = 0; i < (int)A.size(); i++) {
    vector<node> tmp;
    for (int j = 0; j < (int)now.size(); j++) {
      if (now[j].b < 0) {
        now[j].a = -now[j].a;
        now[j].b = -now[j].b;
        now[j].d = -now[j].d;
        now[j].op ^= 1;
      }
      if (now[j].a == 0 && now[j].b == 0) {
        if (now[j].check(0, 0)) tmp.push_back((node){0, now[j].val});
        continue;
      }
      if (now[j].b == 0) {
        if (now[j].check(A[i], 0)) tmp.push_back((node){0, now[j].val});
        continue;
      }
      double y = (1.0 * now[j].d - now[j].a * A[i]) / now[j].b;
      if (now[j].op == 0) {
        int yy = (int)floor(y) + 1;
        if ((1ll * now[j].d - 1ll * now[j].a * A[i]) % now[j].b == 0) yy = (1ll * now[j].d - now[j].a * A[i]) / now[j].b + 1;
        if (yy >= 0) {
          tmp.push_back((node){0, now[j].val});
          tmp.push_back((node){yy, -now[j].val});
        }
      } else {
        int yy = (int)ceil(y);
        if ((1ll * now[j].d - 1ll * now[j].a * A[i]) % now[j].b == 0) yy = (1ll * now[j].d - now[j].a * A[i]) / now[j].b;
        if (yy <= K) tmp.push_back((node){max(yy, 0), now[j].val});
      }
    }
    sort(tmp.begin(), tmp.end());
    long long mx = 0, sum = 0;
    for (int i = 0; i < (int)tmp.size(); i++) {
      sum += tmp[i].val;
      if (i == (int)tmp.size() - 1 || tmp[i].pc != tmp[i + 1].pc) mx = max(mx, sum);
    }
    res.push_back((node){A[i], mx});
  }
  sort(res.begin(), res.end());
  return res;
}
vector<node> Merge(vector<node> &A, vector<node> &B) {
  int p1 = 0, p2 = 0;
  long long val1 = 0, val2 = 0;
  vector<node> res;
  while (p1 < (int)A.size() && p2 < (int)B.size()) {
    if (A[p1].pc < B[p2].pc) {
      res.push_back((node){A[p1].pc, A[p1].val + val2});
      val1 = A[p1].val;
      p1++;
    } else if (A[p1].pc > B[p2].pc) {
      res.push_back((node){B[p2].pc, val1 + B[p2].val});
      val2 = B[p2].val;
      p2++;
    } else {
      res.push_back((node){A[p1].pc, A[p1].val + B[p2].val});
      val1 = A[p1].val;
      val2 = B[p2].val;
      p1++;
      p2++;
    }
  }
  while (p1 < (int)A.size()) {
    res.push_back((node){A[p1].pc, A[p1].val + val2});
    p1++;
  }
  while (p2 < (int)B.size()) {
    res.push_back((node){B[p2].pc, val1 + B[p2].val});
    p2++;
  }
  return res;
}
void dfs(int now) {
  //	printf("now=%d\n",now);
  Val[now].clear();
  Val[now].push_back((node){0, 0});
  //	Val[now].push_back((node){INF,0});
  for (int i = head[now]; i; i = edge[i].nx) {
    int nxt = edge[i].to;
    if (fa[now] == nxt) continue;
    fa[nxt] = now;
    dfs(nxt);
    vector<int> num = Get_point(edge[i].id, 1);
    vector<node> Add = Get_val(Get_point(edge[i].id, 1), edge[i].id);
    Val[now] = Merge(Val[now], Add);
  }
}
int Deg[M];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) fa[i] = 0;
    //		printf("%d %d\n",n,K);
    tot = 0;
    for (int i = 1; i <= n; i++) head[i] = Deg[i] = 0;
    long long res = 0;
    for (int i = 1; i < n; i++) {
      Lim[i].clear();
      int a, b, cnt;
      scanf("%d%d%d", &a, &b, &cnt);
      Deg[a]++;
      Deg[b]++;
      Addedge(a, b, i);
      Addedge(b, a, -i);
      while (cnt--) {
        Lim_node nw;
        scanf("%d%d%d%d%d", &nw.op, &nw.a, &nw.b, &nw.d, &nw.val);
        if (nw.val < 0) {
          if (nw.op == 0) {
            nw.d++;
          } else
            nw.d--;
          nw.op ^= 1;
          res += nw.val;
          nw.val = -nw.val;
        }
        Lim[i].push_back(nw);
      }
    }
    int Root = 1;
    for (int i = 1; i <= n; i++)
      if (Deg[i] > Deg[Root]) Root = i;
    dfs(Root);
    long long ans = 0;
    for (int i = 0; i < (int)Val[Root].size(); i++) ans = max(ans, Val[Root][i].val);
    printf("%lld\n", ans + res);
  }
  return 0;
}
