#pragma once
#include <string>
#include <list>
#include "RadixTreeNode.h"
#include "RadixTreeIterator.h"

namespace flaber {

	class radix_tree
	{
	public:
		void insert(std::string& str);

		radix_tree_iterator begin();
		radix_tree_iterator end();

	private:

		radix_tree_node rootNode;

		friend std::ostream& operator<< (std::ostream& os, const radix_tree& rtree) {
			rtree.rootNode.print(os);
			return os;
		}
		
	};
}
