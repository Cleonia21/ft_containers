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


namespace ft {

	enum RBT_color { black, red };

	template<class T>
	struct RB_node {

		typedef T value_type;

		value_type value;
		RB_node *left;
		RB_node *right;
		RB_node *parent;
		RBT_color	color;

		RB_node()
				:
				value(),
				left(nullptr),
				right(nullptr),
				parent(nullptr),
				color(red) {}

		RB_node(value_type _value, RB_node *left = nullptr,
				RB_node *right = nullptr, RB_node *parent = nullptr)
				:
				value(_value),
				left(left),
				right(right),
				parent(parent),
				color(red) {}

		RB_node(const RB_node& a)
				:
				value(a.value),
				left(a.left),
				right(a.right),
				parent(a.parent),
				color(a.color) {}

		virtual ~RB_node() {}

		RB_node &operator=(const RB_node &a)
		{
			if (&a == this)
				return *this;
			value = a.value;
			left = a.left;
			right = a.right;
			parent = a.parent;
			color = a.color;
			return *this;
		}

		bool operator==(const RB_node& nd)
		{
			if (value == nd.value)
				return (true);
			return (false);
		}

	};

	template<class T, class Compare = std::less<T>, class Node = RB_node<T>,
			class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
	class RB_tree
	{
	public:

		RB_tree(const Node_Alloc &alloc = Node_Alloc())
				:
				_root(nullptr),
				_alloc(alloc),
				_size(0)
		{
			_last = _alloc.allocate(1);
			_alloc.construct(_last);
			_last->left = _last->right = nullptr;
		}

		~RB_tree()
		{
			destroy(_root);
		}

		Node* insert(T key)
		{
			_size++;
			Node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, key);

			Node* x = _root;
			Node* y = nullptr;

			while (x != nullptr)
			{
				y = x;
				if (_compare(new_node->value, y->value))
					x = x->left;
				else
					x = x->right;
			}
			new_node->parent = y;
			if (y != nullptr)
			{
				if (_compare(new_node->value, y->value))
					y->left = new_node;
				else
					y->right = new_node;
			}
			else
				_root = new_node;

			return insert_fix(new_node);
		}

		void erase(T key)
		{
			Node* node = search(key, _root);
			if (node == nullptr)
				return ;
			_size--;

			Node* child;
			if (node->right && node->left)
			{
				child = node->right;
				while (child->left)
					child = child->left;
//				swap(node, child);
				node->value = child->value;
				node = child;
			}

			if (node->left)
				child = node->left;
			else if (node->right)
				child = node->right;
			else
				child = nullptr;

			//swap
			if (child)
				child->parent = node->parent;
			if (node->parent && node == node->parent->left)
				node->parent->left = child;
			else if (node->parent)
				node->parent->right = child;

			if (node->color == black)
			{
				if (child)
					child->color = black;
				else
					erase_fix(node->parent, child);
			}
			if (node->parent == nullptr && (!child || child->parent == nullptr))
				_root = child;
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}

		void swap(Node *upper, Node *lower)
		{
			if (!upper || !lower)
				return;
			lower->parent = upper->parent;
			if (upper == upper->parent->left)
				upper->parent->left = lower;
			else
				upper->parent->right = lower;
		}

		Node* search_by_key(T& value)
		{
			Node* tmp = search(value, _root);
			if (!tmp)
				return _last;
			return tmp;
		}

		void print()
		{
			print(_root);
		}

		Node* end()
		{
			Node* tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			_last->parent = tmp;
			return _last;
		}

		Node* begin()
		{
			if (_root == nullptr)
				return _last;
			Node* tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		size_t size() { return _size; }

	private:

		void erase_fix(Node* parent, Node* node)
		{
			// case 1
			if (parent == nullptr)
			{
				_root = node;
				return ;
			}

			// case 2
			Node* sibling = get_sibling(parent, node);
			if (sibling->color == red)
			{
				parent->color = red;
				sibling->color = black;
				if (node == parent->left)
					left_rotate(parent);
				else
					right_rotate(parent);
			}

			// case 3
			sibling = get_sibling(parent, node);
			if (parent->color == black &&
				sibling->color == black &&
				(!sibling->left || sibling->left->color == black) &&
				(!sibling->right || sibling->right->color == black))
			{
				sibling->color = red;
				erase_fix(parent->parent, parent);
				return ;
			}

			// case 4
			sibling = get_sibling(parent, node);
			if (parent->color == red &&
				sibling->color == black &&
				(!sibling->left || sibling->left->color == black) &&
				(!sibling->right || sibling->right->color == black))
			{
				sibling->color = red;
				parent->color = black;
				return ;
			}

			// case 5
			sibling = get_sibling(parent, node);
			if (sibling->color == black)
			{
				if ((node == parent->left) &&
					(!sibling->right || sibling->right->color == black) &&
					(sibling->left && sibling->left->color == red))
				{
					sibling->color = red;
					sibling->left->color = black;
					right_rotate(sibling);
				}
				else if (
						(node == parent->right) &&
						(!sibling->left || sibling->left->color == black) &&
						(sibling->right && sibling->right->color == red)
						)
				{
					sibling->color = red;
					sibling->right->color = black;
					left_rotate(sibling);
				}
			}

			// case 6
			sibling = get_sibling(parent, node);
			sibling->color = parent->color;
			parent->color = black;

			if (node == parent->left)
			{
				if (sibling->right)
					sibling->right->color = black;
				left_rotate(parent);
			}
			else
			{
				if (sibling->left)
					sibling->left->color = black;
				right_rotate(parent);
			}


/*
			Node* child = node->left;
			RBT_color l_child_color = black, r_child_color = black;
			if (child->left)
				l_child_color = child->left->color;
			if (child->right)
				r_child_color = child->right->color;

			//КЧ1
			if (node->color == red &&
				l_child_color == black &&
				r_child_color == black)
			{
				node->color = black;
				child->color = red;
				return ;
			}

			//КЧ2
			if (node->color == red &&
				child->color == black &&
				l_child_color == red)
			{
				node->color = black;
				child->color = red;
				child->left->color = black;
				right_rotate(node);
				return ;
			}

*/
/*
			// case 1
			if (!node->parent)
			{
				std::cout << "Not parent" << std::endl;
				_root = node;
				return;
			}

			// case 2
			Node* brother = get_brother(node);
			if (!brother)
			{
				std::cout << "Not brother" << std::endl;
				return ;
			}
			if (brother->color == red)
			{
				node->parent->color = red;
				brother->color = black;
				if (node == node->parent->left)
					left_rotate(node->parent);
				else
					right_rotate(node->parent);
			}

			// case 3
			brother = get_brother(node);
			if (!brother)
			{
				std::cout << "Not brother" << std::endl;
				return ;
			}
			if (node->parent->color == black &&
				brother->color == black &&
				(!brother->left || brother->left->color == black) &&
				(!brother->right || brother->right->color == black))
			{
				brother->color = red;
				erase_fix(node->parent);
				return ;
			}

			// case 4
			if (node->parent->color == red &&
				brother->color == black &&
				(!brother->left || brother->left->color == black) &&
				(!brother->right || brother->right->color == black))
			{
				brother->color = red;
				node->parent->color = black;
				return ;
			}

			// case 5
			if (brother->color == black)
			{
				if ((node == node->parent->left) &&
					(!brother->right || brother->right->color == black) &&
					(brother->left && brother->left->color == red))
				{
					brother->color = red;
					brother->left->color = black;
					right_rotate(brother);
				}
				else if ((node == node->parent->right) &&
					(!brother->right || brother->right->color == red) &&
					(brother->left && brother->left->color == black))
				{
					brother->color = red;
					brother->right->color = black;
					right_rotate(brother);
				}
			}

			// case 6
			brother = get_brother(node);
			if (!brother)
			{
				std::cout << "Not brother" << std::endl;
				return ;
			}
			if (!node->parent)
			{
				std::cout << "Not parent" << std::endl;
				return ;
			}
			brother->color = node->parent->color;
			node->parent->color = black;
			if (node == node->parent->left) {
				brother->right->color = black;
				left_rotate(node->parent);
			} else {
				brother->left->color = black;
				right_rotate(node->parent);
			}
*/
		}

		Node* get_sibling(Node* parent, Node* node)
		{
			if (node == parent->left)
				return parent->right;
			else
				return parent->left;
		}

		Node* get_brother(Node* node)
		{
			if (node->parent && node == node->parent->left)
				return node->parent->right;
			else if (node->parent)
				return node->parent->left;
		}

		void destroy(Node* node)
		{
			if (node == nullptr)
				return ;
			destroy(node->left);
			destroy(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			node = nullptr;
		}

		void print(Node *node)
		{
			if (node == nullptr)
				return;
			if (node->parent == nullptr)
				std::cout << node->value << "(" << node->color << ") is root" << std::endl;
			else if(node->parent->left==node)
			{
				std::cout << node->value << "(" << node->color << ") is "<<node->parent->value<<"'s "<<"left child" << std::endl;
			}
			else
			{
				std::cout << node->value << "(" << node->color << ") is " << node->parent->value << "'s " << "right child" << std::endl;
			}
			print(node->left);
			print(node->right);
		}

		Node* search(T& value, Node *node)
		{
			if (node == nullptr || (!_compare(node->value->first, value->first)
									&& (!_compare(value->first, node->value->first))))
				return node;
			if (_compare(value->first, node->value->first))
				return search(value, node->left);
			if (_compare(node->value->first, value->first))
				return search(value, node->right);
			return nullptr;
		}

		Node* insert_fix(Node* node)
		{
			if (node->parent == nullptr)
			{
				node->color = black;
				return node;
			}
			if (node->parent->color == black)
				return node;

			Node* grandparent = node->parent->parent;
			Node* uncle = nullptr;
			if (grandparent)
			{
				uncle = grandparent->right;
				if (node->parent == grandparent->right)
					uncle = grandparent->left;
			}

			if (uncle && uncle->color == red)
			{
				node->parent->color = black;
				uncle->color = black;
				grandparent->color = red;
				insert_fix(grandparent);
				return nullptr;
			}
			else {
				if (node == node->parent->right
					&& node->parent == grandparent->left) {
					left_rotate(node->parent);
					node = node->left;
				} else if (node == node->parent->left
						   && node->parent == grandparent->right) {
					right_rotate(node->parent);
					node = node->right;
				}
			}
			node->parent->color = black;
			grandparent = node->parent->parent;
			grandparent->color = red;
			if (node == node->parent->left
				&& node->parent == grandparent->left)
				right_rotate(grandparent);
			else
				left_rotate(grandparent);
			return node;
		}

		void left_rotate(Node* node)
		{
//			std::cout << "left rotate" << std::endl;
			Node* pivot = node->right;
			pivot->parent = node->parent;
			if (node->parent != nullptr)
			{
				if (node->parent->left == node)
					node->parent->left = pivot;
				else
					node->parent->right = pivot;
			}
			node->right = pivot->left;
			if (pivot->left != nullptr)
				pivot->left->parent = node;

			node->parent = pivot;
			pivot->left = node;
			if (pivot->parent == nullptr)
				_root = pivot;
		}

		void right_rotate(Node* node)
		{
//			std::cout << "right rotate" << std::endl;
			Node* pivot = node->left;
			pivot->parent = node->parent;
			if (node->parent != nullptr)
			{
				if (node->parent->left == node)
					node->parent->left = pivot;
				else
					node->parent->right = pivot;
			}
			node->left = pivot->right;
			if (pivot->right != nullptr)
				pivot->right->parent = node;

			node->parent = pivot;
			pivot->right = node;
			if (pivot->parent == nullptr)
				_root = pivot;
		}

		Node_Alloc _alloc;
		Node* _root;
		Node* _last;
		Compare _compare;
		size_t _size;
	};

	template<class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
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
		typedef ft::rbt_iterator<value_type> iterator;
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
/*
		template<class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
				:
				_comp(comp),
				_alloc(alloc),
				_rbt()
		{
//			insert(first, last);
		}

		map(const map &x)
			:
			_comp(x.comp),
			_alloc(x.alloc),
			_rbt()
		{
//			insert(first, last);
		}

		virtual ~map()
		{
//			clear();
		}
*/
		iterator 				begin() { return iterator(_rbt.begin, _rbt.end()); }
		const_iterator 			begin() const { return const_iterator(_rbt.begin, _rbt.end()); }
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

/*

		pair<iterator, bool> insert(const value_type &val);

		iterator insert(iterator position, const value_type &val);

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last);

		void erase(iterator position);

		size_type erase(const key_type &k);

		void erase(iterator first, iterator last);

		void swap(map &x);

		void clear();

		key_compare key_comp() const;

		value_compare value_comp() const;

		size_type count(const key_type &k) const;

		iterator lower_bound(const key_type &k);

		const_iterator lower_bound(const key_type &k) const;

		iterator upper_bound(const key_type &k);

		const_iterator upper_bound(const key_type &k) const;

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

		pair<iterator, iterator> equal_range(const key_type &k);

		allocator_type get_allocator() const;
		*/
	private:
		allocator_type                          _alloc;
		Compare                                 _comp;
		RB_tree<value_type, Compare>  			_rbt;

	};




}


#endif //FT_CONTAINERS_MAP_HPP
