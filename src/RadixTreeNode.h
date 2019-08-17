#pragma once
#include <string>
//#include <unordered_map>
#include <map>

namespace flaber {

	class radix_tree_node {
	public:
		template<typename S>
		radix_tree_node(S&& _str, bool _isEnd) : str(std::forward<S>(_str)), isEnd(_isEnd) {}

		radix_tree_node()  : str(""), isEnd(false) {};

		void insert(std::string&);
		void print(std::ostream&) const;

	private:

		void print(std::ostream&, const std::string& offset, bool draw_linw) const;
		void devide_node(std::string::iterator&);

		std::string str;
		bool isEnd;
		std::map<char, radix_tree_node> childs;

		friend class radix_tree_iterator;
	};
}
