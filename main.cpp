#include "lcc_style.hpp"
#include "general.hpp"
void solve(){
	/*
	vector<MSTR> v;
	v.pb(str("aaaaab"));
	v.pb(str("aaabaa"));
	v.pb(str("aabaaba"));
	v.pb(str("baabaa"));
	v.pb(str("abaaaa"));
	*/
	vector<MSTR> br;
	br.pb(str("aaaaabbbbbbbbbbb"));
	br.pb(str("aaabbbbbbbbbbbaa"));
	br.pb(str("aabbbbbbbbbbbaabbbbbbbbbbba"));
	br.pb(str("bbbbbbbbbbbaabbbbbbbbbbbaa"));
	br.pb(str("abbbbbbbbbbbaaaa"));
	draw_graph(br,PENTAGON_TEX);
	ret;
	//VI ord={3,2,1,4,0};
	VI ord={0,1,2,3,4};
	MSTR s=br[ord[0]];
	fori1(i,ord.sz()){
		s=merge(s,br[ord[i]]);
	}
	print(s);
	ret;
	/*
	br.pb(str("aaaaab"));
	br.pb(str("aaabaa"));
	br.pb(str("aabaaba"));
	br.pb(str("baabaa"));
	br.pb(str("abaaaa"));
	*/
	/*
	br.pb(str("aaabaab"));
	br.pb(str("baabaaba"));
	br.pb(str("abaabaa"));
	br.pb(str("aabaaaa"));
	/*
	br.pb(str("ccaccaccaccaccaccb"));
	br.pb(str("ccaccaccaccbccaccac"));
	br.pb(str("ccaccaccbccaccaccbccac"));
	br.pb(str("ccbccaccaccbccaccacc"));
	br.pb(str("ccaccbccaccaccaccac"));
	*/
	foris(i,br){
		foris(j,br){
			cout<<get(br[i],br[j])<<' ';
		}
		cout<<endl;
	}
	//add_ziza(br);
	//print_all();
	/*
	*/
}
