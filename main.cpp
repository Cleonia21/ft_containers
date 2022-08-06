#include "vector.hpp"
#include "reverse_iterator.hpp"
#include <vector>
#include "map.hpp"
#include <map>
#include "rbt_iterator.hpp"
#include "RB_tree.hpp"

#include <list>

#define TESTED_NAMESPACE ft

#define _pair TESTED_NAMESPACE::pair
//#define T1 char
//#define T2 int
//typedef _pair<const T1, T2> T3;

#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

template <class T>
void	is_empty(T const &mp)
{
	std::cout << "is_empty: " << mp.empty() << std::endl;
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int		main(void)
{
	std::map<int, int> mp1;
	std::map<int, int> mp2;

	if (mp1 > mp1)
		std::cout << "Yes" << std::endl;

	return (0);
}