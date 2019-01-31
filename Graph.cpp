///////////////////////////                 Graph                 ///////////////////////

#include<iostream>
#include<string.h>
#include<iterator>
#include<algorithm>
#include<map>
#include<utility>
#include<set>
#include<queue>
#include<stack>
#define INF INT_MAX
using namespace std;

class disjointSet {
	int n;
	int *parent,*rank,*size;
	public:
	disjointSet(int n){
		parent= new int[n];
		rank = new int[n];
		size = new int[n];
		for(int i = 0;i<n;i++)
			makeSet(i);
		this->n=n;
	}
	void makeSet(int x){
		parent[x] = x;
		rank[x] = 1;
		size[x] = 1;
	}
	int findSet(int x){
		if(parent[x]==x)
			return x;
		parent[x] = findSet(parent[x]);
		return parent[x];
	}
	bool unionSet(int x,int y){
		if(parent[x]==parent[y]){
			return false;
		}
		int parX = parent[x];
		int parY = parent[y];
		if(rank[parX]>=rank[parY]){
			parent[parY] = parent[parX];
			if(rank[parX]==rank[parY])
				rank[parX]++;
			size[parX]+=size[parY];
		}
		else{
			parent[parX] = parent[parY];
			size[parY]+=size[parX];
		}
		return true;
	}
};

bool compare( pair<int,pair<int,int> > e1, pair<int,pair<int,int> > e2){
	return e1.second.second<e2.second.second;
}
	
class Graph{
	int v;
	set<int> vertices;
	vector<pair<int,pair<int,int> > > edges;
	int e;
	public:
	map<int,map<int,int> > adj;
	
	Graph(int v,int e){
		this->v = v;
		this->e = e;
	}
	void addEdge(int u,int v,bool bidir){
		vertices.insert(u);
		vertices.insert(v);
		adj[u][v] = 1;
		edges.push_back(make_pair(u,make_pair(v,1)));
		if(bidir){
			adj[v][u] = 1;
			edges.push_back(make_pair(v,make_pair(u,1)));
		}
		cout<< u <<" is connected to "<< v<< endl;
	}
	void addEdge(int u,int v,int wt,bool bidir){
		vertices.insert(u);
		vertices.insert(v);
		adj[u][v] = wt;
		edges.push_back(make_pair(u,make_pair(v,wt)));
		if(bidir){
			adj[v][u] = wt;
			edges.push_back(make_pair(v,make_pair(u,wt)));
		}
		cout<< u <<" is connected to "<< v<< endl;
	}
	void dfsUtil(int src, map<int,map<int,int> > adj,map<int,bool> &vis){
		vis[src] = true;
		cout<< src<< " ";
		for(auto it:adj[src]){
			//cout<< it.first<< endl;
			if(!vis[it.first])
				dfsUtil(it.first,adj,vis);
		}		
	}
	void dfs(){
		map<int,bool> visited;
		
		for(auto it: vertices){
			//cout<< it.first<< endl;
			visited[it] = false;
		}
		for(auto it:vertices)
			if(!visited[it])
				dfsUtil(it,adj,visited);
		cout<< endl;
	}
	void bfs(){
		map<int,bool> visited;
		for(auto it:vertices){
			visited[it] = false;
		}
		for(auto it:vertices){
			if(!visited[it]){
				queue<int> q;
				q.push(it);
				visited[it] = true;
				while(!q.empty()){
					int curr = q.front();
					q.pop();
					cout<< curr<< " ";
					for(auto it:adj[curr])
						if(!visited[it.first]){
							q.push(it.first);
							visited[it.first] = true;
						}
				}
			}
		}
		cout<< endl;
	}
	void topologicalUtil(int src,stack<int> &s,map<int,bool> &visited){
		if(visited[src])
			return;
		visited[src] = true;
		for(auto it:adj[src]){
			if(!visited[it.first]){
				topologicalUtil(it.first,s,visited);
			}
		}
		s.push(src);
	}
	void topologicalSort(){
		cout<< endl<< "Topological Sort is : ";
		stack<int> stk;
		map<int,bool> visited;
		for(auto it:vertices){
			visited[it] = false;
			//cout<< it.first<< " ";
		}
		//cout<< endl;
		for(auto it: vertices)
			topologicalUtil(it,stk,visited);
		while(!stk.empty()){
			cout<< stk.top()<< " ";
			stk.pop();
		}
		cout<< endl;
	}
	
	void djikstra(int src){
		priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
		q.push(make_pair(0,src));
		map<int,int> dist,par;
		for(auto it:vertices){
			dist[it] = INF;
			par[it] = INF;
		}
		dist[src]=0;
		map<int,bool> processed;
		while(!q.empty()){
			bool flag = false;
			pair<int,int> curr;
			while(!q.empty()){
				curr = q.top();
				q.pop();
				if(processed.find(curr.second)==processed.end()){
					flag = true;
					break;
				}
			}
			if(!flag)
				break;
			int srce = curr.second;
			int wt = curr.first;
			processed[curr.second] = true;
			for(auto it:adj[srce]){
				if(dist[it.first]>(wt+it.second)){
					dist[it.first] = wt+it.second;
					q.push(make_pair(dist[it.first],it.first));
					par[it.first] = srce;
				}
			}
		}
		for(auto it:vertices){
			cout<< it<< " "<< dist[it]<<" "<< par[it]<< endl;
		}
	}
	
	void prims(){
		priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
		map<int,int> par,dist;
		int src = *(vertices.begin());
		q.push(make_pair(0,src));
		map<int,bool> processed;
		vector<pair<int,int> > mst;
		
		for(auto it: vertices){
			par[it] = INF;
			dist[it] = INF; 
		}
		while(!q.empty()){
			pair<int,int> curr;
			bool flag = false;
			while((!flag) && (!q.empty())){
				curr = q.top();
				q.pop();
				if(processed.find(curr.second) == processed.end())
					flag = true;
			}
			if(!flag)
				break;
			int srce = curr.second;
			processed[srce] = true;
			if(srce!=src){
				mst.push_back(make_pair(srce,par[srce]));
			}
		for(auto it:adj[srce]){
				if((processed.find(it.first)==processed.end()) && dist[it.first]>it.second){
					dist[it.first] = it.second;
					par[it.first] = srce;
					q.push(make_pair(it.second,it.first));
				}
			}
		}
		for(auto it:mst){
			cout<< it.first<< "->"<< it.second<< endl;
		}
	}
	
	void bellmanford(int src){
		map<int,int> par,dist;
		for(auto it:vertices){
			par[it] = INF;
			dist[it] = INF;
		}
		dist[src] = 0;
		for(int i = 0;i<vertices.size()-1;i++){
			//cout<< "here";
			for(auto it:edges){
				//cout<< "here";
				int u = it.first;
				int v = it.second.first;
				//cout<< "arrived here";
				if((long long int)dist[v]>((long long int)dist[u]+adj[u][v])){
					//cout<< dist[v]<<" "<< dist[u]+adj[u][v]<< endl;
					dist[v] = dist[u]+adj[u][v];
					par[v] = u;
				}
			}
		}
		bool flag = false;
		for(auto it:edges){
			int u = it.first;
			int v = it.second.first;
			if((long long int)dist[v]> (long long int)dist[u]+adj[u][v]){
				flag = true;
				break;
			}
		}
		if(flag){
			cout<<"Negative cycle present"<< endl;
			return;
		}
		for(auto it:vertices){
			cout<< it<< " "<< dist[it]<< " "<< par[it]<< endl;
		}
	}
	void floydWarshall(){
		int dist[v][v],par[v][v];
		for(int i =0;i<v;i++)
			for(int j =0;j<v;j++){
				dist[i][j] = INF;
				par[i][j] = INF;
			}
		//memset(dist,INF,sizeof(dist));
		//memset(par,INF,sizeof(par));
		
		for(auto it:adj){
			for(auto it2:adj[it.first]){
				dist[it.first][it2.first] = it2.second;
				par[it.first][it2.first] = it.first;
			}
		}
		for(auto it:vertices)
			dist[it][it] = 0;
		for(int k = 0;k<v;k++){
			for(int i = 0;i<v;i++){
				//if(i!=j)
				for(int j = 0;j<v;j++){
					
					if((dist[i][k]!=INF && dist[k][j]!=INF) && dist[i][j]>(dist[i][k]+dist[k][j])){
						dist[i][j] = dist[i][k]+dist[k][j];
						par[i][j] = k;
					}
				}
			}
		}
		for(int i = 0;i<v;i++,cout<< endl)
			for(int j = 0;j<v;j++)
				cout<< dist[i][j]<< " ";
		for(int i = 0;i<v;i++,cout<< endl)
			for(int j = 0;j<v;j++)
				cout<< par[i][j]<< " ";
		return;
	}
	
	void kruskal(){
		disjointSet d(v);
		sort(edges.begin(),edges.end(),compare);
		vector<pair<int,pair<int, int> > > MST;
		for(auto it:edges){
			if(d.unionSet(it.first,it.second.first)){
				MST.push_back(it);
			}
			if(MST.size()>=(v-1))
				break;
		}
		for(auto it:MST){
			cout<< it.first<< "->"<< it.second.first<< "("<< it.second.second<< ")"<< endl;
		}
	}
	bool cycleDetectedUndirected(){
		disjointSet d(v);
		for(int it =0;it<edges.size();it+=2){
			//cout<< "checking "<< it.first<< " and "<< it.second.first<< endl;
			if(!d.unionSet(edges[it].first,edges[it].second.first))
				return true;
		}
		return false;
	}
	bool cycleDetectedUndirected2Util(int src,int par,map<int,bool> &visited){
		visited[src] = true;
		bool cycle = false;
		for(auto it:adj[src]){
			if(visited[it.first] && it.first!=par)
				return true;
			if(!visited[it.first])
				cycle= cycle||cycleDetectedUndirected2Util(it.first,src,visited);
		}
		return cycle;
	}
	bool cycleDetectedUndirected2(){
		map<int,bool> visited;
		for(auto it:vertices)
			visited[it] = false;
		visited[*vertices.begin()] = true;
		return cycleDetectedUndirected2Util(*(vertices.begin()),-1,visited);
	}
	bool cycleDetectedDirectedUtil(int src,map<int,int> &visited){
		visited[src] = 1;
		bool cycle = false;
		for(auto it:adj[src]){
			if(visited[it.first]==1)
				return true;
			if(!visited[it.first])
				cycle = cycle || cycleDetectedDirectedUtil(it.first,visited);
		}
		visited[src] = 2;
		return cycle;
	}
	bool cycleDetectedDirected(){
		map<int,int> visited;
		for(auto it:vertices)
			visited[it] = 0;
		bool ans = false;
		for(auto it:vertices){
			ans = ans || cycleDetectedDirectedUtil(it,visited);
		}
		return ans;
	}
};

int main(){
	int v;
	v = 8;
	int e;
	e= 8;
	Graph g(v,e);
//	g.addEdge(0,1,3,0);
//	g.addEdge(0,3,15,0);
//	g.addEdge(0,2,6,0);
//	g.addEdge(1,2,-2,0);
//	g.addEdge(2,3,2,0);
//	g.addEdge(3,0,1,0);
	
	g.addEdge(0,1,1);
	g.addEdge(1,2,1);
	g.addEdge(0,2,1);
	g.addEdge(3,2,1);
	g.addEdge(3,4,1);
	g.addEdge(4,5,1);
	g.addEdge(4,6,1);
	g.addEdge(4,7,1);
	cout<< endl<< "dfs traversal is:"<< endl;
	g.dfs();
	cout<< endl<< "dfs traversal is:"<< endl;
	g.bfs();
	g.topologicalSort();
	cout<< endl<< "shortest distance using djikstra: "<< endl;
	g.djikstra(0);
	cout<< endl<< "shortest distance using bellmanford: "<< endl;
	g.bellmanford(0);
	cout<< endl<< "MST edges are: "<< endl;
	g.prims();
	g.floydWarshall();
	g.kruskal();
	if(g.cycleDetectedUndirected())
		cout<< "Cycle Present"<< endl;
	else
		cout<< "No cycle present"<< endl;
	if(g.cycleDetectedUndirected2())
		cout<< "Cycle Present"<< endl;
	else
		cout<< "No cycle present"<< endl;
	return 0;
}
