
#include "RadixTreeNode.h"
#include <algorithm>
#include <iostream>

void flaber::radix_tree_node::insert(std::string& str)
{
	auto it = childs.find(str[0]);

	if (it != childs.end())
	{
		auto its = std::mismatch(it->second.str.begin(), it->second.str.end(), str.begin(), str.end());

		// new string included in current node, devide node
		if (its.second == str.end()) {
			if (its.first == it->second.str.end())
				it->second.isEnd = true;
			else 
				it->second.devide_node(its.first);
		}else
		// new string contains current node, go deeper
		if (its.first == it->second.str.end()) {
			std::string afterTmp(its.second, str.end());
			it->second.insert(afterTmp);
		}
		else // string intersect
		{
			it->second.devide_node(its.first);

			it->second.isEnd = false;
			std::string afterTmpNew(its.second, str.end());
			it->second.insert(afterTmpNew);
		}
	}
	else 
		childs.insert(std::pair<char, radix_tree_node>(str[0], radix_tree_node(str, true)));
}
void flaber::radix_tree_node::devide_node(std::string::iterator& iter)
{
	std::string beforeTmp(str.begin(), iter);
	std::string afterTmp(iter, str.end());

	radix_tree_node newNode(afterTmp, true);
	newNode.childs.swap(childs);
	childs.insert(std::pair<char, radix_tree_node>(afterTmp[0], newNode));
	str = beforeTmp;
}
void flaber::radix_tree_node::print(std::ostream& os) const
{
	print(os, "", false);
}
void flaber::radix_tree_node::print(std::ostream& os, const std::string& offset, bool draw_line) const
{
	if (str.size() > 0 || isEnd)
		os << offset << "+ " << str << (isEnd ? "$" : "") << std::endl;

	int i = 0;
	for (const auto& ch : childs) {
		std::string newOffset = offset;
		if (str.size() > 0 || isEnd)
			newOffset = draw_line ? offset + "| " : offset + "  ";

		ch.second.print(os, newOffset, childs.size() > 1u && i < childs.size() -1);
		++i;
	}
}
