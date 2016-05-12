#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#include "graph.hpp"

template <typename T>
void test_equal(const T& x, const T& y) {
  cout << x << " == " << y << ":\t";
  cout << (x == y ? "PASSED" : "FAILED") << endl;
}

template <typename T>
void test_range(const T& x, const T& ymin, const T& ymax) {
  cout << x << " in [" << ymin << ", " << ymax << "]:\t";
  cout << (x >= ymin && x <= ymax ? "PASSED" : "FAILED") << endl;
}

void read_graph (ifstream &infile, undirected_graph &g) {
  /*
    Precondition:
      infile is a file whose lines have the following format:
        u \t v \n
      where u and v are 0-based node ids.

      g is an empty graph.

    Postcondition:
      g is the graph read from infile.
   */
  string line;
  while (getline (infile, line)) {
    int u, v;
    istringstream ss (line);
    ss >> u >> v;
    add_edge(u, v, g);
  }
}

void test (int n) {
  undirected_graph g;
  int ne = 0;
  test_equal(static_cast<int>(num_vertices(g)), 0);
  for (int i=0; i<n; i++)
    for (int j=i+1; j<n; j++)
      if (i > 0 && j % i == 0) {
	add_edge(i, j, g);
	ne++;
      }
  test_range(static_cast<int>(num_vertices(g)), n-1, n);

  int ne_check = 0;
  bool pass = true;
  for (int i=0; i<n; i++) {
    pair<neighbor_iterator, neighbor_iterator> p = adjacent_vertices(i, g);
    for (neighbor_iterator it = p.first; it != p.second; ++it) {
      int j = *it;
      if (j > i && i > 0 && j % i != 0)
	pass = false;
      else if (i > j && j > 0 && i % j != 0)
	pass = false;
      ne_check++;
    }
  }
  test_equal(pass, true);
  test_equal(ne*2, ne_check);
}

int main (int argc, char *argv[]) {
  cout << "Small test" << endl;
  test(10);
  cout << "Large test" << endl;
  test(50000);
}
