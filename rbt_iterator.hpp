//
// Created by Cleonia on 01.08.2022.
//

#ifndef FT_CONTAINERS_RBT_ITERATOR_HPP
#define FT_CONTAINERS_RBT_ITERATOR_HPP


#include <iterator>
#include "utils/utils.hpp"

namespace ft {


	template<typename T>
	class rbt_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
	public:
		typedef bidirectional_iterator_tag	iterator_category;
		typedef typename T::value_type 		value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer	pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference	reference;

		rbt_iterator()
				:
				_node(),
				_last() {}

		rbt_iterator(T* node, T* last)
				:
				_node(node),
				_last(last) {}

		rbt_iterator(const rbt_iterator &p)
				:
				_node(p._node),
				_last(p._last) {}

		rbt_iterator &operator=(const rbt_iterator &p) {
			if (this == &p)
				return (*this);
			this->_node = p._node;
			this->_last = p._last;
			return *this;
		}

		virtual ~rbt_iterator() {}

        T* base() const { return _node; }
		reference operator*() const { return _node->value; }
		pointer operator->() const { return &(_node->value); }

		rbt_iterator& operator++(void)
		{
			if (_node->right)
			{
				_node = _node->right;
				while (_node->left)
					_node = _node->left;
			}
			else
			{
				while (true)
				{
					if (_node->parent == nullptr)
					{
						_node = _last;
						break ;
					}
					else if (_node == _node->parent->right)
						_node = _node->parent;
					else if (_node == _node->parent->left)
					{
						_node = _node->parent;
						break ;
					}
				}
			}
			return *this;
		}

		rbt_iterator operator++(int)
		{
			rbt_iterator ret(*this);
			operator++();
			return ret;
		}

		rbt_iterator& operator--(void)
		{
			if (_node->left)
			{
				_node = _node->left;
				while (_node->right)
					_node = _node->right;
			}
			else
			{
				while (true)
				{
					if (_node->parent == nullptr)
					{
						_node = _last;
						break ;
					}
					else if (_node == _node->parent->left)
						_node = _node->parent;
					else if (_node == _node->parent->right || _node == _last)
					{
						_node = _node->parent;
						break ;
					}
				}
			}
			return *this;
		}

		bool operator!=(const rbt_iterator& bst_it)
		{ return (this->_node != bst_it._node); }


/*
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
*/
	private:
		T* _node;
		T* _last;
	};

/*
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
	operator!=(const ft::rbt_iterator<T> lhs,
			   const ft::rbt_iterator<T> rhs)
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

*/
}

#endif //FT_CONTAINERS_RBT_ITERATOR_HPP
