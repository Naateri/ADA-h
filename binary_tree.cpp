#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

typedef std::vector<int> int_vec;

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

void BTree::inorder(TNode* p){
	if (!p) return;
	inorder(p->m_nodes[0]);
	std::cout << p->m_x << ' ';
	inorder(p->m_nodes[1]);
}

TNode** BTree::Rep(TNode** p){
	for(p = &((*p)->m_nodes[0]); *p; p = &( (*p)->m_nodes[1]) );
	return p;
}

int rdtsc(){
	__asm__ __volatile__("rdtsc");
}

void partition(int_vec A, BTree& res){
	int_vec L, R;
	srand( rdtsc() );
	if (A.size() == 0)
		return;
	int p = rand() % int(A.size());
	for (int i= 0; i < A.size(); i++){
		if (i == p) continue;
		else if (A.at(i) <= A.at(p) ) L.push_back(A.at(i));
		else R.push_back(A.at(i));
	}
	res.insert(A.at(p));
	partition(L, res);
	partition(R, res);
}

BTree createTree(int_vec A){
	BTree res;
	partition(A, res);
	return res;
}

int main(int argc, char *argv[]) {
	BTree A, B;
	A.insert(5);
	A.insert(3);
	A.insert(8);
	A.inorder(A.m_root);
	int_vec test (12);
	test = {4,8,9,2,10,15,1,18,12,3,15,-1};
	B = createTree(test);
	B.inorder(B.m_root);
	return 0;
}

