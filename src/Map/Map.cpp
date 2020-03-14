
#include "Map.hpp"
#include <iostream>
#include <queue>
#include <utility>
#include "limits.h"

using namespace std;

/**
 * Default constructor for the map object
 */
Map::Map() {}

/* Build the map graph from vertex and edge files */
bool Map::buildMapFromFile(const string& vertexFileName,
                           const string& edgeFileName) {
    // add vertices first
    ifstream vertexFile(vertexFileName);
    while (vertexFile) {
        string s;
        if (!getline(vertexFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 3) continue;

        // add vertex defined in this line to the graph
        string name(data[0]);
        float x = stoi(data[1]);
        float y = stoi(data[2]);

        addVertex(name, x, y);
    }

    // then add edges
    ifstream edgeFile(edgeFileName);
    while (edgeFile) {
        string s;
        if (!getline(edgeFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 2) continue;

        // add edge defined in this line to the graph
        string name1(data[0]);
        string name2(data[1]);

        addEdge(name1, name2);
    }

    return true;
}

/*
 * Add a vertex with name and x, y coordinates to the map graph. Returns
 * false if the name already existed in the map graph, and true otherwise
 */
bool Map::addVertex(const string& name, float x, float y) {
    if (vertexId.count(name) > 0) return false;
    vertexId[name] = vertices.size();
    vertices.push_back(new Vertex(name, x, y));
    return true;
}

/*
 * Add an undirected edge between vertices with names "name1" and "name2".
 * Returns false if either name is not in the map graph.
 */
bool Map::addEdge(const string& name1, const string& name2) {
    if (vertexId.count(name1) == 0 || vertexId.count(name2) == 0) {
        return false;
    }
    unsigned int id1 = vertexId[name1];
    unsigned int id2 = vertexId[name2];
    Vertex* v1 = vertices[id1];
    Vertex* v2 = vertices[id2];
    float weight = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
    v1->outEdges.push_back(new Edge(v1, v2, weight));
    v2->outEdges.push_back(new Edge(v2, v1, weight));

    undirectedEdges.push_back(new Edge(v1, v2, weight));
    return true;
}

/**
 * Finds the shortest weighted path from vertex "from" to "to" in the map
 * using Dijkstra's algorithm.
 * Paramter(s): from - the string of the first vertex in the connection to find
 *              to - the string of the second vertex in the connection to find
 *              shortestPath - the string containing the connection between
 *                             the vertices
 * Return: none
 */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, VertexComp>
        pq;
    // iterates through all vertices and sets the variables used in Dijkstra's
    // algorithm to the default values
    for (int i = 0; i < vertices.size(); i++) {
        (vertices.at(i))->dist = INT_MAX;
        (vertices.at(i))->prev = nullptr;
        (vertices.at(i))->done = false;
    }

    // error catching if vertex doesn't exist
    try {
        Vertex* startV = vertices.at(vertexId.at(from));

        startV->dist = 0;
        pair<int, Vertex*> start = make_pair(0, startV);
        pq.push(start);

        Vertex* endV = vertices.at(vertexId.at(to));

    } catch (exception& e) {
        return;
    }

    // while priority queue is not empty
    while (pq.size() != 0) {
        Vertex* curr = pq.top().second;

        if ((curr->name).compare(to) == 0) {
            while (curr->prev != nullptr) {
                shortestPath.insert(shortestPath.begin(), curr);
                curr = curr->prev;
            }
            shortestPath.insert(shortestPath.begin(), curr);

            while (pq.size() != 0) {
                pq.pop();
            }
            return;
        }

        pq.pop();

        if (curr->done == false) {
            curr->done = true;

            // for every edge from curr
            for (int e = 0; e < curr->outEdges.size(); e++) {
                Edge* edge = curr->outEdges.at(e);
                Vertex* targ = edge->target;
                int totalDist = curr->dist + edge->weight;
                // if there is a smaller weighted path
                if (totalDist < targ->dist) {
                    targ->prev = curr;
                    targ->dist = totalDist;
                    pair<int, Vertex*> newPair = make_pair(totalDist, targ);
                    pq.push(newPair);
                }
            }
        }
    }
}

/**
 * Method that finds all the undirected edges in the minimum spanning tree of
 * the map graph. This method uses the helper functions Union() in order to
 * implement Kruskal's algorithm.
 * Parameter(s): MST - the vector that should be filled with all the edges
 *                     in the minimum spanning tree
 * Return: none
 */
void Map::findMST(vector<Edge*>& MST) {
    priority_queue<Edge*, vector<Edge*>, EdgeComp> edge_pq;

    // fills the priority queue with edges
    for (int i = 0; i < undirectedEdges.size(); i++) {
        edge_pq.push(undirectedEdges.at(i));

        // sets the parent of all to nullptr, creating a forest of single nodes
        undirectedEdges.at(i)->source->parent = nullptr;
        undirectedEdges.at(i)->source->treeSize = 1;
    }

    // iterates through all the undirected edges
    while (edge_pq.size() != 0) {
        Edge* curr = edge_pq.top();

        edge_pq.pop();
        Union(curr);
    }

    // goes through all the marked edges and fills the MST vector
    for (int e = 0; e < undirectedEdges.size(); e++) {
        if (undirectedEdges.at(e)->used == true) {
            undirectedEdges.at(e)->used = false;
            MST.push_back(undirectedEdges.at(e));
        }
    }
}

/**
 * Helper method to MST that connectes two subtrees or nodes using the
 * sentinels of both as shown in Kruskal's algorithm.
 * Parameter(s): edge - the edge between two nodes to compare
 * Return: none
 */
void Map::Union(Edge* edge) {
    // creates variables for the two vertices that the edge connects
    Vertex* v1 = edge->source;
    Vertex* v2 = edge->target;

    Vertex* v1_sentinel = Find(v1);
    Vertex* v2_sentinel = Find(v2);

    // if both nodes are in the same subtree, return
    if (v1_sentinel == v2_sentinel) {
        return;
        // if one node is greater than the other, connect the lesser subtree to
        // the greater one
    } else if (v1_sentinel->treeSize > v2_sentinel->treeSize) {
        v2_sentinel->parent = v1_sentinel;
        v1_sentinel->treeSize = v1_sentinel->treeSize + v2_sentinel->treeSize;
        edge->used = true;
    } else {
        v1_sentinel->parent = v2_sentinel;
        v2_sentinel->treeSize = v2_sentinel->treeSize + v1_sentinel->treeSize;
        edge->used = true;
    }
}

/**
 * Helper method for Union that finds the sentinel for a given vertex.
 * Parameter(s): v - a pointer to the vertex to find
 * Return: a vertex pointer returning the sentinel of the subtree that the node
 *         is currently in.
 */
Vertex* Map::Find(Vertex* v) {
    Vertex* sentinel = v;
    // finds the sentinel of the entire subtree
    while (sentinel->parent != nullptr) {
        sentinel = sentinel->parent;
    }
    // connects all nodes up the path directly to sentinel
    while (v->parent != nullptr && v->parent != sentinel) {
        Vertex* connect = v;
        v = v->parent;
        connect->parent = sentinel;
    }
    return sentinel;
}

/**
 * Finds all the edges representing crucial roads in the map graph using
 * a BFS algorithm.
 * Parameter(s): roads - a vector that should be filled with all the edges
 *                       representing crucial roads
 * Return: none
 */
void Map::crucialRoads(vector<Edge*>& roads) {
    // iterates through every edge in the map
    for (int i = 0; i < undirectedEdges.size(); i++) {
        // for each iteration, reset all vertices and their variables used
        // in the BFS search
        for (int a = 0; a < vertices.size(); a++) {
            vertices.at(a)->done = false;
        }
        // if the edge is a crucial road, add it to the roads vector
        if (crucialBFS(undirectedEdges.at(i))) {
            roads.push_back(undirectedEdges.at(i));
        }
    }
}

/**
 * Helper method for crucialRoads that returns whether or not the edge is a
 * crucialRoad by finding if a different path exists between the two vertices
 * the edge connects.
 * Parameter(s): e - the edge to decide
 * Return: boolean representing whether or not the edge is a crucial road
 */
bool Map::crucialBFS(Edge* e) {
    queue<Vertex*> vert;

    // creates variables for the two vertices the edge connects
    Vertex* source = e->source;
    Vertex* target = e->target;

    vert.push(source);
    // iterates through the tree using a BFS algorithm to check whether
    // a different path exists to the target node
    while (vert.size() != 0) {
        Vertex* curr = vert.front();
        curr->done = true;
        vert.pop();
        // iterates through the all edges the current vertex is connected to
        for (int i = 0; i < curr->outEdges.size(); i++) {
            Edge* currEdge = curr->outEdges.at(i);

            // if edge is the edge we are checking as the crucial road, move on
            if (currEdge->source == e->source &&
                currEdge->target == e->target) {
                continue;
            }

            Vertex* t = currEdge->target;

            // if there is a path to target, return false
            if (t == target) {
                return false;
            }

            // if t has already been visited before, continue
            if (t->done) {
                continue;
            }
            vert.push(t);
        }
    }
    return true;
}

/* Destructor of Map graph */
Map::~Map() {
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}