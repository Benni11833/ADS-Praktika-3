/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;


bool Tree::rec_searchNode(TreeNode* tmp, std::string Name)
{
	static bool flag{ false };
	if (tmp == anker)	//wenn flag auf true steht von vorherigen aufrufen
		flag = false;
	if (tmp) {
		if (tmp->getName() == Name) {
			flag = true;
			std::cout << "NodeID: " << tmp->getNodeID() << ", Name: " << tmp->getName()
				<< ", Alter: " << tmp->getAlter() << ", Einkommen: " << tmp->getEinkommen()
				<< ", PLZ: " << tmp->getPLZ() << ", PosID: " << tmp->getNodePosID()
				<< std::endl;
		}
			//Teilbaum weiter durchlaufen - links,rechts
			rec_searchNode(tmp->getLeft(), Name);
			rec_searchNode(tmp->getRight(), Name);
		
		if (tmp == anker)
			return flag;	//baum wurde durchlaufen
	}
}

bool Tree::isLeaf(TreeNode* tmp) {
	return (!tmp->getRight() && !tmp->getLeft());
}

bool Tree::isRoot(TreeNode* tmp) {
	return (anker == tmp);
}

bool Tree::has2Child(TreeNode* tmp) {
	return (tmp->getRight() && tmp->getLeft());
}

bool Tree::has1Child(TreeNode* tmp) {
	return (!has2Child(tmp) && !isLeaf(tmp));
}

void Tree::print_preorder(TreeNode *tmp) {
	if (tmp) {
		tmp->print();
		print_preorder(tmp->getLeft());
		print_preorder(tmp->getRight());
	}
}

TreeNode* Tree::Min(TreeNode* tmp) {	//findet Min vom rechten Teilbaum
	while (tmp->getLeft())
		tmp = tmp->getLeft();
	return tmp;
}

TreeNode* Tree::searchNode(int NodePosID) {	//iterativ - nullptr wenn nicht vorhanden
	TreeNode *x{ anker };
	while (x && NodePosID != x->getNodePosID()) {
		if (NodePosID < x->getNodePosID())
			x = x->getLeft();
		else
			x = x->getRight();
	}
	return x;
}

TreeNode* Tree::getParent(TreeNode *tmp) {
	TreeNode *run{ anker };
	if (isRoot(tmp))
		return nullptr;
	while (run && run->getRight() != tmp && run->getLeft() != tmp) {
		if (tmp->getNodePosID() < run->getNodePosID())
			run = run->getLeft();
		else
			run = run->getRight();
	}
	return run;
}



Tree::Tree()
	:anker{ nullptr }, NodeIDCounter{ 0 }
{}

bool Tree::rotateTreeLeft(TreeNode *p1, TreeNode *p2)
{
	TreeNode *pp = getParent(p1);
	p1->setRight(p2->getLeft());
	p2->setLeft(p1);

	if (pp && p2->getNodePosID() < pp->getNodePosID())
		pp->setLeft(p2);
	else if(pp)
		pp->setRight(p2);

	return true;
}

bool Tree::rotateTreeRight(TreeNode *p1, TreeNode *p2)
{
	TreeNode *pp = getParent(p1);
	p1->setLeft(p2->getRight());
	p2->setRight(p1);

	if (pp && p2->getNodePosID() < pp->getNodePosID())
		pp->setLeft(p2);
	else if (pp)
		pp->setRight(p2);

	p2->setRed(false);
	p1->setRed(true);

	return true;
}

void Tree::addNode(std::string Name, int Alter, double Einkommen, int PLZ)
{
	int NodePosID = Alter + PLZ + Einkommen;
	TreeNode* new_entry = new TreeNode{ NodePosID, NodeIDCounter++, Name, Alter, Einkommen, PLZ , 1};
		TreeNode* y{ nullptr }, *x{ anker };
		while (x) {
			y = x;
			if (NodePosID < x->getNodePosID())
				x = x->getLeft();
			else
				x = x->getRight();
		}
		if (!y) {	//anker == nullptr
			new_entry->setRed(false);	//anker muss schwarz sein
			anker = new_entry;
		}
		else
			if (NodePosID < y->getNodePosID())
				y->setLeft(new_entry);
			else
				y->setRight(new_entry);
}

bool Tree::searchNode(std::string Name)
{
	if (anker)
		return rec_searchNode(anker, Name);
	else
		return false;
}

bool Tree::balanceTree(void)	//false wenn nicht ausbalanciert wurde, true wenn doch
{
	return false;
}

void Tree::printLevelOrder(void)
{
	TreeNode *k = anker, *node = nullptr;
	std::queue<TreeNode*> q;
	if (anker) {
		q.push(anker);
		while (!q.empty()) {
			TreeNode *node = q.front();
			node->print();
			q.pop();

			//enqueue left child
			if (node->getLeft())
				q.push(node->getLeft());

			//enqueue right child
			if (node->getRight())
				q.push(node->getRight());
		}
	}
}