#include <iostream>
#include "vector.hpp"
#include "reverse_iterator.hpp"
#include <vector>
#include "map.hpp"
#include <map>
#include "rbt_iterator.hpp"
#include "RB_tree.hpp"

void print(ft::map<int, int>::iterator begin, ft::map<int, int>::iterator end)
{
    while (begin != end)
    {
        std::cout << "{" << begin->first << "," << begin->second << "} ";
        begin++;
    }
    std::cout << std::endl;
}

int		main()
{
    /*
    std::map<int, char> mp;

    mp.insert({1, 'a'});
    mp.insert({2, 'b'});
    mp.insert({3, 'c'});
    mp.insert({4, 'd'});
    std::pair<std::map<int, char>::iterator , bool> p = mp.insert({5, 'e'});

    p.first++;
    if (p.first == mp.end())
        std::cout << "je" << std::endl;
//    p.first++;
    mp.insert(p.first, {0, '-'});

    std::map<int, char>::iterator it = mp.find(0);

    if (it != mp.end())
        std::cout << (*it).second << std::endl;
*/

    ft::map<int, int> m1;
    ft::map<int, int> m2;

    for (int i = 0; i < 10; i++)
    {
        m1.insert(ft::make_pair(i, i * i));
        m2.insert(ft::make_pair(i * i, i));
    }
//
//    print(m1.begin(), m1.end());
//    print(m2.begin(), m2.end());
//
//    m1.swap(m2);
//
//    print(m1.begin(), m1.end());
//    print(m2.begin(), m2.end());

//    m1.clear();
//    if (!(m1.begin() != m1.end()))
//        std::cout << "Yes, baby!" << std::endl;

    /*
    std::vector<ft::pair<int, int>> vct;

    for (int i = 0; i < 10; i++)
        vct.push_back(ft::make_pair(i, i * i));

    mp.insert(vct.begin(), vct.end());
     */


//	ft::RB_tree<int> tree;
//	ft::RB_node<int> *end;
//
//	ft::RB_node<int> *begin = tree.insert(0);
//
//	for (int i = 1; i < 10; i++) // 0-9
//		tree.insert(i);
//	for (int i = 30; i > 20; i--) // 30-21
//		tree.insert(i);
//	for (int i = 10; i < 20; i++) // 10-19
//		tree.insert(i);
//
//	end = tree.end();
//
//	ft::rbt_iterator<ft::RB_node<int> > itr(begin, end);
//	ft::rbt_iterator<ft::RB_node<int> > itr2(end, end);
//
//	while (--itr2 != itr)
//	{
//		std::cout << *itr2 << std::endl;
//	}


}
