/* Samantha Rack
 * CSE 30331
 * Program 2
 * map.h
 */

#ifndef ND_MAP_H
#define ND_MAP_H

#include <stack>

namespace fightingirish {

	/**********************************************
	 * struct binary_node <T>
	 * A node of a binary tree (without parent pointers).
	 * You shouldn't need to change anything here.
	 **********************************************/
	template <typename T>
	struct binary_node {
		T value;
		binary_node<T> *left, *right;
		binary_node(T value) : value(value), left(NULL), right(NULL) { }

	};

	/**********************************************
	 * class inorder_iterator <T>
	 * Iterator for inorder traversal of binary tree.
	 * We've written this for you, and you shouldn't need to change
	 * anything here.
	 **********************************************/
	template <typename T>
	class inorder_iterator {
		private:
			// A stack of all the ancestors of a node (needed because we don't have parent pointers).
			std::stack<binary_node<T> *> path;
		public:
			// default constructor
			inorder_iterator() : path() { }
			// nondefault constructor
			inorder_iterator(binary_node<T> *node) : path() {
				// Start at the leftmost node
	      			while (node) {
					path.push(node);
					node = node->left;
				}
			}

			// equality operator
			bool operator== (const inorder_iterator &other) const {
				if (this->path.empty() && other.path.empty()) return true;
				if (!this->path.empty() && !other.path.empty() && 
					(this->path.top() == other.path.top())) return true;
				return false;
			}

			bool operator!= (const inorder_iterator &other) const { 
				return !(*this == other); 
			}

			//prefix increment operator
			inorder_iterator& operator++ () {
				binary_node<T> *node = path.top();
				if (node->right) {
				// If there is a right child, move down to the leftmost descendant of the right child.
					node = node->right;
					while (node) {
						path.push(node);
						node = node->left;
					}
				} else {
				// Otherwise, move up to the first node whose left child is on the path (if any)
					binary_node<T> *child;
					do {
						child = node;
						path.pop();
						if (path.empty()) break;
						node = path.top();
					} while (child == node->right);
				}
				return *this;
			}

			T& operator*  () { return path.top()->value; }
		
			T* operator-> () { return &path.top()->value; }
	};
	  
	/**********************************************
	 * class map <Key, Value>
	 * Partial reimplementation of std::map.
	 **********************************************/
	template <typename Key, typename Value>
	class map {

		//typedefs
		typedef std::pair<Key, Value> key_value;
		typedef inorder_iterator<key_value> iterator;

		public:
			/*********
			 * map()
			 * constructor for map, initialize with 0 nodes in the map
			 *********/
			map() : root(NULL) { }

			/*********
			 * ~map()
			 * destructor for map, calls map_clear to clean up memory allocations
			 *********/
			~map() { map_clear(root); }

			/*********
			 * operator[]()
			 * Look up and possibly insert x into map.
			 * Postcondition: x belongs to map, and (a reference to) the
			 *   corresponding value is returned.
			 *********/
			Value& operator[] (const Key& x) {
				// call recursive function findOrInsertKey, starting the search at the root
				return findOrInsertKey(root, x);
			}

			/********
			 * map_clear()
			 * Clearing the map recursively, freeing the memory that was allocated for each node
			 ********/
			void map_clear(binary_node<key_value> *subRoot) {
				if (subRoot == NULL) return;

				map_clear(subRoot->left);
				map_clear(subRoot->right);
				delete subRoot;
			}

			/********
			 * begin()
			 * returns an iterator pointing to the root of the map
			 ********/
			iterator begin() { return inorder_iterator<key_value>(root); }

			/********
			 * end()
			 * returns an iterator with the default value, indicates the end of the map traversal
			 ********/
			iterator end() { return iterator(); }


		private:
			//pointer to root of the binary tree that stores the data in the map
			binary_node<key_value> *root;	

			/********
			 * findOrInsertKey()
			 * helper function for inserting our new key in the tree
			 * Precondition: the key is not already in the tree
			 * Postcondition: a new key_value node will be added to the tree, and the value will be initialized
			 *	using the default constructor, Value()
			 ********/ 
			Value& findOrInsertKey(binary_node<key_value>*&subRoot, const Key& k) {
				//base case, if we have reached a leaf and haven't found then key yet, then it is not yet in the map			
				if (subRoot == NULL) {
					key_value nodeData(k, Value());	// this is the new key value pair that will be inserted here
					subRoot = new binary_node<key_value>(nodeData);
					return ((subRoot->value).second);
				}
				//another base case -- if we find the key, then we can return the value
				if (k == (subRoot->value).first)
					return ((subRoot->value).second);
				
				//if the key is less than the key at the root, then go to the left child
				if (k < (subRoot->value).first)
					return findOrInsertKey(subRoot->left, k);

				//otherwise, the key is greater than the key at the root, so go to the right child
				return findOrInsertKey(subRoot->right, k);	
			}
			
	};

}

#endif
