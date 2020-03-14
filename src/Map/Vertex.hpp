#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

using namespace std;

class Edge;

/* This class defines a vertex in map graph. Each vertex has a name and x, y
 * coordinates in the map */
class Vertex {
  public:
    const string name;
    float x;
    float y;
    vector<Edge*> outEdges;  // the adjacency list of this vertex that contains
                             // all outgoing edges

    // TODO: you may add more member variables here
    // referenced from Stepik textbook used for Dijkstra's algorithm
    int dist;
    Vertex* prev;
    bool done;

    // used for MST
    Vertex* parent;
    int treeSize;

    /* The constructor that creates a new vertex */
    Vertex(const string& name, float x, float y) : name(name), x(x), y(y) {}
};

struct VertexComp {
    /**
     * overrides comparator that takes in two vertices and weights returns
     * higher priority which is smaller weight
     */
    bool operator()(pair<int, Vertex*> lhs, pair<int, Vertex*> rhs) const {
        return lhs.first > rhs.first;
    }
};

#endif  // VERTEX_HPP