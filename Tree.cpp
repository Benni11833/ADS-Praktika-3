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
	if (p1 == anker)
		anker = p2;
	if (getParent(p1)) {
		if (getParent(p1)->getLeft() == p1)
			getParent(p1)->setLeft(p2);
		else
			getParent(p1)->setRight(p2);
	}
	p2->setRed(false);
	p1->setRed(true);

	p1->setRight(p2->getLeft());
	p2->setLeft(p1);

	return true;
}

bool Tree::rotateTreeRight(TreeNode *p1, TreeNode *p2)
{
	if (p1 == anker)
		anker = p2;
	if (getParent(p1)) {
		if (getParent(p1)->getLeft() == p1)
			getParent(p1)->setLeft(p2);
		else
			getParent(p1)->setRight(p2);
	}
	
	p2->setRed(false);
	p1->setRed(true);

	p1->setLeft(p2->getRight());
	p2->setRight(p1);

	return true;
}

bool Tree::rotateTreeRightLeft(TreeNode *p1, TreeNode *p2) {
	
	TreeNode *pp{ p2->getLeft() };
	if (p1 == anker)
		anker = pp;

		if (getParent(p1)) {
			if (getParent(p1)->getLeft() == p1)
				getParent(p1)->setLeft(pp);
			else
				getParent(p1)->setRight(pp);
		}
	
	p1->setRed(true);
	pp->setRed(false);

	p2->setLeft(pp->getRight());
	p1->setRight(pp->getLeft());
	pp->setLeft(p1);
	pp->setRight(p2);
	
	return true;
}

bool Tree::rotateTreeLeftRight(TreeNode *p1, TreeNode *p2) {

	TreeNode *pp{ p2->getRight() };
	if (p1 == anker)
		anker = pp;
	if (getParent(p1)) {
		if (getParent(p1)->getLeft() == p1)
			getParent(p1)->setLeft(pp);
		else
			getParent(p1)->setRight(pp);
	}

	pp->setRed(false);
	p1->setRed(true);

	p2->setRight(pp->getLeft());
	p1->setLeft(pp->getRight());
	pp->setRight(p1);
	pp->setLeft(p2);

	return true;
}

void Tree::addNode(std::string Name, int Alter, double Einkommen, int PLZ)
{
	int NodePosID = Alter + PLZ + Einkommen;
	TreeNode* new_entry = new TreeNode{ NodePosID, NodeIDCounter++, Name, Alter, Einkommen, PLZ , 1};	//neuer Eintrag soll Rot sein
		TreeNode* y{ nullptr }, *x{ anker };
		while (x) {
			y = x;
			if (!x->getRed() && x->getRight() && x->getRight()->getRed() 
				&& x->getLeft() && x->getLeft()->getRed()) {	//alle schwarzen knoten mit zwei nachfolgern umfaerben
				x->setRed(true);
				x->getLeft()->setRed(false);
				x->getRight()->setRed(false);
			}

			if (NodePosID < x->getNodePosID())
				x = x->getLeft();
			else
				x = x->getRight();
		}
		if (!y)	//anker == nullptr
			anker = new_entry;
		else
			if (NodePosID < y->getNodePosID())
				y->setLeft(new_entry);
			else
				y->setRight(new_entry);
		anker->setRed(false);	//anker immer schwarz
		
		while (balanceTree()) //balanciert baum - moegliche verletzungen beim umfaerben
			;
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
	//auf einanderfolgende rote knoten finden:
	TreeNode *k = anker, *node = nullptr;
		std::queue<TreeNode*> q;
		if (anker) {
			q.push(anker);
			while (!q.empty()) {
				TreeNode *node = q.front();
				q.pop();

				//Rotationen notewendig?
				if (node && !node->getRed() && node->getRight() && node->getRight()->getRed()
					&& node->getRight()->getRight() && node->getRight()->getRight()->getRed()) {
					rotateTreeLeft(node, node->getRight());
					//node->setRed(true);
					anker->setRed(false);	//anker immer schwarz
					std::cout << "rot 1\n";
					return true;
				}
				if(node && !node->getRed() && node->getLeft() && node->getLeft()->getRed()
					&& node->getLeft()->getLeft() && node->getLeft()->getLeft()->getRed()){
					rotateTreeRight(node, node->getLeft());
					//getParent(node)->setRed(false);
					//node->setRed(true);
					anker->setRed(false);	//anker immer schwarz
					std::cout << "rot 2\n";
					return true;
				}

				if (node && !node->getRed() && node->getRight() && node->getRight()->getRed()
					&& node->getRight()->getLeft() && node->getRight()->getLeft()->getRed()) {
					rotateTreeRightLeft(node, node->getRight());
					/*node->setRed(true);
					if (node->getRight())
						node->getRight()->getLeft()->setRed(false);*/
					anker->setRed(false);	//anker immer schwarz
					std::cout << "rot 3\n";
					return true;
				}

				if (node && !node->getRed() && node->getLeft() && node->getLeft()->getRed()
					&& node->getLeft()->getRight() && node->getLeft()->getRight()->getRed()) {
					rotateTreeLeftRight(node, node->getLeft());
					/*node->setRed(true);
					if (node->getLeft())
						node->getLeft()->getRight()->setRed(false);*/
					anker->setRed(false);	//anker immer schwarz
					std::cout << "rot 4\n";
					return true;
				}

				//enqueue left child
				if (node->getLeft())
					q.push(node->getLeft());

				//enqueue right child
				if (node->getRight())
					q.push(node->getRight());
			}
		}

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