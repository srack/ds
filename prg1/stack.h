/* Samantha Rack
 * CSE 30331 Program 1
 * stack.h
 * This file contains the interface of the templated stack class.
 */

#ifndef ND_STACK_H
#define ND_STACK_H

#include <stdexcept>

// Uncomment *only one* of the following #defines...

// For a working stack class to understand how calc is supposed to work:
//#define USE_STD_STACK 1

// For the non-template skeleton defined in this file:
//#define USE_MY_STACK 1

// For the template class which you will write in this file:
#define USE_MY_STACK_TEMPLATE 1

#include "list.h"

namespace fightingirish {

	template <class T>
	class stack {
		public:
			stack();

			bool empty() const; 
			void push(T x);
			void pop();
			T top() const;

		private:
			List<T> list;	//underlying data structure used to implement the stack
					//head_ptr of the list (see list.h) will be the pointer to the top of the stack
					//push and pop will manipulate the head of the list (deleting or adding nodes there)
	};
	
	#include "stack.template"
}

#endif
