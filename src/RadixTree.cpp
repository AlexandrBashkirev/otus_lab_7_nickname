// nickname.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "RadixTree.h"
#include <algorithm>
#include <iostream>

void flaber::radix_tree::insert(std::string str)
{
	if(str.size() > 0)
		rootNode.insert(str);
}

flaber::radix_tree_iterator flaber::radix_tree::begin()
{
	return flaber::radix_tree_iterator(&rootNode);
}
flaber::radix_tree_iterator flaber::radix_tree::end()
{
	return flaber::radix_tree_iterator(nullptr);
}
