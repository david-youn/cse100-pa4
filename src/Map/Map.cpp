
#include "Map.hpp"
#include <iostream>
#include <queue>
#include <utility>
#include "limits.h"

using namespace std;

/* TODO */
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

/* TODO */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, VertexComp>
        pq;
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

/* TODO */
void Map::findMST(vector<Edge*>& MST) {}

/* TODO */
void Map::crucialRoads(vector<Edge*>& roads) {}

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
