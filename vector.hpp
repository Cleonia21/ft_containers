//
// Created by Cleonia on 06.06.2022.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>
#include <unistd.h>
#include <memory>
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"


namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector {

	public:

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type    difference_type;
		typedef typename allocator_type::size_type size_type;

		explicit vector(const allocator_type &alloc = allocator_type())
				:
				_alloc(alloc),
				_start(nullptr),
				_end(nullptr),
				_endCapacity(nullptr) {}

		vector(size_type n, const value_type &val = value_type(),
			   const allocator_type &alloc = allocator_type())
				:
				_alloc(alloc) {
			_start = _alloc.allocate(n);
			_endCapacity = _start + n;
			_end = _start;
			while (n--) {
				_alloc.construct(_end, val);
				_end++;
			}
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = nullptr)
				:
				_alloc(alloc)
				{
			size_type n = ft::distance(first, last);
			_start = _alloc.allocate(n);
			_endCapacity = _start + n;
			_end = _start;
			while (first != last) {
				_alloc.construct(_end, *first);
				_end++;
				first++;
			}
		}

		vector(const vector &x)
				:
				_alloc(x._alloc),
				_start(nullptr),
				_end(nullptr),
				_endCapacity(nullptr) {
			insert(this->begin(), x.begin(), x.end());
		}

		vector &operator=(const vector &p) {
			if (*this == p)
				return (*this);
			clear();
			insert(this->begin(), p.begin(), p.end());
			return (*this);
		}

		~vector() {
			clear();
		}

		iterator begin() {
			return iterator(_start);
		}

		const_iterator begin() const {
			return const_iterator(_start);
		}

		iterator end() {
			return iterator(_end);
		}

		const_iterator end() const {
			return const_iterator(_end);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const {
			return reverse_iterator(this->end());
		}

		reverse_iterator rend() {
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend() const {
			return reverse_iterator(this->begin());
		}

		size_type size() const {
			return (_end - _start);
		}

		size_type max_size() const {
			return allocator_type().max_size();
		}

		void resize(size_type n, value_type val = value_type()) {
			if (n > capacity())
				this->reserve(n);
			if (n < (unsigned long) (_end - _start))
				_end = _start + n;
			while ((unsigned long) (_end - _start) < n) {
				_alloc.construct(_end, val);
				_end++;
			}
		}

		size_type capacity() const {
			return (_endCapacity - _start);
		}

		bool empty() const {
			return (this->size() == 0);
		}

		void reserve(size_type n) {
			if (n > this->capacity()) {
				pointer prev_start = _start;
				pointer prev_end = _end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();

				_start = _alloc.allocate(n);
				_endCapacity = _start + n;
				_end = _start;
				while (prev_start != prev_end) {
					_alloc.construct(_end, *prev_start);
					_end++;
					prev_start++;
				}
				prev_start -= prev_size;
				while (prev_start != prev_end) {
					_alloc.destroy(prev_start);
					prev_start++;
				}
				if (prev_start)
					_alloc.destroy(prev_start);
				_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		reference operator[](size_type n) {
			return *(_start + n);
		}

		const_reference operator[](size_type n) const {
			return *(_start + n);
		}

		reference at(size_type n) {
			if (n >= this->size())
				throw std::out_of_range("vector::_M_range_check");
			return this->operator[](n);
		}

		const_reference at(size_type n) const {
			if (n >= this->size())
				throw std::out_of_range("vector::_M_range_check");
			return this->operator[](n);
		}

		reference front() {
			return *_start;
		}

		const_reference front() const {
			return *_start;
		}

		reference back() {
			return *(_end - 1);
		}

		const_reference back() const {
			return *(_end - 1);
		}

		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = nullptr) {
			this->clear();
			size_type n = ft::distance(first, last);
			if (n > this->capacity())
				this->reserve(n);
			while (first != last) {
				_alloc.construct(_end, *first);
				_end++;
				first++;
			}
		}

		void assign(size_type n, const value_type &val) {
			this->clear();
			if (n > this->capacity())
				this->reserve(n);
			while (n--) {
				_alloc.construct(_end, val);
				_end++;
			}
		}

		void push_back(const value_type &val) {
			if (this->size() == this->capacity())
				this->reserve((this->size() + 1) * 2);
			_alloc.construct(_end, val);
			_end++;
		}

		void pop_back() {
			if (this->size() > 0) {
				_end--;
				_alloc.destroy(_end);
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			pointer tmp = shift(position, 1);
			_alloc.construct(tmp, val);
			return (iterator(tmp));
		}

		void insert(iterator position, size_type n, const value_type &val) {
			pointer tmp = shift(position, n);
			while (n--)
				_alloc.construct(tmp++, val);
		}


		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = nullptr) {
			size_type n = ft::distance(first, last);
			pointer tmp = shift(position, n);
			while (&(*first) != &(*last)) {
				_alloc.construct(tmp, *first);
				tmp++;
				first++;
			}
		}

		iterator erase(iterator position) {
			pointer tmp = _start;
			while (tmp != &(*position) && tmp != _end)
				tmp++;
			if (tmp == _end)
				return iterator(_end);

			for (int i = 0; tmp + 1 + i != _end; i++) {
				_alloc.destroy(tmp + i);
				_alloc.construct(tmp + i, *(tmp + i + 1));
			}
			_alloc.destroy(_end - 1);
			_end--;
			return iterator(tmp);
		}

		iterator erase(iterator first, iterator last) {
			pointer tmp = _start;
			while (tmp != &(*first) && tmp != _end)
				tmp++;
			if (tmp == _end)
				return iterator(_end);

			size_type n = ft::distance(first, last);

			int i = 0;
			for (; tmp + i + n != _end; i++) {
				_alloc.destroy(tmp + i);
				_alloc.construct(tmp + i, *(tmp + n + i));
			}
			for (; tmp + i != _end; i++)
				_alloc.destroy(tmp + i);
			_end -= n;
			return iterator(tmp);
		}

		void swap(vector &x) {
			if (x == *this)
				return;

			allocator_type tmpAlloc = x._alloc;
			pointer tmpStart = x._start;
			pointer tmpEnd = x._end;
			pointer tmpEndCapacity = x._endCapacity;

			x._alloc = _alloc;
			x._start = _start;
			x._end = _end;
			x._endCapacity = _endCapacity;

			_alloc = tmpAlloc;
			_start = tmpStart;
			_end = tmpEnd;
			_endCapacity = tmpEndCapacity;
		}

		void clear() {
			if (_start == _end)
				return;
			while (_start != --_end)
				_alloc.destroy(_end);
			_alloc.destroy(_end);
			_alloc.deallocate(_start, _endCapacity - _start);
			_start = nullptr;
			_end = nullptr;
			_endCapacity = nullptr;
		}

		allocator_type get_allocator() const {
			return _alloc;
		}

	private:

		allocator_type _alloc;
		pointer _start;
		pointer _end;
		pointer _endCapacity;

		pointer shift(iterator &position, size_type n) {
			if (size() + n > capacity()) {
				size_type newCapacity = size() + n;
				pointer prev_start = _start;
				pointer prev_end = _end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();
				size_type posLen = &(*position) - _start;

				_start = _alloc.allocate(newCapacity);
				_endCapacity = _start + newCapacity;
				_end = _start;

				for (size_type i = 0; prev_start != prev_end; i++) {
					if (i < posLen || i >= posLen + n) {
						_alloc.construct(_end, *prev_start);
						prev_start++;
					}
					_end++;
				}
				if (_start + posLen == _end)
					_end += n;

				prev_start -= prev_size;
				if (!prev_start)
					return _start + posLen;
				while (prev_start != prev_end) {
					_alloc.destroy(prev_start);
					prev_start++;
				}
				_alloc.destroy(prev_start);
				_alloc.deallocate(prev_start - prev_size, prev_capacity);
				return _start + posLen;
			} else {
				size_type posLen = _end - &(*position);
				for (size_type i = 0; i < posLen; i++) {
					_alloc.construct(_end - i + n - 1, *(_end - i - 1));
				}
				_end += n;
				return (_end - posLen - n);
			}
		}

	};

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator first1 = lhs.begin();
		typename ft::vector<T>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end()) {
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

}

#endif //FT_CONTAINERS_VECTOR_HPP
