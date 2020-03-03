/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* TODO */
ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    ifstream infile(filename);
    bool readHeader = false;

    cout << "read: " << filename << endl;
    while (infile) {
        string s;
        cout << "s: " << s << endl;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        cout << "record: " << record[0] << endl;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        cout << "actor: " << actor << endl;
        cout << "title: " << title << endl;
        cout << "year: " << year << endl;
        // TODO: we have an actor/movie relationship to build the graph
        // create actor and movie objects first
        Actor* a = new Actor(actor);
        Movie* m = new Movie(title, year);
        a->movies.push_back(m);
        m->actors.push_back(a);

        // adding to the hash tables
        Actors.insert({a->name, m});
        Movies.insert({m->fullT, a});
    }

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO */
ActorGraph::~ActorGraph() {}
