/* Samantha Rack
 * CSE 30331 Program 1
 * list.h
 * This file contains the interface for a templated List class, in the 
 * fightingirish namespace. The List is implemented to be the underlying
 * data structure used for the implementation of the templated stack class.
 */

#ifndef LIST_H
#define LIST_H

#include "node.h"

namespace fightingirish {

	template <class T>
	class List {
		public:
			//constructor
			List();
			//destructor -- calls clear to free all allocated memory
			~List();			

			bool is_empty() const;
			void insert_node(Node<T> *, T);
			void insert_head(T);

			void delete_head();
			void delete_node(Node<T> *);
			void clear();

			T get_value(Node<T> *) const;
			T get_head_value() const;

		private:
			Node<T> *head_ptr;
	};

	#include "list.template"
}

#endif
