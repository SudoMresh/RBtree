#include "stdafx.h"
#include "RBTree_BL.h"


RBtree::RBtree()
{
	tree_root = 0;
	nodes_count = 0;
}

RBtree::~RBtree()
{
	Clear(tree_root);
}

int RBtree::GetNodesCount()
{
	return nodes_count;
}

void RBtree::ReadFromFile(string path)
{
	ifstream reader(path);
	int val;

	if (!reader)
	{
		cout << "Error opening input file" << endl;
		system("pause");
		return;
	}

	for (int i = 0; !reader.eof(); i++)
	{
		reader >> val;
		Insert(val);
	}

	reader.close();
}

int RBtree::GetMin()
{
	int min;

	node_st *node = tree_root;
	node_st *secNode = node->p2;


	min = node->value;
	while (node->p1 != NULL)
	{
		if (min > node->p1->value)
			min = node->p1->value;

		node = node->p1;
	}

	
	while (secNode->p2 != NULL)
	{
		if (min > secNode->p2->value)
			min = secNode->p2->value;

		secNode = secNode->p2;
	}

	return min;

}

int RBtree::GetMax()
{
	int max;

	node_st *node = tree_root;
	node_st *secNode = node->p2;


	max = node->value;
	while (node->p1 != NULL)
	{
		if (max < node->p1->value)
			max = node->p1->value;

		node = node->p1;
	}


	while (secNode->p2 != NULL)
	{
		if (max < secNode->p2->value)
			max = secNode->p2->value;

		secNode = secNode->p2;
	}

	return max;
}

// find and remove the maximum node of the subtree
//! \ Param root of the tree in which you want to find the element
//! \ Retval res element that was deleted
//! \ Result true if you need a balance
bool RBtree::GetMin(node_st **root, node_st **res)
{
	node_st *node = *root;
	if (node->p1) {
		if (GetMin(&node->p1, res)) return BalanceRemove1(root);
	}
	else {
		*root = node->p2;
		*res = node;
		return !node->red;
	}
	return false;
}

// select a new vertexы
RBtree::node_st *RBtree::NewNode(int value)
{
	nodes_count++;
	node_st *node = new node_st;
	node->value = value;
	node->p1 = node->p2 = 0;
	node->red = true;
	return node;
}

// Vertex removal
void RBtree::DelNode(node_st *node)
{
	nodes_count--;
	delete node;
}

// Tree demolition (recursive part)
void RBtree::Clear(node_st *node)
{
	if (!node) return;
	Clear(node->p1);
	Clear(node->p2);
	DelNode(node);
}

// the output of the tree, the recursive part
//! \ Param node node
//! \ Param depth
//! \ Param dir icons
//! \ Code Show (root, 0, '*'); \ Endcode
void RBtree::Show(node_st *node, int depth, char dir)
{
	int n;
	if (!node) return;
	for (n = 0; n<depth; n++) putchar(' ');
	printf("%c[%d] (%s)\n", dir, node->value, node->red ? "red" : "black");
	Show(node->p1, depth + 2, '-');
	Show(node->p2, depth + 2, '+');
}


// Rotate left
//! \ Param index vertex indesk
//! \ Result a new vertex of the tree
RBtree::node_st *RBtree::Rotate21(node_st *node)
{
	node_st *p2 = node->p2;
	node_st *p21 = p2->p1;
	p2->p1 = node;
	node->p2 = p21;
	return p2;
}

// Rotate Right
//! \ Param index vertex indesk
//! \ Result a new vertex of the tree
RBtree::node_st *RBtree::Rotate12(node_st *node)
{
	node_st *p1 = node->p1;
	node_st *p12 = p1->p2;
	p1->p2 = node;
	node->p1 = p12;
	return p1;
}


// Vertex balancing
void RBtree::BalanceInsert(node_st **root)
{
	node_st *p1, *p2, *px1, *px2;
	node_st *node = *root;
	if (node->red) return;
	p1 = node->p1;
	p2 = node->p2;
	if (p1 && p1->red) {
		px2 = p1->p2;             // The task of finding two nearby red vertices
		if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
		px1 = p1->p1;
		if (px1 && px1->red) {
			node->red = true;
			p1->red = false;
			if (p2 && p2->red) { // Get rid of repainting vertices
				px1->red = true;
				p2->red = false;
				return;
			}
			*root = Rotate12(node);
			return;
		}
	}
	// The same in the other direction
	if (p2 && p2->red) {
		px1 = p2->p1;             // The task of finding two nearby red vertices
		if (px1 && px1->red) p2 = node->p2 = Rotate12(p2);
		px2 = p2->p2;
		if (px2 && px2->red) {
			node->red = true;
			p2->red = false;
			if (p1 && p1->red) { // Get rid of repainting vertices
				px2->red = true;
				p1->red = false;
				return;
			}
			*root = Rotate21(node);
			return;
		}
	}
}


bool RBtree::BalanceRemove1(node_st **root)
{
	node_st *node = *root;
	node_st *p1 = node->p1;
	node_st *p2 = node->p2;
	if (p1 && p1->red) {
		p1->red = false; return false;
	}
	if (p2 && p2->red) { // Case 1
		node->red = true;
		p2->red = false;
		node = *root = Rotate21(node);
		if (BalanceRemove1(&node->p1)) node->p1->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st *p21 = p2->p1;
	node_st *p22 = p2->p2;
	if (p21 && p21->red) mask |= 1;
	if (p22 && p22->red) mask |= 2;
	switch (mask)
	{
	case 0:     // Case 2 - if((!p21 || !p21->red) && (!p22 || !p22->red))
		p2->red = true;
		return true;
	case 1:
	case 3:     // Case 3 - if(p21 && p21->red)
		p2->red = true;
		p21->red = false;
		p2 = node->p2 = Rotate12(p2);
		p22 = p2->p2;
	case 2:     // Case 4 - if(p22 && p22->red)
		p2->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);
	}
	return false;
}

bool RBtree::BalanceRemove2(node_st **root)
{
	node_st *node = *root;
	node_st *p1 = node->p1;
	node_st *p2 = node->p2;
	if (p2 && p2->red) { p2->red = false; return false; }
	if (p1 && p1->red) { // Case 1
		node->red = true;
		p1->red = false;
		node = *root = Rotate12(node);
		if (BalanceRemove2(&node->p2)) node->p2->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st *p11 = p1->p1;
	node_st *p12 = p1->p2;
	if (p11 && p11->red) mask |= 1;
	if (p12 && p12->red) mask |= 2;
	switch (mask) {
	case 0:     // Case 2 - if((!p12 || !p12->red) && (!p11 || !p11->red))
		p1->red = true;
		return true;
	case 2:
	case 3:     // Case 3 - if(p12 && p12->red)
		p1->red = true;
		p12->red = false;
		p1 = node->p1 = Rotate21(p1);
		p11 = p1->p1;
	case 1:     // Case 4 - if(p11 && p11->red)
		p1->red = node->red;
		p11->red = node->red = false;
		*root = Rotate12(node);
	}
	return false;
}


bool RBtree::Find(int value)
{
	node_st *node = tree_root;
	while (node) {
		if (node->value == value) return true;
		node = node->value>value ? node->p1 : node->p2;
	}
	return false;
}


// recursive part of the insert
//! \ Result true if there are no changes or balancing is not needed at this vertex
bool RBtree::Insert(int value, node_st **root)
{
	node_st *node = *root;
	if (!node) *root = NewNode(value);
	else {
		if (value == node->value) return true;
		if (Insert(value, value<node->value ? &node->p1 : &node->p2)) return true;
		BalanceInsert(root);
	}
	return false;
}





// recursive delete part
//! \ Result true if you need a balance
bool RBtree::Remove(node_st **root, int value)
{
	node_st *t, *node = *root;
	if (!node) return false;
	if (node->value<value) {
		if (Remove(&node->p2, value)) return BalanceRemove2(root);
	}
	else if (node->value>value) {
		if (Remove(&node->p1, value)) return BalanceRemove1(root);
	}
	else {
		bool res;
		if (!node->p2) {
			*root = node->p1;
			res = !node->red;
		}
		else {
			res = GetMin(&node->p2, root);
			t = *root;
			t->red = node->red;
			t->p1 = node->p1;
			t->p2 = node->p2;
			if (res) res = BalanceRemove2(root);
		}
		DelNode(node);
		return res;
	}
	return 0;
}


// Tree output
void RBtree::Show()
{
	printf("[tree]\n");
	Show(tree_root, 0, '*');
}

// Insert function
void RBtree::Insert(int value)
{
	Insert(value, &tree_root);
	if (tree_root) tree_root->red = false;
}

// Node removal
void RBtree::Remove(int value)
{
	Remove(&tree_root, value);
}

// Demolition of a tree
void RBtree::Clear()
{
	Clear(tree_root);
	tree_root = 0;
}


// check the tree (recursive part)
//! \ Param tree tree
//! \ Param d current black depth
//! \ Param h reference black depth
//! \ Result 0 or error code
RBtree::check_code RBtree::Check(node_st *tree, int d, int &h)
{
	if (!tree) {
		// The number of black vertices on any path is the same
		if (h<0) h = d;
		return h == d ? ok : error_balance;
	}
	node_st *p1 = tree->p1;
	node_st *p2 = tree->p2;
	// The red vertex must have black descendants
	if (tree->red && (p1 && p1->red || p2 && p2->red)) return error_struct;
	if (p1 && tree->value<p1->value || p2 && tree->value>p2->value) return error_struct;
	if (!tree->red) d++;
	check_code n = Check(p1, d, h); if (n) return n;
	return Check(p2, d, h);
}


// Tree check
RBtree::check_code RBtree::Check()
{
	int d = 0;
	int h = -1;
	if (!tree_root) return ok;
	if (tree_root->red) return error_struct;
	return Check(tree_root, d, h);
}

// traverse the tree and compare values with an array (recursive part)
//! \ Param node tree root
//! \ Param array for verification
//! \ Param size array size
bool RBtree::TreeWalk(node_st *node, bool *array, int size)
{
	if (!node) return false;
	int value = node->value;
	if (value<0 || value >= size || !array[value]) return true;
	array[value] = false;
	return TreeWalk(node->p1, array, size) || TreeWalk(node->p2, array, size);
}

// traverse the tree and compare values with an array
//! \ Param array for verification
//! \ Param size array size
bool RBtree::TreeWalk(bool *array, int size)
{
	if (TreeWalk(tree_root, array, size)) return true;
	for (int n = 0; n<size; n++) if (array[n]) return true;
	return false;
}

