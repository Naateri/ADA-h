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

typedef std::string str;
typedef unsigned int uint;
typedef std::vector<uint> uint_vec;

struct Path{
	str path;
	uint length = 0;
	bool done = 0;
};

bool allNodesChecked(Path* p, uint size){
	for(uint i = 0; i < size; i++){
		if ( ! (p+i)->done ) return 0;
	}
	return 1;
}

bool findSameLetter(str a, str b){
	int shortest;
	if (a.size() > b.size()) shortest = b.size();
	else shortest = a.size();
	for(int i = 0; i < shortest; i++){
		if ( a[i] == b[i] ) return 1;
	}
	return 0;
}

uint findInVector(node_vec vec, Node* elem){
	uint i = 0;
	while(vec.at(i) != elem){
		i++;
	}
	return i;
}

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
	uint Dijkstra(int start, int goal); //DISCLAIMER: Este para nada es el mejor Dijkstra y tiene (al menos) 69*10^(69) mejoras posibles de hecho
private:
	uint findByValue(char val);
	void Dijks(int strt_pnt, int& node, Path* p);
	void setMinNode(Path* p, uint size, int& minNode);
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

void Graph::setMinNode(Path* p, uint size, int& minNode){
	uint min = -1;
	for(uint i = 0; i < size; i++){
		if (!(p+i)->length || (p+i)->done ) continue;
		if (min > (p+i)->length){
			min = (p+i)->length;
			minNode = i;
		}
	}
	//p[findInVector(nodes_names, nodes_names.at(minNode))].done = 1;
	p[minNode].done = 1;
}

uint Graph::findByValue(char val){
	uint i = 0;
	while(nodes_names.at(i)->name != val){
		i++;
	}
	return i;
}

void Graph::Dijks(int strt_pnt, int& node, Path* p){
	Path* ptr; //para saber si ya paso por ese nodo o no
	int minNode;
	str newpath;
	uint prevLen;
	int i = 0;
	if (allNodesChecked(p, nodes_names.size())) return;
	//for(node_list::iterator it = node->neighbours.begin(); it != node->neighbours.end(); it++){
	for (int i = 0; i < this->size; i++){
		//if (p[findInVector(nodes, (*it)->m_nodes[node == (*it)->m_nodes[0]])].done) continue;
		if (nodes[strt_pnt][i] == 0){
			continue;
		}
		if (p[i].done) continue;
		/*ptr = &p[findInVector(nodes_names, nodes_names.at(i))];
		newpath = p[findInVector(nodes_names, nodes_names.at(i))].path + nodes_names.at(i)->name; //posible nuevo camino
		prevLen = p[findInVector(nodes_names, nodes_names.at(i))].length; */
		ptr = &p[i];
		newpath = p[i].path + nodes_names.at(i)->name;
		prevLen = p[i].length;
		if (ptr->done) continue;
		//if ( !ptr->length || ptr->length > prevLen + node->weights.at(i)){ //si la nueva distancia
		if ( !ptr->length || ptr->length > prevLen + nodes[strt_pnt][i]){ //si la nueva distancia
			ptr->length = prevLen + nodes[strt_pnt][i]; //es menor
			ptr->path = newpath;
		}
		/*} else { //arista bidireccional 
		if (node == (*it)->m_nodes[0]){ //el nodo esta en la primera pos de la arista
		ptr = &p[findInVector(m_nodes, (*it)->m_nodes[1])]; //nos lleva a la segunda
		newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[1]->m_data;
		//cout << "Connected to: " << (*it)->m_nodes[1]->m_data << endl;
		} else {
		ptr = &p[findInVector(m_nodes, (*it)->m_nodes[0])];
		newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[0]->m_data;
		//cout << "Connected to: " << (*it)->m_nodes[0]->m_data << endl;
		}
		prevLen = p[findInVector(m_nodes, node)].length; 
		if (ptr->done) continue;
		if ( !ptr->length || ptr->length > prevLen + (*it)->m_data){ //si la nueva distancia
		ptr->length = prevLen + (*it)->m_data; //es menor a la ya guardada
		ptr->path = newpath;
		}
		//}*/
		//i++;
	}
	//setMinNode(p, nodes.size(), minNode);
	setMinNode(p, nodes_names.size(), minNode);
	if (node == minNode){
		minNode = strt_pnt;
		Dijks(strt_pnt, minNode, p);
	}
	node = minNode;
	return;
}

uint Graph::Dijkstra(int start, int goal){
	Path* paths = new Path[nodes_names.size()];
	int copy = findInVector(nodes_names, nodes_names.at(start));
	/*paths[findInVector(nodes_names, nodes_names.at(start))].done = 1; //ya "paso" por el nodo de inicio
	paths[findInVector(nodes_names, nodes_names.at(start))].path = nodes_names.at(start)->name; //y el camino es el mismo nodo*/
	paths[start].done = 1; //ya "paso" por el nodo de inicio
	paths[start].path = nodes_names.at(start)->name; //y el camino es el mismo nodo
	for(uint i = 0; i < size; i++){
		std::cout << "start: " << start << '\n';
		std::cout << "copy: " << copy << '\n';
		std::cout << "i: " << i << '\n';
		Dijks(copy, start, paths);
		if (start == goal) break;
	}
	//uint res = paths[findInVector(nodes_names, nodes_names.at(goal))].length;
	uint res = paths[goal].length;
	//std::cout << "Camino: " << paths[findInVector(nodes_names, nodes_names.at(goal))].path << std::endl;
	std::cout << "Camino: " << paths[(goal)].path << std::endl;
	delete[] paths;
	return res;
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
	//std::cout << Test.dfs(Test.nodes[0], 0) << '\n';
	std::cout << Test.dfs(0, 0) << '\n';
	//Test.bfs(Test.nodes[0]);
	Test.bfs(0);
	std::cout << Test.Dijkstra(6, 3) << '\n';
	return 0;
}

