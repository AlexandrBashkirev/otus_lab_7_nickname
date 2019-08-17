#pragma once
#include <string>
#include <stack>
#include "RadixTreeNode.h"

namespace flaber {

	class radix_tree_iterator
	{

	public:

		using node_type = radix_tree_node;
		using value_type = std::pair<std::string, std::string>;
		using value_ref = value_type &;
		using value_ptr = value_type *;

		auto operator->() const
		{
			return const_cast<const value_ptr>(&value);
		}

		auto operator*() const
		{
			return const_cast<const value_ref>(value);
		}

		radix_tree_iterator& operator++()
		{
			find_next(current);
			return *this;
		}

		bool operator!=(const radix_tree_iterator& right)
		{
			return current != right.current;
		}

		bool operator==(const radix_tree_iterator& right)
		{
			return current == right.current;
		}

		radix_tree_iterator(node_type* _current) : current(_current) { 
			find_next(current);
		}
		radix_tree_iterator(const radix_tree_iterator& node) = default;
		~radix_tree_iterator() = default;

	private:
		

		radix_tree_iterator() = delete;

		std::string current_prefix;
		node_type* current;
		value_type value;

		std::stack<std::pair<std::string, node_type*>> node_stack;

		void find_next(flaber::radix_tree_node* node)
		{
			if (node == nullptr)
				return;

			if (node->childs.size() > 0)
			{
				current_prefix += node->str;
				std::string local_current_prefix = current_prefix;

				bool nodeFinded = false;
				for (auto& child_node : node->childs)
				{
					if (!nodeFinded)
						nodeFinded = checkNode(&child_node.second);
					else
						node_stack.push(std::pair<std::string, node_type*>(local_current_prefix, &child_node.second));
				}
			}
			else if (node_stack.size() > 0)
			{
				auto& node = node_stack.top().second;
				current_prefix = node_stack.top().first;
				node_stack.pop();

				checkNode(node);
			}
			else
				current = nullptr;
		}
		bool checkNode(flaber::radix_tree_node* node)
		{
			if (node->isEnd)
			{
				value.first = current_prefix + node->str;
				value.second = (node->str.size() > 0 ? current_prefix + node->str[0] : "");
				current = node;
				return true;
			}
			else
			{
				find_next(node);
				return true;
			}
			return false;
		}
	};
	
}
