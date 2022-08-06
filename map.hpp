//
// Created by Cleonia on 06.06.2022.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <iostream>
#include <unistd.h>
#include <memory>
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "rbt_iterator.hpp"
#include "RB_tree.hpp"


namespace ft {

	template<class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;

		class value_compare : std::binary_function<value_type, value_type, bool> {
			friend class map<key_type, mapped_type, key_compare, Alloc>;

		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const {
				return comp(x.first, y.first);
			}
		};

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::RB_tree<value_type, value_compare>::iterator iterator;
		typedef typename ft::RB_tree<value_type, value_compare>::const_iterator const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
				:
				_comp(comp),
				_alloc(alloc),
				_rbt() {}

		template<class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
				:
				_comp(comp),
				_alloc(alloc),
				_rbt() { insert(first, last); }

		map(const map &x)
				:
				_comp(x._comp),
				_alloc(x._alloc),
				_rbt() { insert(x.begin(), x.end()); }

		map &operator=(const map &x) {
			if (this != &x) {
				clear();
				insert(x.begin(), x.end());
			}
			return (*this);
		}

		virtual ~map() { clear(); }

		iterator				begin() { return iterator(_rbt.begin(), _rbt.end()); }

		const_iterator 			begin() const { return const_iterator(_rbt.begin(), _rbt.end()); }

		iterator 				end() { return iterator(_rbt.end(), _rbt.end()); }

		const_iterator 			end() const { return const_iterator(_rbt.end(), _rbt.end()); }

		reverse_iterator 		rbegin() { return reverse_iterator(this->end()); }

		const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }

		reverse_iterator 		rend() { return reverse_iterator(this->begin()); }

		const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }

		bool					empty() const { return _rbt.begin() == _rbt.end(); }

		size_type				size() const { return _rbt.size(); }

		size_type				max_size() const { return _alloc.max_size(); }

		mapped_type &operator[](const key_type &k) {
			value_type pair(k, mapped_type());
			iterator tmp = find(k);
			if (tmp == this->end())
				tmp = insert(pair).first;
			return tmp->second;
		}

		iterator find(const key_type &k) {
			value_type pair(k, mapped_type());
			return iterator(_rbt.search_by_key(pair), _rbt.end());
		}

		const_iterator find(const key_type &k) const {
			value_type pair(k, mapped_type());
			return const_iterator(_rbt.search_by_key(pair), _rbt.end());
		}

		pair<iterator, bool> insert(const value_type &val) {
			return _rbt.insert(val, nullptr);
		}

		iterator insert(iterator position, const value_type &val) {
			return _rbt.insert(val, position.base()).first;
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = nullptr) {
			while (first != last) {
				_rbt.insert(*first, nullptr);
				first++;
			}
		}

		void erase(iterator position) { _rbt.erase(position.base()); }

		size_type erase(const key_type &k) { return _rbt.erase(ft::make_pair(k, mapped_type())); }

		void erase(iterator first, iterator last) {
			while (first != last) {
				key_type tmp = first->first;
				first++;
				this->erase(tmp);
			}
		}

		void swap(map &x) { _rbt.swap(x._rbt); }

		void clear() { _rbt.destroy(); }

		key_compare key_comp() const { return key_compare(); }

		value_compare value_comp() const { return value_compare(key_compare()); }

		size_type count(const key_type &k) const {
			const_iterator itr1 = this->begin();
			const_iterator itr2 = this->end();

			while (itr1 != itr2) {
				if (!_comp(itr1->first, k) && !_comp(k, itr1->first))
					return 1;
				itr1++;
			}
			return 0;
		}

		iterator lower_bound(const key_type &k) {
			iterator itr1 = this->begin();
			iterator itr2 = this->end();

			while (itr1 != itr2) {
				if (!_comp(itr1->first, k))
					break;
				itr1++;
			}
			return itr1;
		}

		const_iterator lower_bound(const key_type &k) const {
			const_iterator itr1 = this->begin();
			const_iterator itr2 = this->end();

			while (itr1 != itr2) {
				if (!_comp(itr1->first, k))
					break;
				itr1++;
			}
			return itr1;
		}

		iterator upper_bound(const key_type &k) {
			iterator itr1 = this->begin();
			iterator itr2 = this->end();

			while (itr1 != itr2) {
				if (_comp(k, itr1->first))
					break;
				itr1++;
			}
			return itr1;
		}

		const_iterator upper_bound(const key_type &k) const {
			const_iterator itr1 = this->begin();
			const_iterator itr2 = this->end();

			while (itr1 != itr2) {
				if (_comp(k, itr1->first))
					break;
				itr1++;
			}
			return itr1;
		}

		pair<iterator, iterator> equal_range(const key_type &k) {
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		allocator_type get_allocator() const { return allocator_type(); }

	private:
		key_compare _comp;
		allocator_type _alloc;
		RB_tree<value_type, Compare> _rbt;

	};

	template<class _Key, class _Tp, class _Compare, class _Allocator>
	bool
	operator==(const map<_Key, _Tp, _Compare, _Allocator> &__x,
			   const map<_Key, _Tp, _Compare, _Allocator> &__y) {
		return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
	}

	template<class _Key, class _Tp, class _Compare, class _Allocator>
	bool
	operator<(const map<_Key, _Tp, _Compare, _Allocator> &__x,
			  const map<_Key, _Tp, _Compare, _Allocator> &__y) {
		return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template<class _Key, class _Tp, class _Compare, class _Allocator>
	bool
	operator!=(const map<_Key, _Tp, _Compare, _Allocator> &__x,
			   const map<_Key, _Tp, _Compare, _Allocator> &__y) {
		return !(__x == __y);
	}

	template<class _Key, class _Tp, class _Compare, class _Allocator>
	bool
	operator>(const map<_Key, _Tp, _Compare, _Allocator> &__x,
			  const map<_Key, _Tp, _Compare, _Allocator> &__y) {
		return __y < __x;
	}

	template<class _Key, class _Tp, class _Compare, class _Allocator>
	bool
	operator>=(const map<_Key, _Tp, _Compare, _Allocator> &__x,
			   const map<_Key, _Tp, _Compare, _Allocator> &__y) {
		return !(__x < __y);
	}

	template<class _Key, class _Tp, class _Compare, class _Allocator>
	bool
	operator<=(const map<_Key, _Tp, _Compare, _Allocator> &__x,
			   const map<_Key, _Tp, _Compare, _Allocator> &__y) {
		return !(__y < __x);
	}

}

#endif //FT_CONTAINERS_MAP_HPP
