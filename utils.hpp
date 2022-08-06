//
// Created by Cleonia on 23.06.2022.
//

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

#include <iostream>
#include <unistd.h>
#include <cstddef>

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	class iterator
	{
	public:
		typedef T           value_type;
		typedef Distance    difference_type;
		typedef Pointer     pointer;
		typedef Reference   reference;
		typedef Category    iterator_category;
	};

	class random_access_iterator_tag { };
	struct bidirectional_iterator_tag { };

	template <class Iterator> struct iterator_traits
	{
		typedef typename Iterator::difference_type       difference_type;
		typedef typename Iterator::value_type            value_type;
		typedef typename Iterator::pointer               pointer;
		typedef typename Iterator::reference             reference;
		typedef typename Iterator::iterator_category     iterator_category;
	};

	template <class T> struct iterator_traits<T*>
	{
		typedef ptrdiff_t                       difference_type;
		typedef T                               value_type;
		typedef T*                              pointer;
		typedef T&                              reference;
		typedef ft::random_access_iterator_tag  iterator_category;
	};

	template <class T> struct iterator_traits<const T*>
	{
		typedef ptrdiff_t                       difference_type;
		typedef T                               value_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;
		typedef ft::random_access_iterator_tag  iterator_category;
	};

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type num = 0;
		while(first != last)
		{
			first++;
			num++;
		}
		return (num);
	}

	template<bool is_integral, typename T>
	struct is_integral_res {
		typedef T type;
		static const bool value = is_integral;
	};

	template<typename>
	struct is_integral_type : public is_integral_res<false, bool> {};

	template<>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template<>
	struct is_integral_type<char> : public is_integral_res<true, char> {};

	template<>
	struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};

	template<>
	struct is_integral_type<char32_t> : public is_integral_res<true, char32_t> {};

	template<>
	struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};

	template<>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template<>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};

	template<>
	struct is_integral_type<int> : public is_integral_res<true, int> {};

	template<>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template<>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template<>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	template<>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	template<>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	template<>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

	template<>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template <typename T>
	struct is_integral : public is_integral_type<T> { };

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	template<class T1, class T2>
	struct pair {

	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair()
				:
				first(),
				second() {}

		template<class U, class V>
		pair(const pair<U, V> &pr)
				:
				first(pr.first),
				second(pr.second) {}

		pair(const first_type &a, const second_type &b)
				:
				first(a),
				second(b) {}

		pair& operator=(const pair& pr)
		{
			if (this == &pr)
				return (*this);
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}

	};

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs == rhs); }

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(rhs < lhs); }

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; }

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); }

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	}

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				BinaryPredicate pred)
	{
		while (first1!=last1) {
			if (!pred(*first1,*first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) return false;
			else if (*first1 < *first2) return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2,
								  Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) return false;
			else if (comp(*first1, *first2)) return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

}


#endif //FT_CONTAINERS_UTILS_HPP
