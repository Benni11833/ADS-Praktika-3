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
#include <stack>

using namespace std;

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
	TreeNode* new_entry = new TreeNode{ NodePosID, NodeIDCounter++, Name, Alter, Einkommen, PLZ , 1};	//neuer Eintrag soll Rot sein
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
	bool flag{ false };
	if (anker) {
		std::queue<TreeNode*> q;
		TreeNode *k{ anker };
		q.push(anker);
		while (!q.empty()) {
			k = q.front();
			q.pop();
			if (k->getName() == Name) {
				flag = true;
				std::cout << "NodeID: " << k->getNodeID() << ", Name: " << k->getName()
					<< ", Alter: " << k->getAlter() << ", Einkommen: " << k->getEinkommen()
					<< ", PLZ: " << k->getPLZ() << ", PosID: " << k->getNodePosID()
					<< std::endl;
			}
			if (k->getRight())
				q.push(k->getRight());
			if (k->getLeft())
				q.push(k->getLeft());
		}
	}
	return flag;
}

bool Tree::balanceTree(void)	//durchlaeuft baum, prueft ob balanciert(rotiert) werden muss
{
	/*
	Kinder von roten Knoten sind schwarz
	Keine zwei aufeinanderfolgende rote Knoten
	--> Jeder Pfad von k zu einem Blatt enthaelt gleiche Anzahl an schwarzer Knoten
	*/
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