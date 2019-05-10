/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <fstream>
#include "Tree.h"
#include "catch.h"

using namespace std;

void printmenu() {
	std::cout << "1) Datensatz einfuegen, manuell" << std::endl
		<< "2) Datensatz einfuegen, CSV Datei" << std::endl
		<< "3) Datensatz loschen" << std::endl
		<< "4) Suchen" << std::endl
		<< "5) Datenstruktur anzeigen" << std::endl;
}

void readData(std::string& name, int& alter, double& einkommen, int& plz) {
	std::cout << "+ Bitte geben Sie die den Datensatz ein" << std::endl
		<< "Name ?> ";	std::getline(std::cin, name);
	std::cout << "Alter ?>";	std::cin >> alter;			std::cout << std::endl;
	std::cout << "Einkommen ?>";	std::cin >> einkommen;	std::cout << std::endl;
	std::cout << "PLZ ?>";	std::cin >> plz;				std::cout << std::endl;
}

int main() {

	//int result = Catch::Session().run();

	Tree nTree;
	nTree.addNode("Mayer", 20, 0, 0);
	nTree.addNode("Mayer2", 10, 0, 0);
	nTree.addNode("Mayer3", 35, 0, 0);
	nTree.addNode("Mayer4", 26, 0, 0);
	nTree.addNode("Mayer5", 40, 0, 0);
	nTree.addNode("Mayer6", 25, 0, 0);
	nTree.addNode("Mayer7", 30, 0, 0);
	nTree.printAll();
	/*
	char choice{ -1 };
	printmenu();
	std::string name{ "" };
	int alter{ 0 }, plz{ 0 };	double einkommen{ 0.00 };

	while (true) {
		std::cout << "?>";
		std::cin >> choice;
		if (choice-'0' < 1 || choice-'0' > 5)
			break;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (choice-'0') {
		case 1:
			readData(name, alter, einkommen, plz);
			t1.addNode(name, alter, einkommen, plz);
			std::cout << "+ Ihr Datensatz wurde eingefuegt" << std::endl;
			break;
		case 3:
			std::cout << "+ Bitte geben Sie den zu suchenden Datensatz an"
				<< std::endl << "Name ?>";	std::getline(std::cin, name);
			std::cout << "+ Fundstellen:" << std::endl;
			if (!t1.searchNode(name))
				std::cout << "Keine Treffer" << std::endl;
			break;
		case 4:
			std::cout << "klsjadiljnsdfo\n";
			break;
		default:
			std::cout << "?> ";
			break;
		}
	}
	*/
	system("PAUSE");

	return 0;
}
