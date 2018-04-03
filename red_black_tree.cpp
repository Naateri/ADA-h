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
public:
	RBNode* root;
	RedBlack();
	bool find(int x, RBNode**& p);
	bool insert(int x);
	bool remove(int x);
	void inorder(RBNode* p);
	RBNode** Rep(RBNode** p);
};

RedBlack::RedBlack(){
	this->root = 0;
}

bool RedBlack::find(int x, RBNode**& p){
	path.clear();
	for(p = &root; *p && (*p)->m_x != x; p = &( (*p)->m_nodes[ (*p)->m_x < x ] ) ){
		path.push_back(*p);
	}
	return ( (*p)->m_x == x );
}

bool RedBlack::insert(int x){
	RBNode** v;
	if (find (x, v) ) return 0;
	*v = new RBNode(x);
	//fix things if necessary -> recolor
}

void RedBlack::recolor(RBNode* v){
	RBNode* p, *g_parent, *uncle;
	node_list::iterator it = path.end();
	p = *(--it);
	path.pop_back();
	if (parent->colour) return;
	g_parent = *(--it);
	path.pop_back();
	uncle = g_parent->m_nodes[1];
	if (! uncle->colour){
		p->colour = 1;
		uncle->colour = 1;
		g_parent->colour = 0;
		recolor(g_parent);
	} else {
		p->colour = 1;
		g_parent->colour = 0;
		right_rotate(&g_parent);
	}
}

int main(int argc, char *argv[]) {
	
	return 0;
}

