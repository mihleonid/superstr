#define MSTR deque<char>
vector<MSTR> sqr;
vector<pair<MSTR,MSTR>> reb;
void print(const MSTR& s){
	if(s.empty()){
		cout<<'-';
	}
	for(auto c:s){
		cout<<char(c+'a');
	}
}
void print(const vector<MSTR>& v){
	for(auto s:v){
		print(s);
		cout<<' ';
	}
	cout<<endl;
}
void print(const vector<pair<MSTR,MSTR>>& v){
	for(auto s:v){
		print(s.x);
		cout<<' ';
		print(s.y);
		cout<<endl;
	}
}
void print_all(){
	print(sqr);
	print(reb);
}
MSTR suf(MSTR a){
	a.ppf();
	ret a;
}
MSTR pref(MSTR a){
	a.pp();
	ret a;
}
MSTR add_down(MSTR a,int c=-1){
	while(1){
		if(a.empty()){
			ret a;
		}
		if(c==0){
			ret a;
		}
		--c;
		reb.pb({a,suf(a)});
		a=suf(a);
	}
}
MSTR add_up(MSTR a,int c=-1){
	while(1){
		if(a.empty()){
			ret a;
		}
		if(c==0){
			ret a;
		}
		--c;
		reb.pb({pref(a),a});
		a=pref(a);
	}
}
void add_both(MSTR a,int c=-1){
	add_up(a,c);
	add_down(a,c);
}
void add_cyc(MSTR a){
	MSTR b=a;
	do{
		sqr.pb(b);
		MSTR c=suf(b);
		reb.pb({b,c});
		b.pb(b.front());
		b.ppf();
		reb.pb({c,b});
	}while(b!=a);
}
int get(MSTR a,MSTR b){
	int m=min(a.sz(),b.sz());
	while(--m){
		MSTR st=b;
		MSTR en=a;
		while(st.sz()!=m){
			st.pp();
		}
		while(en.sz()!=m){
			en.ppf();
		}
		if(st==en){
			break;
		}
	}
	ret m;
}
void add_ziza(const vector<MSTR>& v){
	for(auto x:v){
		sqr.pb(x);
	}
	add_up(v[0]);
	fori1(i,v.sz()){
		int o=get(v[i-1],v[i]);
		add_down(v[i-1],v[i-1].sz()-o);
		add_up(v[i],v[i].sz()-o);
	}
	add_down(v.back());
}
MSTR str(const string& s){
	MSTR a;
	for(auto c:s){
		a.pb(c-'a');
	}
	ret a;
}
MSTR ov(MSTR a,MSTR b){
	int m=min(a.sz(),b.sz());
	while(--m){
		MSTR st=b;
		MSTR en=a;
		while(st.sz()!=m){
			st.pp();
		}
		while(en.sz()!=m){
			en.ppf();
		}
		if(st==en){
			ret st;
		}
	}
	ret str("");
}
VI get_v(const MSTR& a,const MSTR& b){
	auto o=ov(a,b);
	VI v(255);
	for(auto x:o){
		++v[x];
	}
	while(v.sz()&&!v.back()){
		v.pp();
	}
	ret v;
}
void echo_v(const VI& v){
	if(v.empty()){
		cout<<0;
		ret;
	}
	cout<<v[0]<<'a';
	fori1(i,v.sz()){
		cout<<" + "<<v[i]<<char((char)i+'a');
	}
}
void pentagon(const vector<MSTR>& v){
	string tex=" \\begin{figure}[H] \\centering \\begin{tikzpicture}[>=latex, xscale=\\tkizx, yscale=\\tkizy] \\node[rectangle, draw, darkgreen, inner sep=5pt] (a) at (7,7) {\\color{red} stra}; \\node[rectangle, draw, darkgreen, inner sep=5pt] (b) at (11,4) {\\color{red} strb}; \\node[rectangle, draw, darkgreen, inner sep=5pt] (c) at (9,0) {\\color{red} strc}; \\node[rectangle, draw, darkgreen, inner sep=5pt] (d) at (5,0) {\\color{red} strd}; \\node[rectangle, draw, darkgreen, inner sep=5pt] (e) at (3,4) {\\color{red} stre}; \\path (a) to [bend left=15] node (ab) {%} (b); \\path (a) to [bend left=10] node (ac) {%} (c); \\path (a) to [bend left=10] node (ad) {%} (d); \\path (a) to [bend left=15] node (ae) {%} (e); \\path (b) to [bend left=15] node (ba) {%} (a); \\path (b) to [bend left=15] node (bc) {%} (c); \\path (b) to [bend left=10] node (bd) {%} (d); \\path (b) to [bend left=10] node (be) {%} (e); \\path (c) to [bend left=10] node (ca) {%} (a); \\path (c) to [bend left=15] node (cb) {%} (b); \\path (c) to [bend left=15] node (cd) {%} (d); \\path (c) to [bend left=10] node (ce) {%} (e); \\path (d) to [bend left=10] node (da) {%} (a); \\path (d) to [bend left=10] node (db) {%} (b); \\path (d) to [bend left=15] node (dc) {%} (c); \\path (d) to [bend left=15] node (de) {%} (e); \\path (e) to [bend left=15] node (ea) {%} (a); \\path (e) to [bend left=10] node (eb) {%} (b); \\path (e) to [bend left=10] node (ec) {%} (c); \\path (e) to [bend left=15] node (ed) {%} (d); \\draw[blue, ->] (a) -- (ab) -- (b); \\draw[blue, ->] (a) -- (ac) -- (c); \\draw[blue, ->] (a) -- (ad) -- (d); \\draw[blue, ->] (a) -- (ae) -- (e); \\draw[blue, ->] (b) -- (ba) -- (a); \\draw[blue, ->] (b) -- (bc) -- (c); \\draw[blue, ->] (b) -- (bd) -- (d); \\draw[blue, ->] (b) -- (be) -- (e); \\draw[blue, ->] (c) -- (ca) -- (a); \\draw[blue, ->] (c) -- (cb) -- (b); \\draw[blue, ->] (c) -- (cd) -- (d); \\draw[blue, ->] (c) -- (ce) -- (e); \\draw[blue, ->] (d) -- (da) -- (a); \\draw[blue, ->] (d) -- (db) -- (b); \\draw[blue, ->] (d) -- (dc) -- (c); \\draw[blue, ->] (d) -- (de) -- (e); \\draw[blue, ->] (e) -- (ea) -- (a); \\draw[blue, ->] (e) -- (eb) -- (b); \\draw[blue, ->] (e) -- (ec) -- (c); \\draw[blue, ->] (e) -- (ed) -- (d); \\end{tikzpicture} \\label{fig:gr1img1} \\end{figure}";
	int k=0;
	foris(i,v){
		foris(j,v){
			if(i==j){
				cont;
			}
			while(1){
				if(k==tex.sz()){
					ret;
				}
				if(tex[k]=='%'){
					++k;
					break;
				}
				cout<<tex[k];
				++k;
			}
			echo_v(get_v(v[i],v[j]));
		}
	}
	while(1){
		if(k==tex.sz()){
			ret;
		}
		cout<<tex[k];
		++k;
	}
}
MSTR merge(const MSTR& a,MSTR b){
	auto o=ov(a,b);
	MSTR r;
	fori(i,a.sz()-o.sz()){
		r.pb(a[i]);
	}
	for(auto x:b){
		r.pb(x);
	}
	ret r;
}
