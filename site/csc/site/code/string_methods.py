#def overlap(first_string, second_string):
#    for i in range(min(len(first_string), len(second_string)), 0, -1):
#        if first_string[-i:] == second_string[0:i]:
#            return i
#
#    return 0
def overlap(u,v):
	def idx(u,v,i):
		if i<len(v):
			return v[i]
		if i==len(v):
			return '#'
		return u[i-len(v)-1]
	pref=[]
	for i in range(len(u)+len(v)+3):
		pref.append(0)
	if v==u:
		n=len(u)
		return n # TODO decide to do non trivial overlap, but old implementation uses trivial
		pref[0]=0
		for i in range(1,n):
			pref[i]=0
			cur=pref[i-1]
			while u[i]!=u[cur] and cur>0:
				cur=pref[cur-1]
			if u[i]==u[cur]:
				pref[i]=cur+1
		return pref[n-1]
	n=len(u)+len(v)+1;
	pref[0]=0;
	for i in range(1,n):
		pref[i]=0
		cur=pref[i-1]
		while idx(u,v,i)!=idx(u,v,cur) and cur>0:
			cur=pref[cur-1]
		if idx(u,v,i)==idx(u,v,cur):
			pref[i]=cur+1
	return pref[n-1]

def prefix(first_string, second_string):
    return len(first_string) - overlap(first_string, second_string)


def suffix(first_string, second_string):
    return len(second_string) - overlap(first_string, second_string)
