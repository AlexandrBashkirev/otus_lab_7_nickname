// nickname.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RadixTree.h"

int main()
{
	flaber::radix_tree tree;

	std::string line;
	while (std::getline(std::cin, line))
		tree.insert(line);

	for (auto it : tree)
		std::cout << it.first << " " << it.second << std::endl;

	std::cout << std::endl;

	std::cout << tree;
}
