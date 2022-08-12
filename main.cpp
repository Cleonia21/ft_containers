#include "vector.hpp"
#include "reverse_iterator.hpp"
#include <vector>
#include "map.hpp"
#include <map>
#include "RB_tree.hpp"
#include "stack.hpp"

int main()
{
	ft::stack<int, ft::vector<int> > stk;

	std::cout << stk.size() << std::endl;
	std::cout << stk.empty() << std::endl;
//	std::cout << stk.top() << std::endl;
	stk.push(1);
	stk.push(2);
	stk.push(3);
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;

}