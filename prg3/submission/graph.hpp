/* Samantha Rack
 * CSE 30331
 * Program 3
 * graph.hpp
 * This file defines the interface for the undirected_graph class and for 
 * non-member functions that are used to manipulate objects of this class.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>
#include <set>
#include <vector>
#include <algorithm>

///////////////////////////////////
// typedef for neighbor_iterator //
///////////////////////////////////
typedef std::set<int>::iterator neighbor_iterator;

/////////////////////////////
// CLASS: undirected_graph //
/////////////////////////////
class undirected_graph {
	public:
		undirected_graph();
		inline int size() const { return nodeEdges.size(); }
		void insertNextVertex();
		void addEdge(int x, int y);
		std::pair<neighbor_iterator, neighbor_iterator> adjacent_vertices(int x) const;

	private:
		// the nodes are solely identified by their index in the vector (ie. no other labels)
		std::vector<std::set<int> > nodeEdges;

};


///////////////////////////////
// GRAPH FUNCTION PROTOTYPES //
///////////////////////////////
void add_edge(int u, int v, undirected_graph &g);
int num_vertices(const undirected_graph &g);
std::pair<neighbor_iterator, neighbor_iterator> adjacent_vertices(int u, const undirected_graph &g);


#endif
