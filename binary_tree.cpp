#include <iostream>

struct TNode{
	int m_x;
	TNode* m_nodes[2];
	TNode(int x){
		m_nodes[0] = m_nodes[1] = 0;
		m_x = x;
	}
};

class BTree{
public:
	TNode* m_root;
	BTree();
	bool find(int x, TNode**& p);
	bool insert(int x);
	bool remove(int x);
	void inorder(TNode* p);
	TNode** Rep(TNode** p);
};

BTree::BTree(){
	this->m_root = 0;
}

bool BTree::find(int x, TNode**& p){
	for(p = &m_root; *p && (*p)->m_x != x; p = &( (*p)->m_nodes[ (*p)->m_x < x ] ) );
	return !!*p;
}

bool BTree::insert(int x){
	TNode** p;
	if (find (x, p) ) return 0;
	*p = new TNode(x);
	return 1;
}

bool BTree::remove(int x){
	TNode** p;
	if (!find (x,p) ) return 0;
	if ((*p)->m_nodes[0] && (*p)->m_nodes[1]){
		TNode** q = Rep(p);
		(*p)->m_x = (*q)->m_x;
		p = q;
	}
	TNode* temp = *p;
	*p = (*p)->m_nodes[(*p)->m_nodes[1]!=0];
	delete temp;
	return 1;
}

TNode** BTree::Rep(TNode** p){
	for(p = &(p->m_nodes[0]); *p; p = &( (*p)->m_nodes[1]) );
	return p;
}

int main(int argc, char *argv[]) {
	BTree A;
	A.insert(5);
	A.insert(3);
	A.insert(8);
	return 0;
}

