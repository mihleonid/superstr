#define MSTR deque<char>
#define OCTAGON_TEX "tex/octagon_template.tex"
#define ROTATED_OCTAGON_TEX "tex/octagon_template_rotated.tex"
#define HEXAGON_TEX "tex/hexagon_template.tex"
#define ROTATED_HEXAGON_TEX "tex/hexagon_template_rotated.tex"
#define PENTAGON_TEX "tex/pentagon_template.tex"
#define TETRAGON_TEX "tex/tetragon_template.tex"
#define TRIANGLE_TEX "tex/triangle_template.tex"
#define MAX_COLOR 6
#define LEN_LIMIT 30
#ifndef PRINT_ZEROS
#define WHITE_ZEROS
#endif
#ifndef NO_ROTATED
//#define ROTATED
#endif
vector<MSTR> sqr;
vector<pair<MSTR,MSTR>> reb;
void print(const MSTR& s){
	if(s.empty()){
		cout<<'-';
	}
	for(auto c:s){
		cout<<char(c);
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
int get(const MSTR& u,const MSTR& v){
	auto idx=[](const MSTR& u,const MSTR& v,int i)->char{ //TODO optimize
		if(i<v.sz()) ret  v[i];
		if(i==v.sz()) ret  '#';
		ret  u[i-v.size()-1];
	};
	VI pref(u.sz()+v.sz()+3);
	if(v==u){
		int n=u.sz();
		pref[0]=0;
		fori1(i,n){
			pref[i]=0;
			int cur=pref[i-1];
			while(u[i]!=u[cur]&&cur>0){
				cur=pref[cur-1];
			}
			if(u[i]==u[cur]){
				pref[i]=cur+1;
			}
		}
		ret pref[n-1];
	}
	int n=u.sz()+v.sz()+1;
	pref[0]=0;
	fori1(i,n){
		pref[i]=0;
		int cur=pref[i-1];
		while(idx(u,v,i)!=idx(u,v,cur)&&cur>0){
			cur=pref[cur-1];
		}
		if(idx(u,v,i)==idx(u,v,cur)){
			pref[i]=cur+1;
		}
	}
	ret pref[n-1];
}
int ovby(const MSTR& u,const MSTR& v,char c){
    int ovl=get(u,v);
    ret count(v.begin(),v.begin()+ovl,c);
}
/*
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
*/
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
		a.pb(c);
	}
	ret a;
}
MSTR ov(const MSTR& a,const MSTR& b){
	MSTR o;
	int x=get(a,b);
	fori(i,x){
		o.pb(b[i]);
	}
	ret o;
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
string to_string(const MSTR& s){
	string ss;
	for(auto x:s){
		ss.pb(x);
	}
	ret ss;
}
string to_string(const VI& v){
	vector<pair<char,int>> for_print;
	foris(i,v){
		if(v[i]){
			for_print.pb({i,v[i]});
		}
	}
	if(for_print.empty()){
		ret "0";
	}
	string ans="";
	if(for_print[0].y!=1){
		ans=to_string(for_print[0].y);
	}
	ans.pb(for_print[0].x);
	fori1(i,for_print.sz()){
		ans+=" + ";
		if(for_print[i].y!=1){
			ans+=to_string(for_print[i].y);
		}
		ans.pb(for_print[i].x);
	}
	ret ans;
}
void echo_v(const VI& v){
	cout<<to_string(v);
}
void draw_matrix(const vector<MSTR>& br){
	foris(i,br){
		foris(j,br){
			cout<<get(br[i],br[j])<<' ';
		}
		cout<<endl;
	}
}
void draw_graph(const vector<MSTR>& v, const string& tpl_path, const VPII& mord, char split=0){
	string tex=file_get_contents(tpl_path);
	int k=0;
	int n=v.sz();
	VI backtick(2*n*n,MAX_COLOR);
	VVS rebs(n,VS(n));
	fori(i,n){
		fori(j,n){
			if(split==0){
				rebs[i][j]=to_string(get_v(v[i],v[j]));
			}else{
				if(split==1){
					rebs[i][j]=to_string(get(v[i],v[j]));
				}else{
					rebs[i][j]=to_string(ovby(v[i],v[j],split));
				}
			}
		}
	}
	VS strs(n);
	fori(i,n){
		if(v[i].sz()>LEN_LIMIT){
			strs[i]="str"+to_string(i);
		}else{
			strs[i]=to_string(v[i]);
		}
	}
	int l=-1;
	int m=-1;
#ifdef WHITE_ZEROS
	fori(i,n){
		fori(j,n){
			int idx=i*n+j;
			if(rebs[i][j]=="0"){
				backtick[idx*2]=-1;
				backtick[idx*2+1]=-1;
			}
		}
	}
#endif
	foris(i,mord){
		int idx=mord[i].x*n+mord[i].y;
		backtick[idx*2]=i;
		backtick[idx*2+1]=i;
	}
	foris(i,v){
		foris(j,v){
			while(1){
				if(k==tex.sz()){
					ret;
				}
				if(tex[k]=='~'){
					++k;
					break;
				}
				if(tex[k]=='`'){
					cout<<"color"<<backtick[++l];
				}else{
					if(tex[k]=='@'){
						cout<<strs[++m];
					}else{
						cout<<tex[k];
					}
				}
				++k;
			}
#ifdef WHITE_ZEROS
			if(rebs[i][j]!="0"){
#endif
				cout<<rebs[i][j];
#ifdef WHITE_ZEROS
			}
#endif
		}
	}
	while(1){
		if(k==tex.sz()){
			ret;
		}
		if(tex[k]=='`'){
			cout<<"color"<<backtick[++l];
		}else{
			if(tex[k]=='@'){
				cout<<strs[++m];
			}else{
				cout<<tex[k];
			}
		}
		++k;
	}
}
void draw_graph(const vector<MSTR>& v, const VPII& mord,char split=0){
	VS paths(9);
	paths[3]=TRIANGLE_TEX;
	paths[4]=TETRAGON_TEX;
	paths[5]=PENTAGON_TEX;
	paths[6]=HEXAGON_TEX;
	paths[8]=OCTAGON_TEX;
#ifdef ROTATED
	paths[6]=ROTATED_HEXAGON_TEX;
	paths[8]=ROTATED_OCTAGON_TEX;
#endif
	draw_graph(v,paths[v.sz()],mord,split);
}
void draw_graph(const vector<MSTR>& v, const string& tpl_path,char split=0){
	VPII mord;
	draw_graph(v,tpl_path,mord,split);
}
void draw_graph(const vector<MSTR>& v,char split=0){
	VPII mord;
	draw_graph(v,mord,split);
}
MSTR merge(MSTR a,const MSTR& b){
	auto o=get(a,b);
	foriab(i,b.sz()-o,b.sz()){
		a.pb(b[i]);
	}
	ret a;
}
MSTR merge(const vector<MSTR>& v,const VI& ord){
	MSTR s=v[ord[0]];
	fori1(i,ord.sz()){
		s=merge(s,v[ord[i]]);
	}
	ret s;
}
MSTR merge(const vector<MSTR>& v){
	MSTR s=v[0];
	fori1(i,v.sz()){
		s=merge(s,v[i]);
	}
	ret s;
}
