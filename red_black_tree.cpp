#include <iostream>
#include <list>

struct RBNode;

typedef std::list<RBNode*> node_list;

struct RBNode{
	int m_x;
	bool colour; //0 = red, 1 = black
	RBNode* m_nodes[2];
	RBNode(int x){
		this->m_x =x;
		m_nodes[0] = m_nodes[1] = 0;
		this->colour = 0;
	}
};

class RedBlack{
	node_list path;
	void recolor(RBNode* v);
	void right_rotate(RBNode** p);
	void left_rotate(RBNode** p);
public:
	RBNode* root;
	RedBlack();
	bool find(int x, RBNode**& p);
	bool insert(int x);
	bool remove(int x);
	void inorder(RBNode* p);
	RBNode** Rep(RBNode** p);
	void printTree(RBNode* p);
};

RedBlack::RedBlack(){
	this->root = 0;
}

void RedBlack::printTree(RBNode* p){
	if (!p) return;
	std::cout << "Valor: " << p->m_x << " Color: ";
	if (p->colour) std::cout << "Negro\n"; 
	else std::cout << "Rojo\n";
	if (p->m_nodes[0]) std::cout << "Hijo izquierdo: " << p->m_nodes[0]->m_x << ' ';
	if (p->m_nodes[1]) std::cout << "Hijo derecho: " << p->m_nodes[1]->m_x << ' ';
	printTree(p->m_nodes[0]);
	printTree(p->m_nodes[1]);
}

bool RedBlack::find(int x, RBNode**& p){
	path.clear();
	for(p = &root; *p && (*p)->m_x != x; p = &( (*p)->m_nodes[ (*p)->m_x < x ] ) ){
		path.push_back(*p);
	}
	return ( (*p) && (*p)->m_x == x );
}

bool RedBlack::insert(int x){
	RBNode** v;
	if (find (x, v) ) return 0;
	*v = new RBNode(x);
	recolor(*v);
}

void RedBlack::recolor(RBNode* v){
	if ( v == root){
		root->colour = 1;
		return;
	}
	RBNode* p, *g_parent, *uncle;
	node_list::iterator it = path.end();
	--it;
	p = *(it--);
	if (p->colour) return;
	g_parent = *(it);
	uncle = g_parent->m_nodes[1];
	if (uncle && !uncle->colour){
		p->colour = 1;
		uncle->colour = 1;
		g_parent->colour = 0;
		recolor(g_parent);
	} else {
		p->colour = 1;
		g_parent->colour = 0;
		right_rotate(&g_parent);
		//left_rotate(&g_parent);
	}
}

void RedBlack::right_rotate(RBNode** p){
	RBNode* father, *gfather, *temp, *bl;
	node_list::iterator it = path.end();
	while(*p != *(it) ){
		it--;
	}
	gfather = *p;
	father = gfather->m_nodes[1];
	if ( (*it) != this->root ) {
		it--;
		temp = *(it);
	}
	bl = father->m_nodes[0];
	father->m_nodes[0] = gfather;
	gfather->m_nodes[1] = bl;
	if (root == gfather) root = father;
	else {
		if (father->m_x < temp->m_x ) temp->m_nodes[0] = father;
		else temp->m_nodes[1] = father;
	}
}

void RedBlack::left_rotate(RBNode** p){
	RBNode* father, *gfather, *temp, *bl;
	node_list::iterator it = path.end();
	while(*p != *(it) ){
		it--;
	}
	gfather = *p;
	father = gfather->m_nodes[0];
	if ( (*it) != this->root ) {
		it--;
		temp = *(it);
	}
	bl = father->m_nodes[1];
	father->m_nodes[1] = gfather;
	gfather->m_nodes[0] = bl;
	if (root == gfather) root = father;
	else {
		if (father->m_x < temp->m_x ) temp->m_nodes[0] = father;
		else temp->m_nodes[1] = father;
	}
}


int main(int argc, char *argv[]) {
	RedBlack Example;
	Example.insert(5);
	Example.insert(3);
	Example.insert(6);
	Example.insert(1);
	Example.printTree(Example.root);
	return 0;
}

