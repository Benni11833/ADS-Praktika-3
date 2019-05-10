/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree {
private:
	TreeNode * anker;
	int NodeIDCounter;
	TreeNode* searchNode(int NodePosID);
	bool isLeaf(TreeNode*);
	bool isRoot(TreeNode*);
	bool has2Child(TreeNode*);
	bool has1Child(TreeNode*);
	TreeNode* Min(TreeNode*);
	void print_preorder(TreeNode*);
	TreeNode* getParent(TreeNode *);
	bool balanceTree(void);
	void printLevelOrder(void);
	bool rotateTreeRight(TreeNode*, TreeNode*);
	bool rotateTreeLeft(TreeNode*, TreeNode*);
public:
	Tree();
	void addNode(std::string Name, int Alter, double Einkommen, int PLZ);
	bool searchNode(std::string Name);
	// friend-Funktionen sind f�r die Tests erforderlich und m�ssen unangetastet bleiben! 
	friend TreeNode * get_anker(Tree& TN);
	void printAll() {
		print_preorder(anker);
	}
};
