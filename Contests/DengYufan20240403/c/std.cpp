// even-faster.cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll inf = 1e18;

ll S, bound;

struct State {
  ll a1, d1, a2, d2;
  bool operator==(const State& other) const { return a1 == other.a1 && a2 == other.a2 && d1 == other.d1 && d2 == other.d2; }
};

State sab(State state) {
  return {state.a2, max(0ll, state.d2 - 1), state.a1, state.d1};
}
State att(State state) {
  return {state.a2 - (state.a1 - S * state.d2), state.d2, state.a1, state.d1};
}

bool half_sab_win(State state) {
  ll sab_cnt = state.d2 / 2;
  state.a1 -= sab_cnt * (state.a2 - S * state.d1);
  state.d2 -= sab_cnt;
  state = att(state);
  state.a1 -= state.d2 * (state.a2 - S * state.d1);
  state.d2 = 0;
  state = att(state);

  ll alpha1 = state.a1 - S * state.d2;
  ll beta2 = S - state.a2;
  return alpha1 + state.d2 * beta2 >= S;
}

void dbg(State state) {
  cerr << state.a1 << " " << state.d1 << " " << state.a2 << " " << state.d2 << endl;
}

int calls = 0;
vector<vector<ll>> critA2;
vector<vector<vector<int>>> lookup;  // (d1, d2, alpha2 - minAlpha2) -> d2' until which we sabotage
vector<ll> zeroLookup;               // a2 -> min winning a1 (if d1 = d2 = 0)
bool afterPrecalc = false;

ll minAlpha2(ll d1, ll d2) {
  return S - min(S, 8 * S / (d2 * d2 * max(1ll, d1)));
}

bool wins(State state) {
  if (afterPrecalc) calls++;
  // trivial cases
  if (state.a1 <= 0) return false;
  if (state.a2 <= 0) return true;

  if (state.d1 == 0 && state.d2 == 0 && state.a2 < S) {
    return state.a1 >= zeroLookup[state.a2];
  }

  // no one can attack
  ll sab_rounds = (max(0ll, min(state.d2 * S - state.a1, state.d1 * S - state.a2)) + S - 1) / S;
  state.d1 -= sab_rounds;
  state.d2 -= sab_rounds;
  // player 1 can't attack and player 2 can't sabotage
  if (state.a1 <= state.d2 * S && state.d1 == 0 && state.a2 < S) {
    ll beta2 = S - state.a2;
    ll rounds = (state.d2 * S - state.a1 + beta2 - 1) / beta2;
    state.d2 -= rounds;
    state.a1 -= rounds * state.a2;
    if (state.d2 < 0 || state.a1 <= 0) return false;
  }
  // player 1 can't attack
  if (state.a1 <= state.d2 * S) return !wins(sab(state));
  // helpful values
  ll alpha1 = state.a1 - S * state.d2;
  ll alpha2 = state.a2 - S * state.d1;
  ll beta2 = min(S, S - alpha2);  // The inequalities work without min, but it's needed to prevent overflow!
  // player 1 must attack
  if (alpha1 >= S && alpha2 <= S) return true;
  if (alpha2 >= S) return !wins(att(state));
  if (state.d2 == 0) return !wins(att(state));
  // Can player 1 win by repeated sabotage?
  if (state.d2 >= S) return true;  // prevent overflow!
  if (alpha1 + state.d2 * beta2 >= S) return true;
  // Prevent opponent win by repeated sabotage:
  if (state.d1 > 0) {
    // (alpha2 - alpha1) + d1 * (S - alpha1) < S
    // S * (d1 - 1) + alpha2 < alpha1 * (d1 + 1)
    ll minAlpha1 = (S * (state.d1 - 1) + alpha2) / (state.d1 + 1);
    ll sabs_todo = min(state.d2, (max(0ll, minAlpha1 - alpha1) + beta2 - 1) / beta2);
    state.d2 -= sabs_todo;
    state.a1 -= sabs_todo * alpha2;
  }
  alpha2 = state.a2 - S * state.d1;
  // Can player 1 win by using half of his sabotages?
  if (half_sab_win(state)) return true;
  assert(state.d1 * state.d2 * state.d2 * (S - alpha2) <= 8 * S);
  if (state.d1 * state.d2 > bound) {
    dbg(state);
  }
  assert(state.d1 * state.d2 <= bound);

  if (state.d2 == 0) return !wins(att(state));
  ll crit = critA2[state.d1][state.d2];
  if (alpha2 >= crit) return !wins(att(state));
  if (state.d2 == 1) return !wins(sab(state));  // alpha2 < crit
  // now we can use the lookup table
  int sabs_todo = (int)state.d2 - lookup[state.d1][state.d2][alpha2 - minAlpha2(state.d1, state.d2)];
  if (sabs_todo > state.d2) {
    dbg(state);
    exit(0);
  }
  state.d2 -= sabs_todo;
  state.a1 -= sabs_todo * alpha2;
  assert(state.d2 >= 0);
  // maybe we reached d2 == 1
  if (state.d2 == 1) {
    if (alpha2 >= critA2[state.d1][state.d2])
      return !wins(att(state));
    else
      return !wins(sab(state));
  }
  return !wins(att(state));
}

// It can be proven that we need O(1) iterations when min(d1, d2) > 1
bool winsSafe(State state) {
  if (state.a1 <= state.d2 * S) return !wins(sab(state));
  if (state.d2 == 0) return !winsSafe(att(state));
  return !wins(sab(state)) || !winsSafe(att(state));
}

// minimum alpha1 for which player1 wins if he sabotages
ll sabCrit(ll d1, ll d2, ll alpha2) {
  ll lo = 0, hi = S;
  for (ll alpha1 = (lo + hi) / 2; lo < hi; alpha1 = (lo + hi) / 2) {
    if (!wins(sab({d2 * S + alpha1, d1, d1 * S + alpha2, d2})))
      hi = alpha1;
    else
      lo = alpha1 + 1;
  }
  return lo;
}

// minimum alpha1 for which player1 wins if he attacks
ll attCrit(ll d1, ll d2, ll alpha2) {
  ll lo = 0, hi = S;
  for (ll alpha1 = (lo + hi) / 2; lo < hi; alpha1 = (lo + hi) / 2) {
    if (!winsSafe(att({d2 * S + alpha1, d1, d1 * S + alpha2, d2})))
      hi = alpha1;
    else
      lo = alpha1 + 1;
  }
  return lo;
}

// minimum alpha2 for which it is optimal for player 1 to attack
ll calcCritA2(ll d1, ll d2) {
  ll lo = S - S / d2, hi = S;
  for (ll alpha2 = (lo + hi) / 2; lo < hi; alpha2 = (lo + hi) / 2) {
    ll sc = sabCrit(d1, d2, alpha2);
    ll ac = attCrit(d1, d2, alpha2);
    if (sc < ac || (sc == 0 && ac == 0))
      lo = alpha2 + 1;
    else
      hi = alpha2;
  }
  return lo;
}

ll wins2(State state) {
  // trivial cases
  if (state.a1 <= 0) return false;
  if (state.a2 <= 0) return true;
  // no one can attack
  ll sab_rounds = (max(0ll, min(state.d2 * S - state.a1, state.d1 * S - state.a2)) + S - 1) / S;
  state.d1 -= sab_rounds;
  state.d2 -= sab_rounds;
  // player 1 can't attack and player 2 can't sabotage
  if (state.a1 <= state.d2 * S && state.d1 == 0 && state.a2 < S) {
    ll beta2 = S - state.a2;
    ll rounds = (state.d2 * S - state.a1 + beta2 - 1) / beta2;
    state.d2 -= rounds;
    state.a1 -= rounds * state.a2;
    if (state.d2 < 0 || state.a1 <= 0) return false;
  }
  // player 1 can't attack
  if (state.a1 <= state.d2 * S) return !wins2(sab(state));
  // helpful values
  ll alpha1 = state.a1 - S * state.d2;
  ll alpha2 = state.a2 - S * state.d1;
  ll beta2 = min(S, S - alpha2);
  // player 1 must attack
  if (alpha1 >= S && alpha2 <= S) return true;
  if (alpha2 >= S) return !wins2(att(state));
  if (state.d2 == 0) return !wins2(att(state));
  // Can player 1 win by repeated sabotage?
  if (state.d2 >= S) return true;  // prevent overflow!
  if (alpha1 + state.d2 * beta2 >= S) return true;
  // Prevent opponent win by repeated sabotage:
  if (state.d1 > 0) {
    // (alpha2 - alpha1) + d1 * (S - alpha1) < S
    // S * (d1 - 1) + alpha2 < alpha1 * (d1 + 1)
    ll minAlpha1 = (S * (state.d1 - 1) + alpha2) / (state.d1 + 1);
    ll sabs_todo = min(state.d2, (max(0ll, minAlpha1 - alpha1) + beta2 - 1) / beta2);
    state.d2 -= sabs_todo;
    state.a1 -= sabs_todo * alpha2;
  }
  // Can player 1 win by using half of his sabotages?
  if (half_sab_win(state)) return true;

  while (state.d2 > 0) {
    if (state.d1 * state.d2 <= bound) return wins(state);
    if (!wins(att(state))) return true;
    state = att(sab(state));
  }
  return !wins(att(state));
}

bool win0(ll a1, ll a2) {
  if (a1 <= 0) return false;
  if (a2 <= 0) return true;
  return !win0(a2 - a1, a1);
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.ans", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int Q;
  cin >> S >> Q;
  zeroLookup.resize(S);
  {
    ll a1 = 1;
    for (ll a2 = 1; a2 < S; a2++) {
      while (a1 < S && !win0(a1, a2)) a1++;
      zeroLookup[a2] = a1;
    }
  }

  bound = 1;
  while (bound * bound <= 8 * S) bound++;
  critA2.assign(bound + 1, vector<ll>(1, -1));
  lookup.assign(bound + 1, vector<vector<int>>(2));
  vector<pair<ll, ll>> dvals;
  for (ll d2 = 1; d2 <= bound; d2++) {
    for (ll d1 = 0; d1 * d2 <= bound; d1++) {
      dvals.emplace_back(d1, d2);
      critA2[d1].push_back(inf);
      if (d2 > 1) {
        lookup[d1].push_back(vector<int>(S - minAlpha2(d1, d2), -1));
      }
    }
  }
  sort(dvals.begin(), dvals.end(), [](auto a, auto b) { return a.first + a.second < b.first + b.second; });
  for (auto [d1, d2] : dvals) {
    critA2[d1][d2] = calcCritA2(d1, d2);
    if (d2 == 1) continue;
    ll mi = minAlpha2(d1, d2);
    for (ll alpha2 = max(mi, critA2[d1][d2]); alpha2 < S; alpha2++) {
      lookup[d1][d2][alpha2 - mi] = (int)d2;
    }
    if (d2 == 2) {
      for (ll alpha2 = mi; alpha2 < critA2[d1][d2]; alpha2++) {
        lookup[d1][d2][alpha2 - mi] = 1;
      }
    } else {
      ll oldMi = minAlpha2(d1, d2 - 1);
      for (ll alpha2 = mi; alpha2 < critA2[d1][d2]; alpha2++) {
        lookup[d1][d2][alpha2 - mi] = lookup[d1][d2 - 1][alpha2 - oldMi];
      }
    }
  }
  afterPrecalc = true;

  cerr << dvals.size() << "\n";

  for (int q = 0; q < Q; q++) {
    ll a1, d1, a2, d2;
    cin >> a1 >> d1 >> a2 >> d2;
    cout << (wins2({a1, d1, a2, d2}) ? "YES" : "NO") << "\n";
  }
}