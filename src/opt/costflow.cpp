#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<complex>
using namespace std;

template <class W>
struct MinCostFlow {
	struct Edge {
		int u, v, cap, nxt;
		W cost;
		Edge &set(int _u,int _v,int _nxt,int _cap,W _cost) {
			u=_u;v=_v;cost=_cost;cap=_cap;nxt=_nxt;
			return *this;
		}
	};

	vector<Edge> e;
	vector<int> vst, head, que;
	vector<W> dist;
	vector<bool> mark;
	int st, en, N, tot, ret;
	W val, INF, EPS;

	void init(int _s, int _t, int _n, W eps, W inf) {
		head.resize(_n);
		vst.resize(_n);
		dist.resize(_n);
		que.resize(_n);
		mark.resize(_n);
		st=_s;en=_t;N=_n;EPS=eps;INF=inf;
		ret=0;val=0;tot=0;fill(head.begin(),head.end(),-1);
	}

	int dfs(int v, int cap) {
		if(v == en) {
			val += cap * dist[st];
			return cap;
		}
		vst[v]=true;
		int flow=0;
		for(int i=head[v];i!=-1;i=e[i].nxt)
			if(e[i].cap && ! vst[e[i].v] && abs(dist[e[i].v]+e[i].cost-dist[v])<=EPS) {
				int det = dfs(e[i].v, min(cap, e[i].cap));
				if(det) {
					e[i].cap -= det; e[i^1].cap += det; flow += det;
					if(!(cap-=det))break;
				}
			}
		return flow;
	}
	int relabel() {
		W det = INF;
		for(int i=0;i<N;++i)
			if(vst[i])
				for(int j=head[i];j!=-1;j=e[j].nxt)
					if(e[j].cap && !vst[e[j].v])
						det = min(det, dist[e[j].v]+e[j].cost-dist[i]);
		if(det==INF) return false;
		for(int i=0;i<N;++i)
			if(vst[i])dist[i]+=det;
		return true;
	}
	int spfa() {
		queue<int> que;
		fill(vst.begin(),vst.end(),-1);
		vst[en] = -2;
		fill(dist.begin(),dist.end(),INF); dist[en]=0;
		que.push(en);
		fill(mark.begin(),mark.end(),false);
		while(!que.empty()) {
			int u = que.front(); que.pop();
			mark[u]=false;
			for(int i=head[u];i!=-1;i=e[i].nxt)
				if(e[i^1].cap && dist[u]+e[i^1].cost<dist[e[i].v]) {
					dist[e[i].v]=dist[u]+e[i^1].cost;vst[e[i].v]=i^1;
					if(!mark[e[i].v]) {
						mark[e[i].v]=true;
						que.push(e[i].v);
					}
				}
		}
	}
	void insert(int u, int v,int cap, W cost) {
		e.push_back(Edge().set(u,v,head[u],cap,cost)); head[u]=tot++;
		e.push_back(Edge().set(v,u,head[v],0,-cost)); head[v]=tot++;
	}
	void insert(int u, int v, int lo, int hi, W cost) {
		if(hi > lo)
			insert(u, v, hi-lo, cost);
		if(lo > 0) {
			insert(st, v, lo, cost);
			insert(u, en, lo, 0);
		}
	}
	W work() {
		spfa();
		do {
			do {
				fill(vst.begin(),vst.end(),false);
			} while(dfs(st, 2147483647));
		} while(relabel());
		return val;
	}
};
