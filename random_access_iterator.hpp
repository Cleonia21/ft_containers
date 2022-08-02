//
// Created by Cleonia on 10.06.2022.
//

#ifndef FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include "utils/utils.hpp"

namespace ft {

	template<typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type 		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef T*	pointer;
		typedef T&	reference;

		random_access_iterator()
				:
				_elem(nullptr) {}

		explicit random_access_iterator(pointer elem)
				:
				_elem(elem) {}

		random_access_iterator(const random_access_iterator &p)
				:
				_elem(p._elem) {}

		random_access_iterator &operator=(const random_access_iterator &p) {
			if (this == &p)
				return (*this);
			this->_elem = p._elem;
			return *this;
		}

		virtual ~random_access_iterator() {}

		pointer base() const { return (this->_elem); }

		reference operator*() const { return (*_elem); }
		pointer operator->() const { return _elem; }

		random_access_iterator &operator++(void) { _elem++; return *this; }

		random_access_iterator operator++(int) {
			random_access_iterator ret(*this);
			_elem++;
			return ret;
		}

		random_access_iterator &operator--(void) {
			_elem--;
			return *this;
		}

		random_access_iterator operator--(int) {
			random_access_iterator ret(*this);
			_elem--;
			return ret;
		}

		random_access_iterator operator+(difference_type n) const {
			random_access_iterator ret(_elem + n);
			return (ret);
		}

		random_access_iterator operator-(difference_type n) const {
			random_access_iterator ret(_elem - n);
			return (ret);
		}

		random_access_iterator &operator+=(difference_type n) {
			_elem += n;
			return *this;
		}

		random_access_iterator &operator-=(difference_type n) {
			_elem -= n;
			return *this;
		}

		reference operator[](difference_type n) { return (*(operator+(n))); }

		operator random_access_iterator<const T>() const {
			return (random_access_iterator<const T>(this->_elem));
		}

	private:
		pointer _elem;
	};


	template <typename T>
	bool
	operator==(const ft::random_access_iterator<T> lhs,
			   const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename T_R>
	bool
	operator==(const ft::random_access_iterator<T_L> lhs,
			   const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
//	typename ft::random_access_iterator<T>::difference_type
	bool
	operator!=(const ft::random_access_iterator<T> lhs,
			   const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool
	operator!=(const ft::random_access_iterator<T_L> lhs,
			   const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
//	typename ft::random_access_iterator<T>::difference_type
	bool
	operator<(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool
	operator<(const ft::random_access_iterator<T_L> lhs,
			  const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
//	typename ft::random_access_iterator<T>::difference_type
	bool
	operator>(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T_L,
			typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool
	operator>(const ft::random_access_iterator<T_L> lhs,
			  const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
//	typename ft::random_access_iterator<T>::difference_type
	bool
	operator<=(const ft::random_access_iterator<T> lhs,
			   const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool
	operator<=(const ft::random_access_iterator<T_L> lhs,
			   const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
//	typename ft::random_access_iterator<T>::difference_type
	bool
	operator>=(const ft::random_access_iterator<T> lhs,
			   const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T_L,
			typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool
	operator>=(const ft::random_access_iterator<T_L> lhs,
			   const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	ft::random_access_iterator<T> operator+(
			typename ft::random_access_iterator<T>::difference_type n,
			typename ft::random_access_iterator<T>& rai)
	{
		return (rai + n);
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator-(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
//	size_t
	operator-(const ft::random_access_iterator<T_L> lhs,
			  const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() - rhs.base());
	}


}


#endif //FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
