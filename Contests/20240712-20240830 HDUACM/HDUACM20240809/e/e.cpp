// by wls
#include <bits/stdc++.h>
using namespace std;
int winid;
enum Type {
  H,
  D,
  C,
  S,
  _ERR
};
int ch2id(char ch) {
  if (isdigit(ch)) return ch - '0';
  if (ch == 'A') return 14;
  if (ch == 'K') return 13;
  if (ch == 'Q') return 12;
  if (ch == 'J') return 11;
  if (ch == 'T') return 10;
  assert(0);
  return -1;
}
Type ch2tp(char ch) {
  switch (ch) {
    case 'H':
      return H;
    case 'D':
      return D;
    case 'C':
      return C;
    case 'S':
      return S;
    default:
      assert(0);
      return _ERR;
  }
}

char id2ch(int id) {
  if (id < 10) return char(id + '0');
  if (id == 14) return 'A';
  if (id == 13) return 'K';
  if (id == 12) return 'Q';
  if (id == 11) return 'J';
  if (id == 10) return 'T';
  assert(0);
  return '?';
}
char tp2ch(Type tp) {
  switch (tp) {
    case H:
      return 'H';
    case D:
      return 'D';
    case C:
      return 'C';
    case S:
      return 'S';
    default:
      assert(0);
      return '?';
  }
}
struct Card {
  Type tp;
  int id;
  Card() {}
  Card(Type _tp, int _id) : tp(_tp), id(_id) {}
  Card(string _s) {
    id = ch2id(_s[0]);
    tp = ch2tp(_s[1]);
  }
  bool operator<(const Card &rhs) const { return id < rhs.id || (id == rhs.id && tp < rhs.tp); }
  bool operator>(const Card &rhs) const { return id > rhs.id; }
  bool operator==(const Card &rhs) const { return id == rhs.id && tp == rhs.tp; }
  string print() { return string(1, id2ch(id)) + tp2ch(tp); }
};

struct Pat {
  int typ = -1;
  Card c[5];
  void init() {
    static int mp[15];
    fill(mp, mp + 15, 0);

    sort(c, c + 5, greater<Card>());
    bool same = 1;
    for (int i = 1; i < 5; i++) same &= (c[0].tp == c[i].tp);
    if (same) {
      if (c[0].id == 14 && c[4].id == 10) return typ = 9, void();

      if (c[0].id - c[4].id == 4) return typ = 8, void();
      if (c[0].id == 14 && c[1].id == 5 && c[4].id == 2) {
        c[0].id = 1;
        sort(c, c + 5, greater<Card>());
        c[4].id = 14;
        return typ = 8, void();
      }
    }

    int f1 = 0;
    for (int i = 0; i < 5; i++) {
      mp[c[i].id] += 1;
      if (mp[c[i].id] >= 4) f1 = c[i].id;
    }
    if (f1) {
      for (int i = 0; i < 5; i++) {
        if (c[i].id != f1) {
          swap(c[i], c[4]);
          break;
        }
      }
      return typ = 7, void();
    }

    int f_3 = 0, f_2 = 0;
    vector<Card> l_3, l_2, l_1;
    for (int i = 0; i < 5; i++) {
      if (mp[c[i].id] == 3) f_3 = c[i].id, l_3.push_back(c[i]);
      if (mp[c[i].id] == 2) f_2 = c[i].id, l_2.push_back(c[i]);

      if (mp[c[i].id] == 1) l_1.push_back(c[i]);
    }

    if (f_3 && f_2) {
      for (int i = 0; i < 3; i++) c[i] = l_3[i];
      for (int i = 0; i < 2; i++) c[3 + i] = l_2[i];
      return typ = 6, void();
    }

    if (same) return typ = 5, void();

    if (c[0].id - c[4].id == 4 && c[1].id - c[4].id == 3 && c[2].id - c[4].id == 2 && c[3].id - c[4].id == 1) return typ = 4, void();
    if (c[0].id == 14 && c[1].id == 5 && c[2].id == 4 && c[3].id == 3 && c[4].id == 2) {
      c[0].id = 1;
      sort(c, c + 5, greater<Card>());
      c[4].id = 14;
      return typ = 4, void();
    }

    if (f_3) {
      for (int i = 0; i < 3; i++) c[i] = l_3[i];
      for (int i = 0; i < 2; i++) c[3 + i] = l_1[i];
      return typ = 3, void();
    }

    if (l_2.size() == 4) {
      for (int i = 0; i < 4; i++) c[i] = l_2[i];
      assert(l_1.size() == 1);
      c[4] = l_1[0];
      return typ = 2, void();
    }

    if (l_2.size() == 2) {
      for (int i = 0; i < 2; i++) c[i] = l_2[i];
      assert(l_1.size() == 3);
      for (int i = 0; i < 3; i++) c[2 + i] = l_1[i];
      return typ = 1, void();
    }

    typ = 0;
  }
};
bool operator<(const Pat &pa, const Pat &pb) {
  if (pa.typ == -1 || pb.typ == -1) assert(0);
  if (pa.typ != pb.typ) return pa.typ < pb.typ;
  for (int i = 0; i < 5; i++)
    if (pa.c[i].id != pb.c[i].id) return pa.c[i].id < pb.c[i].id;
  return 0;
}

set<Card> All, _All;
vector<Card> swl, last, pub, priv[4];
Pat pat[4];
void init() {
  for (int tp = 0; tp < 4; tp++)
    for (int id = 2; id <= 14; id++) All.insert(Card(Type(tp), id));
}

void gen_pat(int pid) {
  assert(priv[pid].size() == 7);
  for (int i = 0; i < 7; i++) {
    for (int j = i + 1; j < 7; j++) {
      Pat tmp;
      for (int k = 0, pt = 0; k < 7; k++) {
        if (k == i || k == j) continue;
        tmp.c[pt++] = priv[pid][k];
      }
      tmp.init();
      if (pat[pid].typ == -1)
        pat[pid] = tmp;
      else if (pat[pid] < tmp)
        pat[pid] = tmp;
    }
  }
}

int calc() {
  int qwq = 0;
  for (int li = 0; li < last.size(); li++) {
    for (int lj = li + 1; lj < last.size(); lj++) {
      pub.push_back(last[li]), pub.push_back(last[lj]);
      for (int j = 0; j < 4; j++) {
        pat[j] = Pat();
        for (int i = 0; i < 5; i++) priv[j].push_back(pub[i]);
        gen_pat(j);
        for (int i = 0; i < 5; i++) priv[j].pop_back();
      }

      bool flg = 1;
      for (int j = 0; j < 4; j++) {
        if (pat[winid] < pat[j]) {
          flg = 0;
          break;
        }
      }
      qwq += flg;

      pub.pop_back(), pub.pop_back();
    }
  }
  return qwq;
}

void work() {
  _All = All;
  swl.clear(), last.clear(), pub.clear();
  string _s;
  for (int i = 0; i < 3; i++) {
    cin >> _s;
    pub.push_back(Card(_s)), swl.push_back(Card(_s)), _All.erase(Card(_s));
  }
  for (int j = 0; j < 4; j++) {
    priv[j].clear();
    for (int i = 0; i < 2; i++) {
      cin >> _s;
      priv[j].push_back(Card(_s)), swl.push_back(Card(_s)), _All.erase(Card(_s));
    }
  }
  for (auto x : _All) last.push_back(x);
  cin >> winid;

  int ans = calc();
  string Ans = "";

  for (int _i = 0; _i < swl.size(); _i++) {
    for (int _j = _i + 1; _j < swl.size(); _j++) {
      auto do_swp = [&](Card &c) {
        if (c == swl[_i])
          c = swl[_j];
        else if (c == swl[_j])
          c = swl[_i];
      };
      for (int k = 0; k < 3; k++) do_swp(pub[k]);
      for (int j = 0; j < 4; j++)
        for (int i = 0; i < 2; i++) do_swp(priv[j][i]);

      int res = calc();
      string sa = swl[_i].print(), sb = swl[_j].print();
      if (sa > sb) swap(sa, sb);
      if (ans < res || (ans == res && Ans > (sa + " " + sb))) {
        ans = res;
        Ans = (sa + " " + sb);
      }

      // if (swl[_i] == Card("5D") && swl[_j] == Card("JS")) {
      //     cerr << ans << ' ' << res << '\n';
      // }

      for (int k = 0; k < 3; k++) do_swp(pub[k]);
      for (int j = 0; j < 4; j++)
        for (int i = 0; i < 2; i++) do_swp(priv[j][i]);
    }
  }

  if (Ans == "") Ans = "None";

  cout << Ans << '\n';
}
void _test() {
  Pat pat;
  pat.c[0] = Card("6D");
  pat.c[1] = Card("2D");
  pat.c[2] = Card("4H");
  pat.c[3] = Card("3S");
  pat.c[4] = Card("5C");
  pat.init();
  cout << pat.typ << '\n';
  for (int i = 0; i < 5; i++) {
    cout << pat.c[i].print() << " \n"[i == 4];
  }
}
int main() {
  // #ifdef LOCAL
  //     freopen("test.in", "r", stdin);
  //     freopen("test.out", "w", stdout);
  // #endif
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  init();
  // #ifdef LOCAL
  //     _test();
  //     return 0;
  // #endif
  int T;
  cin >> T;
  while (T--) {
    work();
  }
  return 0;
}
