#include <iostream>
#include <vector>
#include <fstream>
#include <string>
// graph_template.exe <input.txt

using namespace std;

typedef string str;
typedef std::vector<int> int_vec;
typedef std::vector<int_vec> int_vec_of_vecs;


struct Node{
	int val, start_time, end_time;
	char status;
	bool visited;
	Node(int m_val){
		this->val = m_val;
		this->status = 'u';
		this->visited = 0;
	}
};

struct Edge  { 
	int v, w; //v -> node, w -> weigh
	Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class GRAPH {
private:
	// Implementation-dependent code
	//vector<vector <bool> > adj; //matriz
	int Vcnt, Ecnt;
	bool digraph; //si es dirigido o no
	
	
public:
	vector<vector <bool> > adj; //matriz
	vector<Node* > nodes_names;
	GRAPH(int V, bool digraph = false) : adj(V), Vcnt(V), Ecnt(0), digraph(digraph), nodes_names(V) {
		for (int i = 0; i < V; i++){
			adj[i].assign(V, false); //por defecto no es dirigido
			Node* temp = new Node(i);
			nodes_names.at(i) = temp;
		}
	}
	
	~GRAPH(){
		adj.clear();
	}
	int V() const{
		return Vcnt; //numero de vertices
	}
	int E() const{
		return Ecnt; //numero de aristas
	}
	bool directed() const; //si es direccionado
	void insert(Edge); //agregar true
	//void insert(int a, int b, int w);
	void remove(Edge); //agregar false
	bool edge(int, int);
	int dfs(int pos, int cur_time);
	void bfs(int pos);  //seems to be working
	/*class adjIterator {
	public:
		adjIterator(const GRAPH &, int); //devolver todos los vecinos de ese nodo
		int beg();
		int nxt();
		bool end();
	};*/
};

void GRAPH::insert(Edge e){
	int a = e.v, b = e.w;
	adj[a][b] = true;
	if (! digraph) adj[b][a] = true;
}

void GRAPH::remove(Edge e){
	int a = e.v, b = e.w;
	adj[a][b] = false;
	if (! digraph) adj[b][a] = false;
}

int GRAPH::dfs(int pos, int cur_time){ //works
	Node* u = nodes_names.at(pos), *t;
	u->start_time = cur_time;
	cur_time++;
	u->status = 'i'; //in progress, yellow
	cout << "Current node: " << u->val << endl;
	for (int i = 0; i < this->V(); i++){
		if (adj[pos][i] == true){
			t = nodes_names.at(i);
			if (t->status == 'u'){
				cur_time = dfs(i, cur_time);
				cur_time++;
			}
		}
	}
	//cout << "Node: " << u->val << " start time " << u->start_time << " end time " << cur_time << endl;
	u->end_time = cur_time;
	u->status = 'd'; //done, black
	return cur_time;
}

void GRAPH::bfs(int pos){  //seems to be working
	int_vec_of_vecs L (this->V());
	//node_vec temp;
	int_vec temp;
	Node* s, *t;
	int tmp;
	s = nodes_names.at(pos);
	temp.push_back(pos);
	L.at(0) = temp;
	s->visited = 1;
	cout << "Current node: " << s->val << endl;
	temp.clear();
	for (int i = 0; i < this->V(); i++){
		for(int j = 0; j < L.at(i).size(); j++){
			tmp = L.at(i).at(j);
			for (int k = 0; k < this->V(); k++){
				if (adj[tmp][k] != 0){
					t = nodes_names.at(k);
					if (! t->visited){
						cout << "Current node: " << t->val << endl;
						t->visited = 1;
						L.at(i+1).push_back(k);
					}
				}
			}
		}
		//std::cout << "size of L at " << i << " : " << L.at(i).size() << '\n'; //TEST PURPOSES
	}
}

class /*GRAPH::*/adjIterator {
	const GRAPH &G;
	int i, v;
	
public:
	adjIterator(const GRAPH &G, int v) :  G(G), v(v), i(-1) { }
	int beg() { i = -1; return nxt(); }
	int nxt() {
		for (i++; i < G.V(); i++)
			if (G.adj[v][i] == true) return i;
		return -1;
	}
	bool end() { return i >= G.V(); }
};

template <class Graph>
vector <Edge> edges(Graph &G) {
	int E = 0;
	vector <Edge> a(G.E());
	for (int v = 0; v < G.V(); v++) {
		typename Graph::adjIterator A(G, v);
		for (int w = A.beg(); !A.end(); w = A.nxt())
			if (G.directed() || v < w)
				a[E++] = Edge(v, w);
	}
	return a;
}

template <class Graph>
void show(const Graph &G) {
	for (int s = 0; s < G.V(); s++) {
		cout.width(2); cout << s << ":";
		/*typename Graph::*/adjIterator A(G, s);
		for (int t = A.beg(); !A.end(); t = A.nxt()) { 
			cout.width(2); cout << t << " "; 
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	/*input_txt file;
	file.open("input.txt");*/
	int nV, nE;
	int a, b;
	float w;
	cin >> nV >> nE;
	GRAPH test(nV, true);
	for (int e = 0; e < nE; e++){
		Edge temp;
		cin >> a >> b >> w;
		temp.v = a;
		temp.w = b;
		test.insert(temp);
		
	}
	/*Edge temp;
	temp.v = 0;
	temp.w = 1;
	GRAPH test(4);
	test.insert(temp);*/
	/*test.insert(1, 2, 0);
	test.insert(2, 3, 0);*/
	show<GRAPH>(test);
	cout << "DFS----------\n";
	std::cout << "DFS on node 0: " << test.dfs(2, 0) << endl;
	cout << "BFS---------------\n";
	test.bfs(2);
	return 0;
}
