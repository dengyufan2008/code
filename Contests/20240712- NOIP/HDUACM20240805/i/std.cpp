// O(n \log n)
// 为了方便处理区间长度为奇数的情况，将坐标全部 *2，这样的话保证区间中心点为整数坐标。
#include <bits/stdc++.h>
using namespace std;

struct node {
  long long pos, rad;
  node() = default;
  node(long long pos) : pos(pos), rad() {}
  node(long long pos, long long rad) : pos(pos), rad(rad) {}
  bool operator<(const node &b) const {
    return pos < b.pos;
  }
};
// node 的含义：在 0 时刻，中心坐标为 pos，半径为 rad。于是 t 时刻的半径为 rad + 2 * t。rad 可以为负数。

node tonode(long long t, long long l, long long r) {
  return node((l + r) / 2, (r - l) / 2 - 2 * t);
}

long long mergetime(node a, node b) {
  return (abs(a.pos - b.pos) - a.rad - b.rad + 3) / 4;
}

node merge(node a, node b) {
  if (a.pos > b.pos)
    swap(a, b);
  long long t = mergetime(a, b);
  long long l = a.pos - a.rad - 2 * t;
  long long r = b.pos + b.rad + 2 * t;
  return node((l + r) / 2, (r - l) / 2 - 2 * t);
}

enum etype { MRG,
             DEL,
             QRY };

struct event {
  etype type;
  long long t, x, y;
  event(etype type, long long t) : type(type), t(t), x(), y() {}
  event(etype type, long long t, long long x, long long y) : type(type), t(t), x(x), y(y) {}
  bool operator<(const event &b) const {
    return t != b.t ? t < b.t : (type != b.type ? type < b.type : (x != b.x ? x < b.x : y < b.y));
  }
};

event mergeevent(node a, node b) {
  return event(MRG, mergetime(a, b), a.pos, b.pos);
}

int main() {
  freopen("i.in", "r", stdin);
  freopen("i.ans", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int m, q;
    cin >> m >> q;
    set<node> nds({node(0, 1)});
    set<event> es;
    long long radsum = 1;
    while (m--) {
      int t, l, r;
      cin >> t >> l >> r;
      es.insert(event(DEL, t, l * 2ll - 1, r * 2ll + 1));
    }
    while (q--) {
      int t;
      cin >> t;
      es.insert(event(QRY, t));
    }
    bool firstquery = true;
    while (es.size()) {
      event e = *es.begin();
      es.erase(es.begin());
      switch (e.type) {
        case DEL: {
          auto [type, t, l, r] = e;
          auto it = nds.lower_bound(node(l));
          if (it != nds.begin())
            it--;
          while (it != nds.end()) {
            node nd = *it;
            long long ndl = nd.pos - nd.rad - 2 * t;
            long long ndr = nd.pos + nd.rad + 2 * t;
            if (ndl >= r || ndr <= l) {
              if (it->pos >= r)
                break;
              it++;
              continue;
            }
            it = nds.erase(it);
            radsum -= nd.rad;
            bool haveprend = it != nds.begin();
            node prend;
            if (haveprend) {
              prend = *prev(it);
              es.erase(mergeevent(prend, nd));
            }
            bool havenxtnd = it != nds.end();
            node nxtnd;
            if (it != nds.end()) {
              nxtnd = *it;
              es.erase(mergeevent(nd, nxtnd));
            }
            if (ndl >= l && ndr <= r) {
              if (haveprend && havenxtnd)
                es.insert(mergeevent(prend, nxtnd));
              continue;
            }
            if (l > ndl && r < ndr) {
              node lnd = tonode(t, ndl, l);
              node rnd = tonode(t, r, ndr);
              nds.insert(lnd);
              radsum += lnd.rad;
              nds.insert(rnd);
              radsum += rnd.rad;
              if (haveprend)
                es.insert(mergeevent(prend, lnd));
              es.insert(mergeevent(lnd, rnd));
              if (havenxtnd)
                es.insert(mergeevent(rnd, nxtnd));
              continue;
            }
            if (r < ndr)
              ndl = r;
            if (l > ndl)
              ndr = l;
            nd = tonode(t, ndl, ndr);
            nds.insert(nd);
            radsum += nd.rad;
            if (haveprend)
              es.insert(mergeevent(prend, nd));
            if (havenxtnd)
              es.insert(mergeevent(nd, nxtnd));
          }
          break;
        }
        case MRG: {
          auto [type, t, x, y] = e;
          auto it = nds.lower_bound(node(x));
          node lnd = *it;
          it = nds.erase(it);
          radsum -= lnd.rad;
          node rnd = *it;
          it = nds.erase(it);
          radsum -= rnd.rad;
          node nd = merge(lnd, rnd);
          if (it != nds.begin()) {
            auto pre = prev(it);
            es.erase(mergeevent(*pre, lnd));
            es.insert(mergeevent(*pre, nd));
          }
          if (it != nds.end()) {
            es.erase(mergeevent(rnd, *it));
            es.insert(mergeevent(nd, *it));
          }
          nds.insert(nd);
          radsum += nd.rad;
          break;
        }
        case QRY: {
          auto [type, t, x, y] = e;
          if (firstquery)
            firstquery = false;
          else
            cout << ' ';
          cout << radsum + 2 * t * nds.size();
          break;
        }
      }
    }
    cout << '\n';
  }
}
