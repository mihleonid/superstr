#include "lcc_style.hpp"
#include "general.hpp"
MSTR middle(){
	MSTR top=str("cdefgzhijab");
	sqr.pb(top);

	MSTR it=add_down(top,8);
	it.pb('y');
	sqr.pb(it);
	add_both(it,1);
	it.ppf();
	it.pb('k');
	sqr.pb(it);
	add_both(it,1);
	it.ppf();
	it.pb('a');
	sqr.pb(it);
	add_both(it,1);
	it.ppf();
	it.pb('b');
	sqr.pb(it);
	add_both(it,1);
	it.ppf();
	add_down(it,2);

	MSTR it2=add_up(top,6);
	MSTR r=it2;
	it2.pf('a');
	it2.pf('b');
	sqr.pb(it2);
	add_down(it2,2);
	add_up(it2,6);
	ret r;
}
void up(){
	MSTR L14=str("zhijbalbacdeft");
	add_cyc(L14);
	MSTR L13=str("zhijbalbacdef");
	add_both(L13);
}
//j<k
void down(){
	MSTR L14=str("kabmjabn");
	add_cyc(L14);
	MSTR L13=str("kabmjab");
	add_both(L13);
}
void solve(){
	up();
	MSTR ci=middle();
	down();
	add_both(ci);
	print_all();
}
