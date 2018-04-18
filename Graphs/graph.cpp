#include <iostream>
#include <vector>
#include <list>
#include <utility>

struct Node;

typedef std::pair<Node*, int> node_weigh;
typedef std::list<node_weigh> node_list;
typedef std::vector<Node*> node_vec;
typedef std::vector<node_vec> node_vec_of_vecs;

struct Node{
	char name, status;
	bool visited;
	int start_time, end_time;
	node_list neighbours;
	Node(char name){
		this->name = name;
		this->visited = 0;
		this->status = 'u'; //unvisited
	}
	void add_neighbour(Node* a, int w){
		node_weigh temp;
		temp.first = a;
		temp.second = w;
		neighbours.push_back(temp);
	}
	//TO_FILL
};

class Graph{
public:
	node_vec nodes;
	node_vec reversed_topological_list;
	Graph();
	void add_node(char a);
	void add_edge(Node* a, Node* b, int w, bool dir); //w is weigh, on dir: 0 is no direction, 1 is A->B
	int dfs(Node* u, int cur_time);
	int dfs_tl(Node* u, int cur_time); //dfs topological list
	void bfs(Node* s);
};

Graph::Graph(){
	node_vec nodes;
	this->nodes = nodes;
}

void Graph::add_node(char a){
	Node* t = new Node(a);
	nodes.push_back(t);
}

void Graph::add_edge(Node* a, Node* b, int w, bool dir){
	a->add_neighbour(b, w);
	if (! dir) b->add_neighbour(a, w);
}

int Graph::dfs(Node* u, int cur_time){ //works
	u->start_time = cur_time;
	cur_time++;
	u->status = 'i'; //in progress, yellow
	for(node_list::iterator it = u->neighbours.begin(); it != u->neighbours.end(); it++){
		if ( ((*it).first)->status == 'u' ){ //unvisited, gray
			cur_time = dfs( ((*it).first), cur_time);
			cur_time++;
		}
	}
	u->end_time = cur_time;
	u->status = 'd'; //done, black
	return cur_time;
}

int Graph::dfs_tl(Node* u, int cur_time){
	u->start_time = cur_time;
	cur_time++;
	u->status = 'i'; //in progress, yellow
	for(node_list::iterator it = u->neighbours.begin(); it != u->neighbours.end(); it++){
		if ( ((*it).first)->status == 'u' ){ //unvisited, gray
			cur_time = dfs( ((*it).first), cur_time);
			cur_time++;
		}
	}
	u->end_time = cur_time;
	u->status = 'd'; //done, black
	reversed_topological_list.push_back(u);
	return cur_time;
}

void Graph::bfs(Node* s){ //Works
	node_vec_of_vecs L (nodes.size());
	node_vec temp;
	Node* tmp;
	temp.push_back(s);
	L.at(0) = temp;
	s->visited = 1;
	temp.clear();
	for (int i = 0; i < nodes.size() - 1; i++){
		for(int j = 0; j < L.at(i).size(); j++){
			tmp = L.at(i).at(j);
			for (node_list::iterator it = tmp->neighbours.begin(); it != tmp->neighbours.end(); it++){
				if ( ! (*it).first->visited ){ //visited is 0
					(*it).first->visited = 1;
					L.at(i+1).push_back( (*it).first );
				}
			}
		}
		std::cout << "size of L at " << i << " : " << L.at(i).size() << '\n'; //TEST PURPOSES
	}
}

int main(int argc, char *argv[]) {
	Graph Test; //graph found at slides
	Test.add_node('A');
	Test.add_node('B');
	Test.add_node('C');
	Test.add_node('D');
	Test.add_node('E');
	Test.add_node('F');
	Test.add_node('G');
	Test.add_node('H');
	Test.add_edge(Test.nodes[0], Test.nodes[1], 1, 0);
	Test.add_edge(Test.nodes[0], Test.nodes[6], 1, 0);
	Test.add_edge(Test.nodes[0], Test.nodes[7], 1, 0);
	Test.add_edge(Test.nodes[1], Test.nodes[2], 1, 0);
	Test.add_edge(Test.nodes[1], Test.nodes[4], 1, 0);
	Test.add_edge(Test.nodes[1], Test.nodes[5], 1, 0);
	Test.add_edge(Test.nodes[2], Test.nodes[3], 1, 0);
	Test.add_edge(Test.nodes[3], Test.nodes[4], 1, 0);
	Test.add_edge(Test.nodes[3], Test.nodes[5], 1, 0);
	Test.add_edge(Test.nodes[5], Test.nodes[6], 1, 0);
	std::cout << Test.dfs(Test.nodes[0], 0) << '\n';
	Test.bfs(Test.nodes[0]);
	return 0;
}

