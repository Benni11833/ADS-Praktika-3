/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>

TreeNode::TreeNode(int NodePosID, int NodeID, std::string Name, int Alter, double Einkommen, int PLZ, bool red)
	:NodePosID{ NodePosID }, NodeID{ NodeID }, Name{ Name }, Alter{ Alter }, Einkommen{ Einkommen }, PLZ{ PLZ },
	left{ nullptr }, right{ nullptr }, red{ red }
{}

void TreeNode::setRed(bool flag){
	red = flag;
}

bool TreeNode::getRed()const{
	return red;
}

int TreeNode::getNodePosID()
{
	return NodePosID;
}

int TreeNode::getNodeID()
{
	return NodeID;
}

std::string TreeNode::getName()
{
	return Name;
}

void TreeNode::setName(std::string new_name)
{
	Name = new_name;
}

int TreeNode::getAlter()
{
	return Alter;
}

void TreeNode::setAlter(int new_alter)
{
	Alter = new_alter;
}

double TreeNode::getEinkommen()
{
	return Einkommen;
}

void TreeNode::setEinkommen(double new_einkommen)
{
	Einkommen = new_einkommen;
}

int TreeNode::getPLZ()
{
	return PLZ;
}

void TreeNode::setPLZ(int new_plz)
{
	PLZ = new_plz;
}

TreeNode * TreeNode::getLeft()
{
	return left;
}

TreeNode * TreeNode::getRight()
{
	return right;
}

void TreeNode::setLeft(TreeNode * new_left)
{
	left = new_left;
}

void TreeNode::setRight(TreeNode *new_right)
{
	right = new_right;
}

void TreeNode::print()
{
	std::cout << NodeID << std::right << std::setw(setw_width) << '|' << Name << std::right << std::setw(setw_width) << '|' << Alter << std::right << std::setw(setw_width) << '|' << Einkommen << std::right << std::setw(setw_width) << '|' << PLZ << std::right << std::setw(setw_width) << '|' << NodePosID << std::endl;
}
