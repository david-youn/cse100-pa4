#ifndef EDGE_HPP
#define EDGE_HPP

#include <math.h>
#include <string>
#include <vector>
#include "Vertex.hpp"

using namespace std;

class Vertex;

/* This class defines a directed edge from source vertex to target vertex in the
 * map graph */
class Edge {
  public:
    Vertex* source;
    Vertex* target;
    float weight;  // the Euclidean distance between source and target vertices

    // used in MST
    bool used = false;

    /* The constructor that creates a new edge */
    Edge(Vertex* source, Vertex* target, float weight)
        : source(source), target(target), weight(weight) {}
};

struct EdgeComp {
    /**
     * overrides comparator taking in two edges and gives higher priority to
     * smaller weight
     */
    bool operator()(Edge* lhs, Edge* rhs) const {
        return lhs->weight > rhs->weight;
    }
};

#endif  // EDGE_HPP