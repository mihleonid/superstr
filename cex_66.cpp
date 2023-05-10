// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
#include <ext/random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll bn = 15;
const ll bsz = 5;

const ll maxstrlen = bsz;
const ll maxstrn = bn;

thread_local ll pref[maxstrlen * 2 + 1];
thread_local ll d[1 << maxstrn][maxstrn];
thread_local ll p[1 << maxstrn][maxstrn];
thread_local ll mat[maxstrn][maxstrn];
thread_local ll matbyc[maxstrn][maxstrn];

char idx(const string &u, const string &v, ll i) {
    if (i < v.size()) return v[i];
    if (i == v.size()) return '#';
    
    return u[i - v.size() - 1];
}

ll ov(const string &u, const string &v) {
    if (v == u) {
        ll n = u.size();
        pref[0] = 0;
        for (int i = 1; i < n; i++) {
            pref[i] = 0;
            int cur = pref[i - 1];
            while (u[i] != u[cur] && cur > 0)
                cur = pref[cur - 1];
            if (u[i] == u[cur])
                pref[i] = cur + 1;
        }
        // cout << "ov " << u << " " << v << " = " << pref[n-1] << endl;
        return pref[n - 1];
    }
    ll n = u.size() + v.size() + 1;
    pref[0] = 0;
    for (int i = 1; i < n; i++) {
        pref[i] = 0;
        int cur = pref[i - 1];
        while (idx(u, v, i) != idx(u, v, cur) && cur > 0)
            cur = pref[cur - 1];
        if (idx(u, v, i) == idx(u, v, cur))
            pref[i] = cur + 1;
    }
    // cout << "ov " << u << " " << v << " = " << pref[n-1] << endl;
    return pref[n - 1];
}

ll ovby(const string &u, const string &v, char c) {
    ll ovl = ov(u, v);
    return count(v.begin(), v.begin() + ovl, c);
}

string merge(const string &u, const string &v) {
    ll ovn = ov(u, v);
    return u.substr(0, u.size() - ovn) + v;
}

string solve_opt(const vector<string> &strs) {
    ll n = strs.size();

    for (ll m = 0; m < 1 << n; m++) {
        for (ll i = 0; i < n; i++) {
            p[m][i] = -1;
        }
    }

    for (ll m = 1; m < 1 << n; m++) {
        for (ll i = 0; i < n; i++) {
            if ((m & (1 << i)) == 0) {
                d[m][i] = -inf;
                continue;
            }
            if (__builtin_popcount(m) == 1) {
                d[m][i] = 0;
            } else {
                d[m][i] = -inf;
                for (ll j = 0; j < n; j++) {
                    if ((m & (1 << j)) == 0) continue;
                    // ll path = d[m ^ (1 << i)][j] + mat[j][i];
                    ll path = d[m ^ (1 << i)][j] + matbyc[j][i];
                    if (path > d[m][i]) {
                        d[m][i] = path;
                        p[m][i] = j;
                    }
                }
            }
        }
    }

    vector<ll> path;
    // ll m = (1 << n) - 1, v = max_element(d[m].begin(), d[m].end()) - d[m].begin();
    ll m = (1 << n) - 1, v = max_element(d[m], d[m] + n) - d[m];
    while (v != -1) {
        path.push_back(v);
        ll pv = v;
        v = p[m][v];
        m &= ~(1 << pv);
    }

    reverse(path.begin(), path.end());

    string ans = "", last = "";
    for (ll v : path) {
        ans += strs[v].substr(ov(last, strs[v]));
        last = strs[v];
    }

    return ans;
}

struct sent {
    string s;
    ll l, r;
};

struct ov_edge {
    ll l, r, ov, chars;

    // bool operator>(const ov_edge &other) const {
    //     return make_tuple(ov, -chars, l, r) > make_tuple(other.ov, -other.chars, other.l, other.r);
    // }
    //
    // bool operator<(const ov_edge &other) const {
    //     return make_tuple(ov, -chars, l, r) < make_tuple(other.ov, -other.chars, other.l, other.r);
    // }

    bool operator>(const ov_edge &other) const {
        return ov > other.ov;
    }

    bool operator<(const ov_edge &other) const {
        return ov < other.ov;
    }
};

thread_local ll parent[maxstrn];

ll leader(ll v) {
    if (parent[v] == v) return v;
    else return parent[v] = leader(parent[v]);
}

void unite(ll a, ll b) {
    a = leader(a), b = leader(b);

    parent[b] = a;
}

string solve_greedy(const vector<string> &strs, vector<vector<ov_edge>> &edges) {
    ll n = strs.size();
    vector<ll> next(n, -1);
    vector<bool> free_out(n, true);
    vector<bool> free_in(n, true);
    iota(parent, parent + n, 0);

    for (auto &rank : edges) {
        for (auto &edge: rank) {
            if (!free_in[edge.r] || !free_out[edge.l] || leader(edge.l) == leader(edge.r)) continue;

            free_out[edge.l] = false;
            free_in[edge.r] = false;
            next[edge.l] = edge.r;

            unite(edge.l, edge.r);
        }
    }

    vector<bool> input(n, false);
    for (ll i = 0; i < n; i++) {
        if (next[i] != -1) input[next[i]] = true;
    }

    ll start = -1;
    for (ll i = 0; i < n; i++) {
        if (!input[i]) start = i;
    }
    if (start == -1) {
        return "";
    }

    string ans = strs[start];
    ll lasti = start;
    start = next[start];
    while (start != -1) {
        ans += strs[start].substr(mat[lasti][start]);
        lasti = start;
        start = next[start];
    }

    return ans;
}

const char special_char = '1';
const ll greedy_shuffles = 100;

const ll max_threads = 8;

atomic_uint64_t iters(0);
const ull total = bn * bsz < 63 ? 1ull << (bn * bsz) : 1ull << 63;

thread_local ull last_tick = 0;
thread_local ull last_count = 0;

const ull step = 50000;
thread_local ofstream ff("found.txt", ios::app);

mutex cout_mutex;

#define mt19937_64 __gnu_cxx::sfmt19937

void check_counterexample(vector<string> &strs, mt19937_64 &mt) {
    vector<ov_edge> all_edges;
    for (ll i = 0; i < strs.size(); i++) {
        for (ll j = 0; j < strs.size(); j++) {
            mat[i][j] = ov(strs[i], strs[j]);
            matbyc[i][j] = ovby(strs[i], strs[j], special_char);
            
            all_edges.push_back({i, j, mat[i][j], matbyc[i][j]});
        }
    }

    vector<vector<ov_edge>> edges_by_ovs;

    sort(all_edges.begin(), all_edges.end());

    while (!all_edges.empty()) {
        ll rank = all_edges.back().ov;
        vector<ov_edge> el;
        while (!all_edges.empty() && all_edges.back().ov == rank) {
            el.push_back(all_edges.back());
            all_edges.pop_back();
        }
        edges_by_ovs.push_back(el);
    }

    auto opt = solve_opt(strs);
    ll opt_cs[2];
    for (ll c = '0'; c <= '1'; c++) {
        opt_cs[c - '0'] = count(opt.begin(), opt.end(), c);
    }

    for (ll itt = 0; itt < greedy_shuffles; itt++) {
        for (auto &el: edges_by_ovs) shuffle(el.begin(), el.end(), mt);
        auto greedy = solve_greedy(strs, edges_by_ovs);
        for (char c = '0'; c <= '1'; c++) {
            ll greedy_c = count(greedy.begin(), greedy.end(), c);
            if (opt_cs[c-'0'] * 2 < greedy_c) {
                lock_guard<mutex> guard(cout_mutex);
                printf("\33[2K\r");
                cout << fixed;
                cout << "COUNTEREXAMPLE FOUND (for sym " << c << "): " << fl(greedy_c) / opt_cs[c-'0'] << endl << endl;
                ff << endl << endl;
                ff << fl(greedy_c) / opt_cs[c-'0'] << endl << endl;

                for (auto &s: strs) {
                    cout << s << endl;
                    ff << s << endl;
                }

                ff << "greedy: " << greedy << endl;
                ff << "opt   : " << opt << endl;

                cout << "greedy: " << greedy << endl;
                cout << "opt   : " << opt << endl;

                cout << endl << endl << scientific;
                ff << endl << endl;
            }
        }
    }
}

void gen_random(vector<string>& strs, mt19937_64& mt) {
    strs.clear();
    for (ll i = 0; i < bn; i++) {
        // auto str = bitset<bsz>(uniform_int_distribution<ull>{0, (1 << bsz) - 1}(mt)).to_string();
        // strs.push_back(str);
        
        string str;
        for (ll j = 0; j < bsz; j++) {
            str.push_back(uniform_real_distribution<fl>()(mt) < 0.7 ? '0' : '1');
        }
        strs.push_back(str);
    }

    sort(strs.begin(), strs.end());
    strs.erase(unique(strs.begin(), strs.end()), strs.end());

    // cout << "generated: ";
    // for (auto &s: strs) {
        // cout << s << ' ';
    // }
    // cout << endl;
}

void brute_random(bool threaded) {
    mt19937_64 mt(random_device{}());

    if (!threaded) cout << scientific;
    
    vector<string> strs;
    for (;;) {
        gen_random(strs, mt);

        check_counterexample(strs, mt);
        iters.fetch_add(1, std::memory_order_relaxed);
    }
}

void brute_random_threaded() {
    cout << scientific;

    vector<thread> pool;
    for (ll i = 0; i < max_threads; i++) {
        pool.push_back(thread(brute_random, true));
    }

    for (;;) {
        this_thread::sleep_for(chrono::milliseconds(1000));
        printf("\33[2K\r");
        cout << flush;

        cout << "--> " << iters.load(std::memory_order_relaxed) << " avg " << fl(iters - last_count) << "/sec" << flush;

        last_count = iters;
    }
}

void brute_full(ll n, vector<string> &strs) {
    if (n < bn) {
        ll i;
        if (n == 0) i = (1 << bsz) / 2;
        else i = 0;
        for (; i < 1 << bsz; i++) {
            auto ss = bitset<bsz>(i).to_string();
            if (find(strs.begin(), strs.end(), ss) != strs.end()) {
                brute_full(n + 1, strs);
            } else {
                strs.push_back(ss);
                brute_full(n + 1, strs);
                strs.pop_back();
            }
        }
    } else {
        __gnu_cxx::sfmt19937 mt{1};
        check_counterexample(strs, mt);
        if (iters % step == 0) {

            printf("\33[2K\r");
            cout << flush;

            fl seconds = (fl(clock() - last_tick) / CLOCKS_PER_SEC) * (fl(total - iters) / step);

            cout << "--> " << iters << "/" << total << " = " << (fl(iters) / total) * 100 << "% eta " << seconds / 3600 << " hours" << flush;
            last_tick = clock();
        }
        iters++;
    }
}

int main() {
    cout << endl << fixed << setprecision(2);
    printf("\33[?25l");

    // vector<string> v;
    // brute_full(0, v);

    // brute_random(false);
    
    brute_random_threaded();
}
