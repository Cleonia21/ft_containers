//
// Created by Cleonia on 11.08.2022.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include <iostream>
#include <unistd.h>
#include <memory>
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "vector.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class stack {

	public:

		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack(const container_type &ctnr = container_type()) {
			_cntr = ctnr;
		}

		bool empty() const { return _cntr.empty(); }

		size_type size() const { return _cntr.size(); }

		value_type &top() { return _cntr.back(); }

		const value_type &top() const { return _cntr.back(); }

		void push(const value_type &val) { _cntr.push_back(val); }

		void pop() { _cntr.pop_back(); }

		template <class Tn, class ContainerN>
		friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		template <class Tn, class ContainerN>
		friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		template <class Tn, class ContainerN>
		friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		template <class Tn, class ContainerN>
		friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		template <class Tn, class ContainerN>
		friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		template <class Tn, class ContainerN>
		friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

	private:
		container_type _cntr;
	};


	template<class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._cntr == rhs._cntr;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._cntr != rhs._cntr;
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._cntr < rhs._cntr;
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._cntr <= rhs._cntr;
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._cntr > rhs._cntr;
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._cntr >= rhs._cntr;
	}

}

#endif //FT_CONTAINERS_STACK_HPP
