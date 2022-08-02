#include <iostream>
#include "vector.hpp"
#include "reverse_iterator.hpp"
#include <vector>
#include "map.hpp"
#include <map>
#include "rbt_iterator.hpp"



int		main()
{
	ft::RB_tree<int> tree;
	ft::RB_node<int> *end;

	ft::RB_node<int> *begin = tree.insert(0);

	for (int i = 1; i < 10; i++) // 0-9
		tree.insert(i);
	for (int i = 30; i > 20; i--) // 30-21
		tree.insert(i);
	for (int i = 10; i < 20; i++) // 10-19
		tree.insert(i);

	end = tree.end();

	ft::rbt_iterator<ft::RB_node<int> > itr(begin, end);
	ft::rbt_iterator<ft::RB_node<int> > itr2(end, end);

	while (--itr2 != itr)
	{
		std::cout << *itr2 << std::endl;
	}


	return (0);
}
