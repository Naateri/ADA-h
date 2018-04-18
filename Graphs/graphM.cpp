#include <iostream>
#include <vector>
#include <list>
#include <utility>

//adjacency matrix

struct Node;
typedef std::vector<Node*> node_vec;
typedef std::vector<node_vec> node_vec_of_vecs;
typedef std::vector<int> int_vec;
typedef std::vector<int_vec> int_vec_of_vecs;
typedef Node* node_ptr;

void print_matrix(int a, int b, int** c){
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			std::cout << c[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

struct Node{
	char name, status;
	bool visited;
	int start_time, end_time;
	Node(char name){
		this->name = name;
		this->visited = 0;
		this->status = 'u'; //unvisited
	}
	//TO_FILL
};

class Graph{
	int size;
public:
	int** nodes; //matrix
	node_vec nodes_names;
	node_vec reversed_topological_list;
	Graph(int n);
	void add_node(char a); //below: pos_a is the position of a within the nodes_names vector, pos_b the position of b within the nodes_names vector
	void add_edge(int pos_a, int pos_b, int w, bool dir); //w is weigh, on dir: 0 is no direction, 1 is A->B
	int dfs(int pos, int cur_time);
	int dfs_tl(Node* u, int cur_time); //dfs topological list
	void bfs(int pos);
};

Graph::Graph(int n){
	nodes = new int*[n];
	for (int i = 0; i < n; i++){
		(nodes)[i] = new int[n];
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			nodes[i][j] = 0;
		}
	}
	this->size = n;
}

void Graph::add_node(char a){
	Node* t = new Node(a);
	nodes_names.push_back(t);
}

void Graph::add_edge(int pos_a, int pos_b, int w, bool dir){
	nodes[pos_a][pos_b] = w;
	if (! dir) nodes[pos_b][pos_a] = w;
}

int Graph::dfs(int pos, int cur_time){ //works
	Node* u = nodes_names.at(pos), *t;
	u->start_time = cur_time;
	cur_time++;
	u->status = 'i'; //in progress, yellow
	for (int i = 0; i < this->size; i++){
		if (nodes[pos][i] != 0){
			t = nodes_names.at(i);
			if (t->status == 'u'){
				cur_time = dfs(i, cur_time);
				cur_time++;
			}
		}
	}
	u->end_time = cur_time;
	u->status = 'd'; //done, black
	return cur_time;
}

void Graph::bfs(int pos){  //seems to be working
	int_vec_of_vecs L (nodes_names.size());
	//node_vec temp;
	int_vec temp;
	Node* s, *t;
	int tmp;
	s = nodes_names.at(pos);
	temp.push_back(pos);
	L.at(0) = temp;
	s->visited = 1;
	temp.clear();
	for (int i = 0; i < this->size; i++){
		for(int j = 0; j < L.at(i).size(); j++){
			tmp = L.at(i).at(j);
			for (int k = 0; k < this->size; k++){
				if (nodes[tmp][k] != 0){
					t = nodes_names.at(k);
					if (! t->visited){
						t->visited = 1;
						L.at(i+1).push_back(k);
					}
				}
			}
		}
		std::cout << "size of L at " << i << " : " << L.at(i).size() << '\n'; //TEST PURPOSES
	}
}


int main(int argc, char *argv[]) {
	Graph Test(8); //graph found at slides
	Test.add_node('A');
	Test.add_node('B');
	Test.add_node('C');
	Test.add_node('D');
	Test.add_node('E');
	Test.add_node('F');
	Test.add_node('G');
	Test.add_node('H');
	Test.add_edge(0, 1, 1, 0);
	Test.add_edge(0, 6, 1, 0);
	Test.add_edge(0, 7, 1, 0);
	Test.add_edge(1, 2, 1, 0);
	Test.add_edge(1, 4, 1, 0);
	Test.add_edge(1, 5, 1, 0);
	Test.add_edge(2, 3, 1, 0);
	Test.add_edge(3, 4, 1, 0);
	Test.add_edge(3, 5, 1, 0);
	Test.add_edge(5, 6, 1, 0);
	std::cout << Test.dfs(0, 0) << '\n';
	Test.bfs(0);
	return 0;
}

