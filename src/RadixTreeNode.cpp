// nickname.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "RadixTreeNode.h"
#include <algorithm>
#include <iostream>

void flaber::radix_tree_node::insert(std::string& str)
{
	auto it = std::find_if(childs.begin(), childs.end(), [&](const radix_tree_node& node) {
		return *str.begin() == *node.str.begin();
		});

	if (it != childs.end())
	{
		auto its = std::mismatch(it->str.begin(), it->str.end(), str.begin(), str.end());

		// new string included in current node, devide node
		if ((its.first - it->str.begin()) == str.size()) {
			if (its.first == it->str.end())
				it->isEnd = true;
			else 
				it->devide_node(its.first);
		}else
		// new string contains current node, go deeper
		if ((its.second - str.begin()) == it->str.size()) {
			std::string afterTmp(its.second, str.end());
			it->insert(afterTmp);
		}
		else // string intersect
		{
			it->devide_node(its.first);

			it->isEnd = false;
			std::string afterTmpNew(its.second, str.end());
			it->insert(afterTmpNew);
		}
	}
	else 
		childs.emplace_back(str, true);
}
void flaber::radix_tree_node::devide_node(std::string::iterator& iter)
{
	std::string beforeTmp(str.begin(), iter);
	std::string afterTmp(iter, str.end());

	radix_tree_node newNode(afterTmp, true);
	newNode.childs.insert(newNode.childs.begin(), childs.begin(), childs.end());
	childs.clear();
	childs.push_back(std::move(newNode));
	str = beforeTmp;
}
void flaber::radix_tree_node::print(std::ostream& os, const std::string& offset) const
{
	std::string newOffset = offset;

	if (str.size() > 0 || isEnd) {
		newOffset += "| ";
		os << offset << "+ " << str << (isEnd ? "$" : "") << std::endl;
	}
	for (auto ch : childs)
		ch.print(os, newOffset);
}
