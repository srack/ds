/* Samantha Rack
 * CSE 30331 Program 1
 * node.h
 * This file contains the interface of the Node class, used as the smaller
 * data elements of the List class.
 */

#ifndef NODE_H
#define NODE_H

namespace fightingirish {
	template <class T>
	class Node {
		public:
			//constructors
			Node(T _data, Node *_next = NULL) {
				next = _next;
				data = _data;
			}

			//data members
			Node *next;
			T data;
	};

}

#endif
