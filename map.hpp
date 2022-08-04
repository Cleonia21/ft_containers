//
// Created by Cleonia on 06.06.2022.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <iostream>
#include <unistd.h>
#include <memory>
#include "random_access_iterator.hpp"
#include "utils/utils.hpp"
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
		typedef pair<key_type, mapped_type> value_type;
		typedef Compare key_compare;

		class value_compare : std::binary_function<value_type, value_type, bool> {
			friend class map<key_type, mapped_type, key_compare, Alloc>;

		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
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
		typedef ft::rbt_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

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
				_rbt()
		{
			insert(first, last);
		}

		map(const map &x)
			:
			_comp(x.comp),
            _alloc(x.alloc),
            _rbt()
		{
			insert(x.begin(), x.end);
		}

		virtual ~map()
		{
			clear();
		}

		iterator 				begin() { return iterator(_rbt.begin(), _rbt.end()); }
		const_iterator 			begin() const { return const_iterator(_rbt.begin(), _rbt.end()); }
		iterator 				end() { return iterator(_rbt.end(), _rbt.end()); }
		const_iterator 			end() const { return const_iterator(_rbt.end(), _rbt.end()); }
		reverse_iterator 		rbegin() { return reverse_iterator(_rbt.end(), _rbt.end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_rbt.end(), _rbt.end()); }
		reverse_iterator 		rend() { return reverse_iterator(_rbt.begin(), _rbt.end()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(_rbt.begin(), _rbt.end()); }

		bool empty() const { return _rbt.begin() == _rbt.end(); }
		size_type size() const { return _rbt.size(); }
		size_type max_size() const { return allocator_type().max_size(); }

		mapped_type &operator[](const key_type &k)
		{
			iterator tmp = find(k);
			if (tmp == this->end())
//				tmp = insert();
			return (*tmp)->second;
		}

		iterator find (const key_type& k)
		{
			return iterator(_rbt.search_by_key(ft::make_pair(k, mapped_type())), _rbt->_last);
		}

		const_iterator find (const key_type& k) const
		{

		}

        pair<iterator, bool> insert(const value_type &val)
        {
            return _rbt.insert(val, nullptr);
        }

        iterator insert(iterator position, const value_type &val)
        {
            return _rbt.insert(val, position.base()).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
        {
            while (first != last)
            {
                _rbt.insert(*first, nullptr);
                first++;
            }
        }

        void erase(iterator position) { _rbt.erase(position.base()); }

        size_type erase(const key_type &k)
        {
            return _rbt.erase(ft::make_pair(k, mapped_type()));
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
                this->erase(first++);
        }

        void swap(map &x)
        {
            _rbt.swap(x._rbt);
        }

        void clear() { _rbt.destroy(); }

        key_compare key_comp() const { return key_compare(); }
        value_compare value_comp() const { return value_compare(); }

        size_type count(const key_type &k) const
        {
            iterator begin = begin();
            iterator end = end();

            while (begin != end)
            {
                if (!key_compare(begin->first, k) && !key_compare(k, begin->first))
                    return 1;
                begin++;
            }
            return 0;
        }

        iterator lower_bound(const key_type &k)
        {
            iterator begin = begin();
            iterator end = end();

            while (begin != end)
            {
                if (!key_compare(begin->first, k) && !key_compare(k, begin->first)
                    || key_compare(begin->first, k))
                    return begin;
                begin++;
            }
            return end;
        }

//        const_iterator lower_bound(const key_type &k) const;

        iterator upper_bound(const key_type &k)
        {
            iterator begin = begin();
            iterator end = end();

            while (begin != end)
            {
                if (key_compare(begin->first, k))
                    return begin;
                begin++;
            }
            return end;
        }

//        const_iterator upper_bound(const key_type &k) const;

//        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            
        }

        allocator_type get_allocator() const { return allocator_type(); }

	private:
		allocator_type                          _alloc;
		Compare                                 _comp;
		RB_tree<value_type, Compare>  			_rbt;

	};




}


#endif //FT_CONTAINERS_MAP_HPP
