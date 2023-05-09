#include "lcc_style.hpp"
#include "general.hpp"
void solve(){
	vector<MSTR> v;
	v.pb(str("a"));
	fori1(m,6){
		fori(a0,m+1){
		fori(a1,m+1){
		fori(a2,m+1){
		fori(a3,m+1){
		fori(a4,m+1){

			fori(b0,m+1){
			fori(b1,m+1){
			fori(b2,m+1){
			fori(b3,m+1){
			fori(b4,m+1){

				vector<MSTR> w(v.sz());
				foris(i,v){
					for(auto c:v[i]){
						fori(j,m){
							w[i].pb('c');
						}
						w[i].pb(c);
					}
					fori(j,m){
						w[i].pb('c');
					}
				}
				fori(i,a0){
					w[0].pp();
				}
				fori(i,a1){
					w[1].pp();
				}
				fori(i,a2){
					w[2].pp();
				}
				fori(i,a3){
					w[3].pp();
				}
				fori(i,a4){
					w[4].pp();
				}
				fori(i,b0){
					w[0].ppf();
				}
				fori(i,b1){
					w[1].ppf();
				}
				fori(i,b2){
					w[2].ppf();
				}
				fori(i,b3){
					w[3].ppf();
				}
				fori(i,b4){
					w[4].ppf();
				}
				print(w);
				ret;

				fori(i1,v.sz()){
					fori(j1,i1){
				fori(i2,v.sz()){
					fori(j2,i2){
						if(get(w[i1],w[j1])==get(w[i2],w[j2])){
							goto end;
						}
						if(get(w[i1],w[j1])>get(w[i2],w[j2])){
							if(get(v[i1],v[j1])<get(v[i2],v[j2])){
								goto end;
							}
						}
					}
				}
					}
				}
				print(w);
				ret;
				end:;

			}
			}
			}
			}
			}

		}
		}
		}
		}
		}
	}
}
