#include <fstream>

using namespace std;

ifstream cin("c.in");
ifstream cout("c.out");
ifstream cans("c.ans");
ofstream ctxt("c.txt");

const bool kCmpAns = 1;
int u, n, m, k, l, ll;
string s, ss, t, o, oo;
char c;

ostream &AC() { return ctxt << "Accepted\n"; }
ostream &WA() { return ctxt << "Wrong Answer\n"; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  for (int _u = 1; _u <= u; _u++) {
    cin >> n >> m >> k >> s >> t, ss = s;
    cout >> o, cans >> oo;
    if (o != oo) {
      WA() << _u << '\n'
           << "Distinct Answer\n";
      return 0;
    } else if (o == "YES") {
      cout >> l, cans >> ll;
      if (l < ll && kCmpAns) {
        WA() << _u << '\n'
             << "Better Answer\n";
        return 0;
      } else if (l > ll && kCmpAns) {
        WA() << _u << '\n'
             << "Worse Answer\n";
        return 0;
      }
      for (int i = 1, x; i <= l; i++) {
        cout >> o >> x, x--;
        if (o == "INSERT") {
          cout >> c, s = s.substr(0, x) + c + s.substr(x);
        } else if (o == "DELETE") {
          s = s.substr(0, x) + s.substr(x + 1);
        } else if (o == "REPLACE") {
          cout >> c, s[x] = c;
        } else {
          WA() << _u << '\n'
               << "Invalid Operator From Solution\n"
               << o << '\n';
          return 0;
        }
      }
      for (int i = 1, x; i <= ll; i++) {
        cans >> o >> x, x--;
        if (o == "INSERT") {
          cans >> c, ss = ss.substr(0, x) + c + ss.substr(x);
        } else if (o == "DELETE") {
          ss = ss.substr(0, x) + ss.substr(x + 1);
        } else if (o == "REPLACE") {
          cans >> c, ss[x] = c;
        } else {
          WA() << _u << '\n'
               << "Invalid Operator From STD\n"
               << o << '\n';
          return 0;
        }
      }
      if (s != t) {
        WA() << _u << '\n'
             << "Wrong Transform From Solution\n"
             << s << '\n';
        return 0;
      } else if (ss != t) {
        WA() << _u << '\n'
             << "Wrong Transform From STD\n"
             << ss << '\n';
        return 0;
      }
    }
  }
  AC();
  return 0;
}
