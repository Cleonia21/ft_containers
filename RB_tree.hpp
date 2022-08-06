//
// Created by mac on 03/08/2022.
//

#ifndef FT_CONTAINERS_RB_TREE_HPP
#define FT_CONTAINERS_RB_TREE_HPP

#include <iostream>
#include <unistd.h>
#include <memory>

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

        virtual ~RB_node()
		{
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}

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

    };

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

		rbt_iterator operator--(int)
		{
			rbt_iterator ret(*this);
			operator--();
			return ret;
		}

		bool operator!=(const rbt_iterator& bst_it)
		{ return (this->_node != bst_it._node); }

		bool operator==(const rbt_iterator& bst_it)
		{ return (!operator!=(bst_it)); }

		T* _node;
		T* _last;
	};

	template<typename T>
	class rbt_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
	public:
		typedef bidirectional_iterator_tag	iterator_category;
		typedef typename T::value_type 		value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, const value_type>::pointer	pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, const value_type>::reference	reference;

		rbt_const_iterator()
				:
				_node(),
				_last() {}

		rbt_const_iterator(T* node, T* last)
				:
				_node(node),
				_last(last) {}

		rbt_const_iterator(const rbt_const_iterator &p)
				:
				_node(p._node),
				_last(p._last) {}

		rbt_const_iterator(const rbt_iterator<T> &p)
				:
				_node(p._node),
				_last(p._last) {}

		rbt_const_iterator &operator=(const rbt_const_iterator &p) {
			if (this == &p)
				return (*this);
			this->_node = p._node;
			this->_last = p._last;
			return *this;
		}

		virtual ~rbt_const_iterator() {}

		T* base() const { return _node; }
		reference operator*() const { return _node->value; }
		pointer operator->() const { return &(_node->value); }

		rbt_const_iterator& operator++(void)
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

		rbt_const_iterator operator++(int)
		{
			rbt_const_iterator ret(*this);
			operator++();
			return ret;
		}

		rbt_const_iterator& operator--(void)
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

		rbt_const_iterator operator--(int)
		{
			rbt_const_iterator ret(*this);
			operator--();
			return ret;
		}

		bool operator!=(const rbt_const_iterator& bst_it)
		{ return (this->_node != bst_it._node); }

		bool operator==(const rbt_const_iterator& bst_it)
		{ return (!operator!=(bst_it)); }

		T* _node;
		T* _last;
	};

    template<class T, class Compare = std::less<T>, class Node = RB_node<T>,
            class Alloc = std::allocator<Node> >
    class RB_tree
    {
    public:
		typedef typename T::first_type first_type;
		typedef Node	node;
		typedef Node*	node_pointer;
		typedef Node&	node_reference;
		typedef Alloc	allocator_type;
        typedef ft::rbt_iterator<node> iterator;
		typedef ft::rbt_const_iterator<node> const_iterator;
		typedef typename allocator_type::size_type size_type;

        RB_tree(const allocator_type &alloc = allocator_type())
                :
                _root(nullptr),
                _alloc(alloc),
                _size(0)
        {
            _last = _alloc.allocate(1);
            _alloc.construct(_last);
            _last->left = _last->right = _last->parent = nullptr;
        }

        ~RB_tree() {
			destroy();
			_alloc.destroy(_last);
			_alloc.deallocate(_last, 1);
		}

        ft::pair<iterator, bool> insert(T key, node* position)
        {
            node* tmp = _root;
            if (position && position->parent)
            {
                if (position == position->parent->left &&
                    _compare(key.first, position->parent->value.first))
                    tmp = position;
                if (position == position->parent->right &&
                    _compare(position->parent->value.first, key.first))
                    tmp = position;
            }

            node* previous = nullptr;
            while (tmp != nullptr)
            {
                previous = tmp;
                if (_compare(key.first, previous->value.first))
                    tmp = tmp->left;
                else if (_compare(previous->value.first, key.first))
                    tmp = tmp->right;
                else
                    return ft::make_pair(iterator(previous, end()), false);
            }
            node* new_node = _alloc.allocate(1);
            _alloc.construct(new_node, key);
            new_node->parent = previous;
            if (previous != nullptr)
            {
                if (_compare(new_node->value.first, previous->value.first))
                    previous->left = new_node;
                else
                    previous->right = new_node;
            }
            else
                _root = new_node;

			_size++;
			insert_fix(new_node);
            return ft::make_pair(iterator(new_node, end()), true);
        }

		size_type erase(T key)
        {
            node* node = search(key, _root);
            if (node == nullptr)
                return 0;
            erase(node);
            return 1;
        }

        void erase(Node* node)
        {
            _size--;
            node_pointer child;

            if (node->right && node->left)
            {
                child = node->right;
                while (child->left)
                    child = child->left;
				swap_node(node, child);
				if (child->parent == nullptr)
					_root = child;
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

		void swap_feedback(node *node)
		{
			if (!node)
				return ;
			if (node->left)
				node->left->parent = node;
			if (node->right)
				node->right->parent = node;
		}

		void swap_node(node* a, node *b)
		{
			node tmp(*b);
			b->color = a->color;
			a->color = tmp.color;

			if (a == b->parent) {
				b->parent = a->parent;
				a->parent = b;
				if (b->parent && a == b->parent->left)
					b->parent->left = b;
				else if (b->parent)
					b->parent->right = b;
				if (b == a->left) {
					b->left = a;
					b->right = a->right;
					if (b->right)
						b->right->parent = b;
				} else {
					b->right = a;
					b->left = a->left;
					if (b->left)
						b->left->parent = b;
				}
			} else {
				b->parent = a->parent;
				a->parent = tmp.parent;
				if (a->parent && a == a->parent->left)
					a->parent->left = b;
				else if (a->parent)
					a->parent->right = b;
				if (b->parent && b == b->parent->left)
					b->parent->left = a;
				else if (b->parent)
					b->parent->right = a;

				b->left = a->left;
				b->right = a->right;
				swap_feedback(b);
			}
			a->left = tmp.left;
			a->right = tmp.right;
			swap_feedback(a);
		}

        void swap(RB_tree& p)
        {
            if (this == &p)
                return ;
            node* tmp = _root;
            _root = p._root;
            p._root = tmp;

            tmp = _last;
            _last = p._last;
            p._last = tmp;

			Compare comp = _compare;
			_compare = p._compare;
			p._compare = comp;

			size_type size = _size;
			_size = p._size;
			p._size = size;
        }

        node* search_by_key(T& value) const
        {
            node* tmp = search(value, _root);
            if (!tmp)
                return _last;
            return tmp;
        }

        void print()
        {
            print(_root);
        }

        node* end() const
        {
            if (_root == nullptr)
                return _last;
            node* tmp = _root;
            while (tmp->right)
                tmp = tmp->right;
            _last->parent = tmp;
            return _last;
        }

        node* begin() const
        {
            if (_root == nullptr)
                return _last;
            node* tmp = _root;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }

		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

        void destroy()
        {
            destroy(_root);
            _root = nullptr;
			_size = 0;
        }

    private:

        void erase_fix(node* parent, node* node)
        {
            // case 1
            if (parent == nullptr)
            {
                _root = node;
                return ;
            }

            // case 2
            node_pointer sibling = get_sibling(parent, node);
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
        }

        node* get_sibling(node* parent, node* node)
        {
            if (node == parent->left)
                return parent->right;
            else
                return parent->left;
        }

        node* get_brother(node* node)
        {
            if (node->parent && node == node->parent->left)
                return node->parent->right;
            else if (node->parent)
                return node->parent->left;
        }

        void destroy(node* node)
        {
            if (node == nullptr)
                return ;
            destroy(node->left);
            destroy(node->right);
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
            node = nullptr;
        }

        void print(node *node)
        {
            if (node == nullptr)
                return;
            if (node->parent == nullptr)
                std::cout << '{' << node->value.first << " , " << node->value.second << '}' << "(" << node->color << ") is root" << std::endl;
            else if(node->parent->left == node)
            {
                std::cout << '{' << node->value.first << " , " << node->value.second << '}' << "(" << node->color << ") is "<< '{' << node->parent->value.first << " , " << node->parent->value.second << '}' <<"'s "<<"left child" << std::endl;
            }
            else
            {
                std::cout << '{' << node->value.first << " , " + node->value.second << '}' << "(" << node->color << ") is " << '{' << node->parent->value.first << " , " << node->parent->value.second << '}' << "'s " << "right child" << std::endl;
            }
            print(node->left);
            print(node->right);
        }

        node* search(T& value, node *node) const
        {
            if (node == nullptr || (!_compare(node->value.first, value.first)
                                    && (!_compare(value.first, node->value.first))))
                return node;
            if (_compare(value.first, node->value.first))
                return search(value, node->left);
            if (_compare(node->value.first, value.first))
                return search(value, node->right);
            return nullptr;
        }

        node* insert_fix(node* node)
        {
            if (node->parent == nullptr)
            {
                node->color = black;
                return node;
            }
            if (node->parent->color == black)
                return node;

            node_pointer grandparent = node->parent->parent;
            node_pointer uncle = nullptr;
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

        void left_rotate(node* node)
        {
            node_pointer pivot = node->right;
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

        void right_rotate(node* node)
        {
            node_pointer pivot = node->left;
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

		node_pointer _root;
		allocator_type _alloc;
        node_pointer _last;
        Compare _compare;
		size_type _size;
    };

}

#endif //FT_CONTAINERS_RB_TREE_HPP
