#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>
#include <iostream>
#include <fstream>

using namespace std;

class RBtree {
	struct node_st { node_st *p1, *p2; int value; bool red; }; // struct of node
	node_st *tree_root;                 //!< root
	int nodes_count;                    //!< count of tree nodes
private:
	node_st *NewNode(int value);        //!< Selection of a new vertex
	void DelNode(node_st*);             //!< Vertex removal
	void Clear(node_st*);               //!< Tree demolition (recursive part)
	node_st *Rotate21(node_st*);        //!< Rotation left
	node_st *Rotate12(node_st*);        //!< Rotation right
	void BalanceInsert(node_st**);      //!< Insertion balancing
	bool BalanceRemove1(node_st**);     //!< Left balancing deletion
	bool BalanceRemove2(node_st**);     //!< Right balance balancing
	bool Insert(int, node_st**);         //!< Recursive part of an insert
	bool GetMin(node_st**, node_st**);   //!< Find and remove the maximum node of the subtree
	bool Remove(node_st**, int);         //!< Recursive delete part
public: // отладочная часть
	enum check_code { error_balance, error_struct, ok }; // error code
	void Show();                        //!< Tree output
	check_code Check();                 //!< Tree check
	bool TreeWalk(bool*, int);           //!< Tree traversal and comparison of values with an array
private: // отладочная часть
	void Show(node_st*, int, char);       //!< Tree output, recursive part
	check_code Check(node_st*, int, int&);//!< Tree check (recursive part)
	bool TreeWalk(node_st*, bool*, int);  //!< Traversing a tree and comparing values with an array (recursive part)
public:
	RBtree();
	~RBtree();
	void Clear();           //!< Tear down a tree              
	bool Find(int);         //!< Find the value
	void Insert(int);       //!< Insert value
	void Remove(int);       //!< Delete value
	int GetNodesCount();    //!< Find the number of nodes
	void ReadFromFile(string path); //!< Read from file
	int GetMin();
	int GetMax();
};

