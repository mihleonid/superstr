#include<iostream>
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cmath>
#include<deque>
#include<iomanip>
#include<list>
#include<map>
#include<random>
#include<set>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<tuple>
#include <utility>
#include<vector>
#include<random>
#include<string>
#include<complex>
using namespace std;

using ll = long long;
using ld = long double;

#define vec vector
#define all(x) x.begin(), x.end()
//#define int long long
#define endl '\n'

random_device rd;
mt19937 rnd(rd());

const int W = 2, LEN = 7, N = 7, INF = 2e9;

int n = 0;
vec<string> a;

int overlap(string& s, string& t) {
    for (int len = min((int)s.size(), (int)t.size()); len >= 0; --len)
        if (s.substr(s.size() - len, len) == t.substr(0, len))
            return len;
}

int overlap_c(string&a, string& b, char c) {
    int ov = overlap(a, b);
    int cnt = 0;
    for (int i = 0; i < ov; ++i) cnt += (b[i] == c);
    return cnt;
}

string nadstroka() {
    vector<vector<int>> dp(n, vector<int> (1 << n, -INF));
    for (int i = 0; i<n; ++i) {
        dp[i][1 << i] = 0;
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i<n; ++i) {
            if (!((mask >> i)&1)) continue;
            int prev_mask = mask^(1 << i);
            if (!prev_mask) continue;
            for (int j = 0; j<n; ++j) {
                if (!((prev_mask >> j)&1)) continue;
                dp[i][mask] = max(dp[i][mask], dp[j][prev_mask]+overlap(a[j], a[i]));
            }
        }
    }
    int ind = 0;
    for (int i = 1; i<n; ++i) {
        if (dp[ind][(1 << n)-1] < dp[i][(1 << n)-1]) ind = i;
    }
    vector<int> res;
    int cur_mask = (1 << n)-1;
    while (true) {
        res.emplace_back(ind);
        if (!(cur_mask ^ (1 << ind))) break;
        int cur_ind = 0;
        while (dp[cur_ind][cur_mask ^ (1 << ind)]+overlap(a[cur_ind], a[ind]) != dp[ind][cur_mask]) cur_ind++;
        cur_mask ^= 1 << ind;
        ind = cur_ind;
    }
    reverse(all(res));
    string s = a[res[0]];
    for (int i = 0; i<n-1; ++i) {
        s += a[res[i+1]].substr(overlap(a[res[i]], a[res[i+1]]));
    }
    return s;
}

string nadstroka(char c) {
    vector<vector<int>> dp(n, vector<int> (1 << n, -INF));
    for (int i = 0; i<n; ++i) {
        dp[i][1 << i] = 0;
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i<n; ++i) {
            if (!((mask >> i)&1)) continue;
            int prev_mask = mask^(1 << i);
            if (!prev_mask) continue;
            for (int j = 0; j<n; ++j) {
                if (!((prev_mask >> j)&1)) continue;
                dp[i][mask] = max(dp[i][mask], dp[j][prev_mask]+overlap_c(a[j], a[i], c));
            }
        }
    }
    int ind = 0;
    for (int i = 1; i<n; ++i) {
        if (dp[ind][(1 << n)-1] < dp[i][(1 << n)-1]) ind = i;
    }
    vector<int> res;
    int cur_mask = (1 << n)-1;
    while (true) {
        res.emplace_back(ind);
        if (!(cur_mask ^ (1 << ind))) break;
        int cur_ind = 0;
        while (dp[cur_ind][cur_mask ^ (1 << ind)]+overlap_c(a[cur_ind], a[ind], c) != dp[ind][cur_mask]) cur_ind++;
        cur_mask ^= 1 << ind;
        ind = cur_ind;
    }
    reverse(all(res));
    string s = a[res[0]];
    for (int i = 0; i<n-1; ++i) {
        s += a[res[i+1]].substr(overlap(a[res[i]], a[res[i+1]]));
    }
    return s;
}
