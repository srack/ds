/* Samantha Rack
 * CSE 30331
 * Program 3
 * dijkstra1.cpp
 * This file contains the implementation for the first working version of
 * Dijkstra's algorithm.  This implementation allows multiple copies of a 
 * given vertex in the priority queue, unvisited, at a given time. In order
 * to account for duplicate distances in unvisited, the program checks if 
 * the vertex is already in visited when it is popped off the queue.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#include "graph.hpp"
#include "pqueue.hpp"


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
void read_graph (ifstream &infile, undirected_graph &g);
int dijkstra(const undirected_graph &g, int u);
int diameter_dijkstra(const undirected_graph &g);


/////////////////////////
//        MAIN         //
/////////////////////////
int main (int argc, char *argv[]) {
	if (argc < 2) {
		cerr << "usage: diameter <filename>" << endl;
		exit(1);
	}

	ifstream infile (argv[1]);
	undirected_graph g;
	read_graph (infile, g);

	int d = diameter_dijkstra(g);
	cout << d << endl;
}


//////////////////////////
// FUNCTION DEFINITIONS //
//////////////////////////

/* Function Name:	read_graph
 * Parameters:		infile -- input file with graph data
 *			g -- graph in which the data will be stored
 * Preconditions:	infile is a file whose lines have the following format: u \t v \n,
 *			where u and v are 0-based node ids.
 *			g is an empty graph
 * Postcondition:	g is the graph read from infile
 */
void read_graph (ifstream &infile, undirected_graph &g) {
	string line;
	while (getline (infile, line)) {
		int u, v;
		istringstream ss (line);
		ss >> u >> v;
		add_edge(u, v, g);
	}
}

/* Function Name:	dijkstra
 * Parameters:		g -- graph on which dijkstra's algorithm will be run
 * 			u -- node in graph g
 * Preconditions:	g is an undirected graph
 * 			u is a node of g
 * Postcondition:	Computes the shortest path from u to every node v in g.
 *			The return value is the maximum length of all such paths.
 */
int dijkstra(const undirected_graph &g, int u) {
	int n = num_vertices(g);

	// a distance of n is like infinity
	vector<int> distance(n, n); 

	// u is distance 0 away from itself (empty path)
	distance[u] = 0;

	// vector bool to keep track of which elements have been visited,
	//	all vertices are initialized to false
	vector<bool> visited(n);

	// a priority queue to keep track of the unvisited nodes
	fightingirish::priority_queue<pair<int, int> > unvisited;
	for (int i=0; i<n; i++)
		// use negative to use minimum distance for priority 
		unvisited.push(make_pair(-distance[i], i));	

	// while there are still unvisited elements
	while (!unvisited.empty()) {

		// u is label of the vertex to be visited next
		u = unvisited.top().second;
		// pop and reheapify the rest of the queue
		unvisited.pop();

		// here is where we check to see if this vertex has duplicates in the priority queue
		if (visited[u]) continue;

		// get iterators for the neighbors of this next shortest distance vertex
		pair<neighbor_iterator, neighbor_iterator> p = adjacent_vertices(u, g);
		// for each of the neighbors, if they are not yet visited, update the 
		//	distance if it can be reduced
		for (neighbor_iterator it = p.first; it != p.second; ++it) {
			// v is label of the neighbor vertex			
			int v = *it;
			// if v is not yet visited, update distance if necessary
			if (!visited[v]) {
				// only push a new version if the new distance is less				
				if (distance[u] + 1 < distance[v]) {
					distance[v] = distance[u] + 1;
					// push the updated distance into the priority queue
					// take care of duplicates as they are popped (see line 110)
					unvisited.push(make_pair(-distance[v], v));
				}
			}
		}

		visited[u] = true;
	}

	return *max_element(distance.begin(), distance.end());
}

/* Function Name:	diameter_dijkstra
 * Parameters:		g -- undirected graph
 * Postcondition:	Computes the shortest path of every node u to every node v. The
			return value is the diameter of g, that is the maximum length
			of all such paths.
 */
int diameter_dijkstra(const undirected_graph &g) {
	int n = num_vertices(g);
	int d = 0;
	for (int u=0; u<n; u++)
		d = max(d, dijkstra(g, u));
	return d;
}
