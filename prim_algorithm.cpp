#include "stdafx.h"
#include<vector>
#include<iostream>
#include<set>

using namespace std;

struct Edge {
	char from;
	char to;
	int weight;
	Edge(char f, char t, int w) : from{ f }, to{ t }, weight{ w } {}
	Edge() {}
};

using edges_t = vector<Edge>;
using vertices_t = set<char>;
using graph_t = pair<vertices_t, edges_t>;

graph_t prim(graph_t &graph, char start) {
	edges_t new_edges = edges_t();
	vertices_t new_vertices = vertices_t();
	edges_t edges = graph.second;
	vertices_t vertices = graph.first;
	new_vertices.insert(start);
	for (Edge edge : graph.second) {
		edges.push_back(*(new Edge(edge.to, edge.from, edge.weight)));
	}
	while (new_vertices.size() < vertices.size()) {
		auto min = INFINITY;
		Edge minEdge;
		for (char v_i: vertices) {
			if (new_vertices.count(v_i) != 0) {
				for (char v_j : vertices) {
					if (new_vertices.count(v_j) == 0) {
						for (Edge e : edges) {
							if (e.from == v_i && e.to == v_j && e.weight < min) {
								min = e.weight;
								minEdge = e;
								break;
							}
						}
					}
				}
			}
		}
		new_edges.push_back(minEdge);
		start = minEdge.to;
		new_vertices.insert(start);
	}
	graph_t mst = make_pair(new_vertices, new_edges);
	return mst;
}



int main(void) {
    vertices_t vertices;
    edges_t edges;
 
    vertices.insert('A');   vertices.insert('B');
    vertices.insert('C');   vertices.insert('D');
    vertices.insert('E');   vertices.insert('F');
    vertices.insert('G');   vertices.insert('H');
    vertices.insert('I');   vertices.insert('J');
    vertices.insert('K');   vertices.insert('L');
    vertices.insert('M');   vertices.insert('N');
    vertices.insert('O');   vertices.insert('P');
    vertices.insert('R');   vertices.insert('S');
    vertices.insert('T');   vertices.insert('U');
    vertices.insert('V');   vertices.insert('W');
    vertices.insert('X');   vertices.insert('Y');
 
    edges.push_back(*(new Edge('A', 'B', 2)));
    edges.push_back(*(new Edge('A', 'C', 4)));
    edges.push_back(*(new Edge('B', 'C', 5)));
    edges.push_back(*(new Edge('B', 'D', 2)));
    edges.push_back(*(new Edge('B', 'E', 7)));
    edges.push_back(*(new Edge('C', 'D', 1)));
    edges.push_back(*(new Edge('C', 'H', 3)));
    edges.push_back(*(new Edge('C', 'G', 8)));
    edges.push_back(*(new Edge('D', 'H', 2)));
    edges.push_back(*(new Edge('D', 'G', 7)));
    edges.push_back(*(new Edge('E', 'F', 8)));
    edges.push_back(*(new Edge('E', 'H', 1)));
    edges.push_back(*(new Edge('F', 'J', 2)));
    edges.push_back(*(new Edge('F', 'I', 4)));
    edges.push_back(*(new Edge('F', 'N', 1)));
    edges.push_back(*(new Edge('G', 'H', 4)));
    edges.push_back(*(new Edge('G', 'L', 3)));
    edges.push_back(*(new Edge('G', 'K', 7)));
    edges.push_back(*(new Edge('H', 'I', 3)));
    edges.push_back(*(new Edge('H', 'M', 2)));
    edges.push_back(*(new Edge('H', 'L', 7)));
    edges.push_back(*(new Edge('I', 'N', 6)));
    edges.push_back(*(new Edge('I', 'M', 2)));
    edges.push_back(*(new Edge('J', 'O', 5)));
    edges.push_back(*(new Edge('K', 'P', 14)));
    edges.push_back(*(new Edge('L', 'T', 8)));
    edges.push_back(*(new Edge('L', 'P', 7)));
    edges.push_back(*(new Edge('M', 'N', 9)));
    edges.push_back(*(new Edge('M', 'S', 4)));
    edges.push_back(*(new Edge('M', 'R', 2)));
    edges.push_back(*(new Edge('N', 'O', 9)));
    edges.push_back(*(new Edge('N', 'V', 10)));
    edges.push_back(*(new Edge('N', 'R', 1)));
    edges.push_back(*(new Edge('O', 'V', 3)));
    edges.push_back(*(new Edge('R', 'U', 6)));
    edges.push_back(*(new Edge('R', 'T', 4)));
    edges.push_back(*(new Edge('S', 'V', 2)));
    edges.push_back(*(new Edge('U', 'V', 11)));
    edges.push_back(*(new Edge('U', 'X', 5)));
    edges.push_back(*(new Edge('V', 'W', 4)));
    edges.push_back(*(new Edge('V', 'Y', 8)));
    edges.push_back(*(new Edge('V', 'X', 6)));
    edges.push_back(*(new Edge('W', 'Y', 9)));
 
 
    graph_t graph = make_pair(vertices, edges);
    graph_t mstGraph = prim(graph,'A');
 
    cout << "vertices: " << endl;
    for(auto i : mstGraph.first){
        cout << i << " ";
    }
 
    cout << "edges: " << endl;
    for(auto i : mstGraph.second){
        cout << i.from << " "<< i.to << " "<< i.weight << endl;
    }
    cout << "its over";
    return 0;
}