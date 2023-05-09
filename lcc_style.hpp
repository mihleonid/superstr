//#define ANGRY_FAST
//#define LOCAL
//#define _GLIBCXX_DEBUG 1
//#pragma optimize( "", on )
//#pragma GCC optimize("Ofast")
//#define FAST_MEM
#ifdef ANGRY_FAST
#pragma optimize( "", on )
#pragma GCC optimize("Ofast")
#define FAST_MEM
#endif
#include <iostream>
#include <cassert>
#include <list>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <list>
#include <unordered_map>
#include <fstream>
#include <memory>
#include <random>
#include <sstream>
#include <deque>
#include <variant>
#include <signal.h>

using namespace std;

//#define map unordered_map
#define cont continue
#define int long long
#define int128 int128_t
#ifdef ANGRY_FAST
#undef int
#endif
#define endl '\n'
#define endlf '\n'<<flush
#define pb push_back
#define pf push_front
#define ins insert
#define x first
#define sz size
#define era erase
#define pp pop_back
#define ppf pop_front
#define y second
#define fori(i, n) for(int i=0;i<(n);++i)
#define fori1(i, n) for(int i=1;i<(n);++i)
#define forir(i, n) for(int i=(n-1);i>=(0);--i)
#define foris(i, n) for(int i=0;i<(n.sz());++i)
#define foriab(i, a, b) for(int i=(a);i<(b);++i)
#define forirab(i, a, b) for(int i=(b)-1;i>=(a);--i)
#define VI vector<int>
#define DI deque<int>
#define VVI vector<VI>
#define VVVI vector<VVI>
#define MSLD map<string, ld>
#define SI set<int>
#define SPII set<PII>
#define SP set<PAR>
#define MII map<int, int>
#define MSI map<string, int>
#define PII pair<int, int>
#define PAR PII
#define VP vector<PAR>
#define PPIII pair<PII,int>
#define VPPIII vector<PPIII>
#define byte unsigned char
#define VB vector<byte>
#define VVB vector<VB>
#define VVP vector<VP>
#define MPIIVVI map<PII,VVI>
#define MPIIPII map<PII,PII>
#define VB vector<byte>
#define VVSI vector<VSI>
#define VVS vector<VS>
#define INF 2000000000000000000LL
#define BIG 1000000LL
#define EPS 1e-8
#define MIMII map<int, MII>
#define VMII vector<MII>
#define MIVI map<int, VI>
#define MISI map<int, SI>
#define MIPII map<int, PII>
#define PILD pair<int,ld>
#define MIVPII map<int, VPII>
#define UMIPII unordered_map<int, PII>
#define wall(x) ((x).begin()), ((x).end())
#define ld long double
#define MOD 1000000007LL
//#undef MOD
//#define MOD 998244353LL
#define VPII vector<PII>
#define VVPII vector<VPII>
#define VMIPII vector<MIPII>
#define VUMIPII vector<UMIPII>
#define MPIII map<PII, int>
#define VDB vector<DB>
#define VPIPII vector<PIPII>
#define PIPII pair<int, PII>
#define ava(X) cout<<(X)<<endl;exit(0);
#define VS vector<string>
#define VSI vector<SI>
#define MPIPIII map<PIPII, int>
#define VC vector<char>
#define MBB map<byte, byte>
#define SB set<byte>
#define ret return
#define VPIB vector<PIB>
#define PIB pair<int,byte>
#define VVPIPII vector<VPIPII>
#define DI deque<int>
#define DB deque<byte>
#define DDI deque<DI>
#define DDB deque<DB>
#define VPN vector<Node*>
#define sstream stringstream

#ifdef FAST_MEM
const signed MAX_MEM=100000000;
signed mpos=0;
char mem[MAX_MEM];
inline void* operator new(size_t n){
	mpos+=n;
	assert(mpos<=MAX_MEM);
	ret(void*)(mem+mpos-n);
}
void operator delete(void*)noexcept{}
void operator delete(void*,size_t)noexcept{}
#endif

template<class A> bool is_sorted(const A& arr){
	fori1(i,arr.sz()){
		if(arr[i-1]>arr[i]){
			ret 0;
		}
	}
	ret 1;
}
template<class I> I mgcd(I a,I b){
	while(b){
		a%=b;
		swap(a,b);
	}
	ret a;
}
template<class I> I gcd(I a,I b){
	if(a<0){
		a=-a;
	}
	if(b<0){
		b=-b;
	}
	ret mgcd(a,b);
}
template<class A, class B> bool rmax(A& a, const B& b){
	A t=b;
	if(a<t){
		a=move(t);
		ret 1;
	}
	ret 0;
}
template<class A, class B> bool rmin(A& a, const B& b){
	A t=b;
	if(a>t){
		a=move(t);
		ret 1;
	}
	ret 0;
}
template<class A, class B> bool rset(A& a, const B& b){
	A t=b;
	if(a!=t){
		a=move(t);
		ret 1;
	}
	ret 0;
}
template<class T, class U> istream& operator>>(istream& i, pair<T, U>& v){
	ret i>>v.x>>v.y;
}
template<class T, class U> ostream& operator<<(ostream& i, const pair<T, U>& v){
	ret i<<v.x<<' '<<v.y<<endl;
}
template<class T> istream& operator>>(istream& i, deque<T>& v){
	for(auto& x:v){
		i>>x;
	}
	ret i;
}
template<class T> istream& operator>>(istream& i, vector<T>& v){
	for(auto& x:v){
		i>>x;
	}
	ret i;
}
template<class T> ostream& operator<<(ostream& i, const set<T>& v){
	for(auto& x:v){
		i<<x<<' ';
	}
	ret i<<endl;
}
template<class T> ostream& operator<<(ostream& i, const vector<T>& v){
	for(auto& x:v){
		i<<x<<' ';
	}
	ret i<<endl;
}
template<class T> ostream& operator<<(ostream& i, const deque<T>& v){
	for(auto& x:v){
		i<<x<<' ';
	}
	ret i<<endl;
}
template<class T> vector<T>& operator+=(vector<T>& a, const vector<T>& b){
	for(const auto& x:b){
		a.pb(x);
	}
	ret a;
}
template<class T> set<T> merge(const set<T>& a, const set<T>& b){
	set<T> ans;
	for(auto x:a){
		ans.ins(x);
	}
	for(auto x:b){
		ans.ins(x);
	}
	ret ans;
}
template<class T> set<T> intersect(const set<T>& a, const set<T>& b){
	set<T> ans;
	if(a.sz()<b.sz()){
		for(auto x:a){
			if(b.count(x)){
				ans.ins(x);
			}
		}
	}else{
		for(auto x:b){
			if(a.count(x)){
				ans.ins(x);
			}
		}
	}
	ret ans;
}
int isqrt(int _){
	assert(_>=0);
	int l=0;
	int r=1LL<<30;
	while(r-l>1){
		int m=l+r>>1;
		if(m*m<=_){
			l=m;
		}else{
			r=m;
		}
	}
	ret l;
}
PII operator+(PII a, PII b){
	ret {a.x+b.x, a.y+b.y};
}
int fpowm(int i, int k){
	if(k){
		int t=fpowm((i*i)%MOD, k>>1);
		if(k&1){
			t*=i;
			t%=MOD;
		}
		ret t;
	}
	ret 1;
}
int invm(int k){
	ret fpowm(k, MOD-2);
}
int fpow(int a, int b){
	if(b){
		int t=fpow(a*a, b>>1);
		if(b&1){
			t*=a;
		}
		ret t;
	}
	ret 1;
}
ld mabs(ld x){
	if(x<0){
		ret -x;
	}
	ret x;
}
int mabs(int x){
	if(x<0){
		ret -x;
	}
	ret x;
}
int delup(int a, int b){
	int c=a/b;
	if(a%b){
		++c;
	}
	ret c;
}
int fpowmod(int a, int k, int MOO){
	if(k){
		int y=fpowmod(a, k/2, MOO);
		y=y*y;
		y%=MOO;
		if(k&1){
			y*=a;
			y%=MOO;
		}
		ret y;
	}
	ret 1;
}
int invmod(int k, int MOO){
	ret fpowmod(k, MOO-2, MOO);
}
#define YES cout<<"YES"<<endl;ret;
#define NO cout<<"NO"<<endl;ret;
#define NE1 cout<<"-1"<<endl;ret;
#define ZERO cout<<"0"<<endl;ret;
#define ANS(x) cout<<(x)<<endl;ret;
#define YESNO(x) if(x){YES;}NO;

PII limit_den(int m, int n, int l){
	int a=n, b=m%n, p=1, q=0, r=m/n, s=1, v=1;
	while(0<b&&q+a/b*s<=l){
		int na, nb, np, nq, nr, ns, nv;
		na=b;
		nb=a%b;
		np=r;
		nq=s;
		nr=p+a/b*r;
		ns=q+a/b*s;
		nv=-v;
		a=na;
		b=nb;
		p=np;
		q=nq;
		r=nr;
		s=ns;
		v=nv;
	}
	int t=p+(l-q)/s*r, u=q+(l-q)/s*s;
	if(2*b*u<=n){
		ret {r, s};
	}
	ret {t, u};
}
struct R{
	int a, b;
	R(int x, int y){
		assert(y);
		a=x;
		b=y;
		norm();
	}
	R(int x, int y, bool){
		a=x;
		b=y;
	}
	R(int x){
		a=x;
		b=1;
	}
	R(){
		a=0;
		b=1;
	}
	R& operator*=(const R& s){
		a*=s.a;
		b*=s.b;
		ret norm();
	}
	R& operator/=(const R& s){
		assert(s.a);
		a*=s.b;
		b*=s.a;
		ret norm();
	}
	R& operator+=(const R& s){
		int x=b;
		a*=s.b;
		b*=s.b;
		a+=s.a*x;
		ret norm();
	}
	R& operator-=(const R& s){
		int x=b;
		a*=s.b;
		b*=s.b;
		a-=s.a*x;
		ret norm();
	}
	R& norm(){
		int d=gcd(a, b);
		a/=d;
		b/=d;
		if(b<0){
			a*=-1;
			b*=-1;
		}
		ret *this;
	}
	int intval(){
		ret a/b;
	}
	R& limit_den(int l){
		PII aa=::limit_den(a, b, l);
		a=aa.x;
		b=aa.y;
		ret *this;
	}
};
R operator+(R a, const R& b){
	a+=b;
	ret a;
}
R operator-(R a, const R& b){
	a-=b;
	ret a;
}
R operator*(R a, const R& b){
	a*=b;
	ret a;
}
R operator/(R a, const R& b){
	a/=b;
	ret a;
}
bool operator==(const R&a,const R&b){
	ret a.a==b.a&&a.b==b.b;
}
bool operator!=(const R&a,const R&b){
	ret a.a!=b.a||a.b!=b.b;
}
bool operator<(const R&a,const R&b){
	ret a.a*b.b<b.a*a.b;
}
bool operator>(const R&a,const R&b){
	ret b<a;
}
bool operator<=(const R&a,const R&b){
	ret !(b<a);
}
bool operator>=(const R&a,const R&b){
	ret b<=a;
}
ostream& operator<<(ostream& o, const R& r){
	//ret o<<r.a<<'/'<<r.b<<endl;
	ret o<<(((ld)(r.a))/((ld)(r.b)));
}
istream& operator>>(istream& i, R& r){
	int x;
	i>>x;
	r.a=x;
	r.b=1;
	ret i;
}

#define has holds_alternative
struct suset{
	set<R> sr;
	bool inv=0;
	suset(){
	}
	suset(const set<R>& srr){
		sr=srr;
	}
	suset(const set<R>& srr,bool invv){
		sr=srr;
		inv=invv;
	}
	suset(R r){
		sr.ins(r);
	}
	suset(R r,bool invv){
		sr.ins(r);
		inv=invv;
	}
	void ins(R r){
		if(inv){
			sr.era(r);
		}else{
			sr.ins(r);
		}
	}
	void era(R r){
		if(inv){
			sr.ins(r);
		}else{
			sr.era(r);
		}
	}
};
suset merge(const suset& a,const suset& b){
	if(a.inv||b.inv){
		if(a.inv&&b.inv){
			return suset(intersect(a.sr,b.sr),1);
		}
		if(a.inv){
			suset ans=a;
			for(auto x:b.sr){
				ans.sr.era(x);
			}
			ret ans;
		}else{
			suset ans=b;
			for(auto x:a.sr){
				ans.sr.era(x);
			}
			ret ans;
		}
	}
	ret suset(merge(a.sr,b.sr));
}
suset intersect(suset a,suset b){
	a.inv^=1;
	b.inv^=1;
	suset ans=merge(a,b);
	ans.inv^=1;
	ret ans;
}
suset invert(suset a){
	a.inv^=1;
	ret a;
}
PII intersect(PII a,PII b){
	rmin(a.y,b.y);
	rmax(a.x,b.x);
	ret a;
}
bool eq(ld a,ld b){
	ret mabs(a-b)<EPS;
}
bool lo(ld a,ld b){
	ret a<b&&!eq(a,b);
}
bool leq(ld a,ld b){
	ret a<=b||eq(a,b);
}
bool gr(ld a,ld b){
	ret a>b&&!eq(a,b);
}
bool geq(ld a,ld b){
	ret a>=b||eq(a,b);
}
void solve();
void precalc();
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	precalc();
	signed t=1;
	//cin>>t;
	//srand(time(0));
	//srand(239);
	while(t--){
		solve();
	}
	ret 0;
}
///SOLUTION///
void precalc(){
}
