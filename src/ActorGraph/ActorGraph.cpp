/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
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

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
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

        // TODO: we have an actor/movie relationship to build the graph

        // check if actor and movie already exist or not
        Actor* a;
        Movie* m;
        // if not, create actor and movie objects first
        if (Actors.count(actor) == 0) {
            a = new Actor(actor);
            Actors.insert({a->name, a});
        } else {
            a = Actors.at(actor);
        }
        string key = title + "#@" + to_string(year);
        if (Movies.count(key) == 0) {
            m = new Movie(title, year);
            Movies.insert({m->fullT, m});
        } else {
            m = Movies.at(key);
        }

        a->movies.push_back(m);
        m->actors.push_back(a);
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
                     string& shortestPath) {
    // vector to hold all actors and movies added to the pq
    vector<Movie*> ms;
    vector<Actor*> as;

    cout << "shortestPath: " << shortestPath << endl;
    cout << "fromActor: " << fromActor << endl;
    queue<Actor*> toExplore;
    Actor* toFind = Actors.at(fromActor);
    cout << "toFind: " << toFind->name << endl;
    toExplore.push(toFind);
    cout << "toExplore size: " << toExplore.size() << endl;
    while (toExplore.size() != 0) {
        Actor* curr = toExplore.front();
        curr->visited = true;
        as.push_back(curr);
        toExplore.pop();
        Movie* currMovie;
        Actor* currActor;
        // goes through all the movies the actor is in
        for (int i = 0; i < curr->movies.size(); i++) {
            currMovie = curr->movies.at(i);
            if (currMovie->visited) {
                continue;
            }
            currMovie->prevActor = curr;
            currMovie->visited = true;
            ms.push_back(currMovie);

            // goes through all the actors in that movie
            for (int j = 0; j < currMovie->actors.size(); j++) {
                currActor = currMovie->actors.at(j);
                if (currActor->visited) {
                    continue;
                }
                currActor->prevMovie = currMovie;
                currActor->visited = true;
                as.push_back(currActor);
                if ((currActor->name).compare(toActor) == 0) {
                    // backtrack through all the previous nodes and return the
                    // string that is built
                    Actor* bActor = currActor;
                    shortestPath = "(" + bActor->name + ")";
                    while (bActor->prevMovie != nullptr) {
                        string MovieActor = "";
                        Movie* bMovie = bActor->prevMovie;
                        MovieActor = "--[" + bMovie->fullT + "]-->";
                        bActor = bMovie->prevActor;
                        MovieActor = "(" + bActor->name + ")" + MovieActor;
                        shortestPath = MovieActor + shortestPath;
                    }

                    // emptying the pq before returning the shortest path
                    while (toExplore.size() != 0) {
                        toExplore.pop();
                    }
                    for (int a = 0; a < as.size(); a++) {
                        Actor* myActor = as.at(a);
                        myActor->visited = false;
                        myActor->prevMovie = nullptr;
                    }
                    for (int m = 0; m < ms.size(); m++) {
                        Movie* myMovie = ms.at(m);
                        myMovie->visited = false;
                        myMovie->prevActor = nullptr;
                    }
                    return;
                } else {
                    toExplore.push(currActor);
                }
            }
        }
    }
}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO */
ActorGraph::~ActorGraph() {}
