#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Edge.hpp"

using namespace std;

class Map {
  private:
    // vector storing vertices in the map: id of each vertex = index in vector
    vector<Vertex*> vertices;

    // Map: name of vertex -> id of vertex = index storing vertex ptr
    unordered_map<string, unsigned int> vertexId;

    // Directed edge in vector represents an undirected edge used in MST
    vector<Edge*> undirectedEdges;

    /*
     * Add a vertex with name and x, y coordinates to the map graph. Returns
     * false if the name already existed in the map graph, and true otherwise
     */
    bool addVertex(const string& name, float x, float y);

    /*
     * Add an undirected edge between vertices with names "name1" and "name2".
     * Returns false if either name is not in the map graph.
     */
    bool addEdge(const string& name1, const string& name2);

  public:
    /**
     * Default constructor for the map object
     */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

    /**
     * Finds the shortest weighted path from vertex "from" to "to" in the map
     * using Dijkstra's algorithm.
     * Paramter(s): from - the string of the first vertex in the connection to
     * find to - the string of the second vertex in the connection to find
     *              shortestPath - the string containing the connection between
     *                             the vertices
     * Return: none
     */
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

    /**
     * Method that finds all the undirected edges in the minimum spanning tree
     * of the map graph. This method uses the helper functions Union() in order
     * to implement Kruskal's algorithm. Parameter(s): MST - the vector that
     * should be filled with all the edges in the minimum spanning tree Return:
     * none
     */
    void findMST(vector<Edge*>& MST);

    /**
     * Helper method to MST that connectes two subtrees or nodes using the
     * sentinels of both as shown in Kruskal's algorithm.
     * Parameter(s): edge - the edge between two nodes to compare
     * Return: none
     */
    void Union(Edge* edge);

    /**
     * Helper method for Union that finds the sentinel for a given vertex.
     * Parameter(s): v - a pointer to the vertex to find
     * Return: a vertex pointer returning the sentinel of the subtree that the
     * node is currently in.
     */
    Vertex* Find(Vertex* v);

    /**
     * Finds all the edges representing crucial roads in the map graph using
     * a BFS algorithm.
     * Parameter(s): roads - a vector that should be filled with all the edges
     *                       representing crucial roads
     * Return: none
     */
    void crucialRoads(vector<Edge*>& roads);

    /**
     * Helper method for crucialRoads that returns whether or not the edge is a
     * crucialRoad by finding if a different path exists between the two
     * vertices the edge connects. Parameter(s): e - the edge to decide Return:
     * boolean representing whether or not the edge is a crucial road
     */
    bool crucialBFS(Edge* e);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP