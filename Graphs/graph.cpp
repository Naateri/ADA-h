#include <iostream>
#include <vector>
#include <list>
#include <utility>

struct Node;

typedef std::pair<Node*, int> node_weigh;
typedef std::list<node_weigh> node_list;
typedef std::vector<node_list> adjacency_vec;
typedef std::vector<Node*> node_vec;

struct Node{
	int val;
	node_list neighbours;
	Node(int x){
		this->val = x;
	}
	bool add_neighbour(Node* a, int w){
		node_weigh temp;
		temp.first = a;
		temp.second = w;
		neighbours.push_back(temp);
	}
	//TO_FILL
};

class Graph{
	node_vec nodes;
public:
	Graph();
	void add_node(Node* a);
	void add_edge(Node* a, Node* b, int w); //w is weigh
};

Graph::Graph(){
	node_vec nodes;
	this->nodes = nodes;
}

void Graph::add_node(Node* a){
	nodes.push_back(a);
}


int main(int argc, char *argv[]) {
	
	
	return 0;
}

