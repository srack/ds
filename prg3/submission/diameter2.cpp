/* Samantha Rack
 * CSE 30331
 * Program 3
 * dijkstra2.cpp
 * This file contains the implementation for the second working version of 
 * Dijkstra's algorithm.  This implementation ...
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

	vector<int> distance(n, n); // a distance of n is like infinity
	distance[u] = 0;

	vector<bool> visited(n);

	// this implementation uses a set (RB tree) to store the unvisited vertices
	set<pair<int, int> > unvisited;

	// add all vertices to the set, because we are using a set the distance as
	//	it is can be added as the value (can get the minimum just as easily
	//	as the maximum)
	for (int i=0; i<n; i++)
		unvisited.insert(make_pair(distance[i], i));

	while (unvisited.size() > 0) {
		// get the next shortest distance vertex
		u = (*(unvisited.begin())).second;
		// and remove it
		unvisited.erase(unvisited.begin());

		pair<neighbor_iterator, neighbor_iterator> p = adjacent_vertices(u, g);
		for (neighbor_iterator it = p.first; it != p.second; ++it) {
			int v = *it;
			// if v is not yet visited, update distance if necessary
			if (!visited[v]) {
				// only update the set if the distance changes!!			
				if (distance[u] + 1 < distance[v]) {
					// need to make an equivalent pair of the previous data for 
					// 	this vertex so it can be removed and the new one 
					//	can be added to the set
					pair<int , int> searchParam = make_pair(distance[v], v);
					// now remove the node that matches this
					unvisited.erase(searchParam);
					// update the distance
					distance[v] = distance[u] + 1;
					// insert the new updated distance, vertex label pair
					unvisited.insert(make_pair(distance[v], v));
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
