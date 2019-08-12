#pragma once
#include <string>
#include <list>

namespace flaber {

	class radix_tree_node {
	public:
		template<typename S>
		radix_tree_node(S&& _str, bool _isEnd) : str(std::forward<S>(_str)), isEnd(_isEnd) {}

		radix_tree_node() {};

		void insert(std::string&);
		void print(std::ostream&, const std::string& offset = "") const;
	private:

		void devide_node(std::string::iterator&);

		std::string str;
		bool isEnd;
		std::list<radix_tree_node> childs;

		friend class radix_tree_iterator;
	};
}
