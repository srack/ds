/* Samantha Rack
 * CSE 30331
 * Program 3
 * graph.cpp
 * This file contains the implementation of the interface defined in graph.hpp.
 * It is includes member functions of the undirected_graph class, as well as
 * non-member functions that are used to manipulate an undirected_graph
 * object.
 */

#include "graph.hpp"

//////////////////////////////////
// Graph Class Member Functions //
//////////////////////////////////

/* Function Name:	undirected_graph
 * 			default constructor
 */
undirected_graph::undirected_graph() : nodeEdges() {
	//constructor does not need to do anything
}


/* Function Name:	insertNextVertex
 * Precondition:	none
 * Postcondition:	One additional vertex has been added to the graph object.
 */
void undirected_graph::insertNextVertex() { 
	std::set<int> temp;	
	nodeEdges.push_back(temp); 
}


/* Function Name:	addEdge
 * Parameters:		x, y -- indices of vertices in the graph object
 * Precondition:	x and y are valid vertices in the graph -- nonnegative 
 *			and less than the size of the graph
 * Postcondition:	An edge has been added between x and y in the undirected
 *			graph.
 */ 
void undirected_graph::addEdge(int x, int y) {
	// verify the precondition is met
	assert( x < size() && y < size() && x >= 0 && y >= 0);
	
	// undirected graph, so add edge from u to v and v to u			
	nodeEdges[x].insert(y);
	nodeEdges[y].insert(x);
}


/* Function Name:	adjacent_vertices
 * Parameter:		x -- index of vertex in graph object
 * Precondition:	x is a valid vertice in the graph -- nonnegative and less than the 
 *			size of the graph
 * Postcondition:	Returns a pair of neighbor_iterators that iterate over the
 * 			neighbors of x in g
 */
std::pair<neighbor_iterator, neighbor_iterator> undirected_graph::adjacent_vertices(int x) const {
	neighbor_iterator start, end;
	start = nodeEdges[x].begin();
	end = nodeEdges[x].end();
	return make_pair(start, end);
}



////////////////////////////////
// Graph Non-Member Functions //
////////////////////////////////

/* Function Name:	add_edge
 * Parameters:		u, v -- vertices either in the graph or to be added to the graph between which
 *				an edge will be added
 *			g -- undirected graph object to which an edge between u and v will be added
 * Precondition:	u and v are valid identifiers for nodes in the undirected graph, g, ie. u
 *			and v are greater than or equal to 0
 * Postcondition:	If u and/or v were not initially in the graph, then the vertices have been added,
 *			as well as any vertices smaller than them that have not yet been added. Additionally
 *			an edge between u and v has been added to g.
 */
void add_edge(int u, int v, undirected_graph &g) {
	// verify the precondition is met
	assert( u >= 0 && v >= 0);

	// find the max of u or v
	int maxIndex = (u > v ? u : v);
	// if either u or v is not yet a vertex in the graph, add it and any vertices with a lower index not yet added
	int i;		
	for (i = g.size() - 1; i < maxIndex; ++i) {
		g.insertNextVertex();
	}

	// add the edge
	g.addEdge(u, v);
}

/* Function Name:	num_vertices
 * Parameters:		g -- undirected graph object of interest
 * Precondition:	none
 * Postcondition:	Function returns the total number of vertices in the undirected graph, g
 */
int num_vertices(const undirected_graph &g) {
	return g.size();
}

/* Function Name:	adjacent_vertices
 * Parameters:		u -- vertex in an undirected graph, g -- undirected graph
 * Precondition:	u must be a valid vertex in g
 * Postcondition:	Returns a pair of iterators that iterate over the neighbors of node, u, in g
 */
std::pair<neighbor_iterator, neighbor_iterator> adjacent_vertices(int u, const undirected_graph &g) {
	// verify precondition
	assert(u < g.size());

	// call the member function that performs this operation
	return g.adjacent_vertices(u);
}








