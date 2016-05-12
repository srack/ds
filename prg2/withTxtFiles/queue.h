/* Samantha Rack
 * CSE 30331
 * Program 2
 * queue.h
 */


#ifndef ND_QUEUE_H
#define ND_QUEUE_H

#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;	//for vector

namespace fightingirish {

	/**********************************************
	 * class priority_queue <T>
	 * Implementation of a priority_queue.
	 * This queue gives priority to the maximum elements.
	 **********************************************/
	template <typename T>
	class priority_queue {

		public:

			/*********
			 * priority_queue()
			 * Constructor calls the default constructor for a std::vector object that will hold the data in the nodes.
			 * Postcondition: Priority queue is empty.
			 *********/
			priority_queue() : data() { }

			/*********
			 * priority_queue()
			 * Constructor initializes the priority queue with elements from given range.
			 * Precondition: first and last are iterators of a collection of T.
			 * Postcondition: The priority queue contains all and only
			 *   elements in [first, last).
			 * Note: This constructor should run in time O(n), not O(n log n).
			 * In other words, do not simply call push() n times!
			 *********/
			template <typename Iterator>
			priority_queue(Iterator first, Iterator last) {

				//put all elements into the heap first				
				Iterator it;
				for (it = first; it != last; ++it) {
					data.push_back(*it);
				}
				
				/* NOW THE ELEMENTS NEED TO BUBBLE DOWN, starting from the bottom */
				// find node with the highest index that has at least one child
				// every node at an index less than this will have child(ren)
				int i = 0;
				
				int lastParent = (data.size() - 2)/2;
					
				//start with prev, and use reheapification down with all of the nodes up to the root
				for (i = lastParent; i >= 0; --i) {
					reheapificationDown(i);
				}

			}

			/*********
			 * ~priority_queue()
			 * Destructor calls clear_queue() to delete the nodes of the list.
			 *********/
			~priority_queue() {
				data.clear();
			}

			/*********
			 * push()
			 * Pushes an element onto the priority queue
			 * Postcondition: The element x is added to the priority queue.
			 *********/
			void push(const T& x) {
				//start by pushing x onto the end of the vector
				data.push_back(x); 

				// REHEAPIFICATION UPWARDS
				// get the initial location of the new element
				int x_index = data.size() - 1;
				// get the index of the first parent of this element
				int x_parent = findParent(x_index);
				
				// loop until find correct position of this new element
				// NOTE: the loop can also exit if x is less than its parent -- 
				// 	not just if x_parent == -1 (ie. x is root)
				while (x_parent != -1) { 
					// if x is greater than its parent
					if (data[x_index] > data[x_parent]) {
						//swap them
						swapDataElements(x_index, x_parent);
						//update x's index
						x_index = x_parent;
						//update x's parent's index
						x_parent = findParent(x_index);
					}
					// loop will also exit is x is less than its parent
					else break;
				}
			}

			/*********
			 * pop()
			 * Pops the maximum element from the priority queue
			 * Precondition: The priority queue is not empty
			 * Postcondition: The maximum element is removed from the priority queue.
			 *********/
			void pop() {
				assert(!empty());
				// move the last element in the queue to the front
				// **for clarity in comments and code I will call this element that 
				// 	was last in the priority queue x for the rest of this 
				// 	implementation**
				data[0] = data.back();
				//pop this element off, so it is not repeated
				data.pop_back();

				//if this was the only element in the queue, then return
				if (empty()) return;

				// REHEAPIFICATION DOWNWARDS
				reheapificationDown(0);

			}

			/*********
			 * top()
			 * Returns the maximum element in the priority queue.
			 * Precondition: The priority queue is not empty.
			 * Postcondition: The maximum element is returned.
			 *********/
			const T& top() const {
				assert(!empty());				
				return data[0];	
			}

			/*********
			 * empty()
			 * Check whether the priority queue is empty.
			 * Precondition: None.
			 * Postcondition: Returns true if and only if the priority queue
			 *	is empty.
			 *********/		
			bool empty() const {
				return (data.size() == 0);
			}
		
		private:
			vector<T> data;

			/*********
 			 * swapDataElements()
 			 * Helper function for swapping two elements of data
 			 * Precondition: i0 and i1 are valid indicies of vector 'data'
 			 * Postcondition: the values in i0 and i1 will be swapped
			 *********/
			void swapDataElements(int i0, int i1){
				assert( (i0 >= 0 && i0 < data.size()) && (i1 >= 0 && i1 < data.size()) );
				//return if they are the same element
				if (i0 == i1) return;
				T temp = data[i0];
				data[i0] = data[i1];
				data[i1] = temp;
			}

			/*********
			 * findParent()
			 * Helper function that returns the index of the parent of the
			 *	data at childI (child index), useful for heapification.
			 * Precondition: childI is a valid index of vector 'data'
			 * Postcondition: findParent returns the index of parent of childI.
			 * 	If the data at childI does not have a parent, findParent()
			 * 	returns -1.
			 *********/
			int findParent(int childI) {
				assert(childI >= 0 && childI < data.size());
				if (childI == 0) return -1;	//for root element, no parent
				return (childI - 1)/2;	//using integer division, takes the floor of this
			}

			/*********
			 * findLchild()
			 * Helper function that returns the index of the left child of the
			 * 	data at pI (parent index).
			 * Precondition: pI is a valid index of vector 'data'
			 * Postconiditon: findLchild() returns the index of the left child of
			 * 	pI, if one exists. If pI has no left child, findLchild() returns
			 * 	-1.
			 *********/
			int findLchild(int pI) {
				assert(pI >= 0 && pI < data.size());
				int index = 2*pI + 1;
				return (index < data.size() ? index : -1);
			}

			/*********
			 * findRchild()
			 * Same description and pre-/postconditions as findLchild(), but 
			 * 	for the right child of the data of pI.
			 *********/
			int findRchild(int pI) {
				assert(pI >= 0 && pI < data.size());
				int index= 2*pI + 2;
				return (index < data.size() ? index : -1);
			}

			/*********
			 * reheapificationDown()
			 * Helper function that reheapifies downward the element at 'index' in the vector
			 * Used in both pop and the constructor running in O(n) time
			 * Precondition: Index is a valid index of vector 'data'
			 * Postcondition: The node initially at index 'index' in vector 'data' is in a 
			 * 	location where it is greater than both (or one if it only has one) of its
			 * 	children
			 */
			void reheapificationDown(int index) {
				int x_index = index;	// location of x at beginning of reheapification
				//intial indices of x's children
				int x_Lchild = findLchild(x_index);
				int x_Rchild = findRchild(x_index);

				// exit when x has no more children
				// NOTE: this loop can also exit if x is greater than both of its children
				//	this is done via a break
				while (x_Lchild != -1 || x_Rchild != -1) {
					int maxChild;
					if (x_Lchild == -1) maxChild = x_Rchild;
					else if (x_Rchild == -1) maxChild = x_Lchild;
					else {
						// assume child with max value is left
						// maxChild has the index of the child with the greatest value
						maxChild = x_Lchild;
						//then update if this is incorrect
						if (data[x_Lchild] < data[x_Rchild]) maxChild = x_Rchild;
					}
					// if x is smaller than one of its children
					if (data[maxChild] > data[x_index]) {
						//swap with the child with the greatest value
						swapDataElements(x_index, maxChild);
						//update x's index
						x_index = maxChild;
						//update x's children's indices
						x_Lchild = findLchild(x_index);
						x_Rchild = findRchild(x_index);
					}
					// the loop also terminates if x is greater than both of its children
					else break;

				}
			}

	};

}

#endif
