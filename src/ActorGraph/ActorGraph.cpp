/**
 * Name(s): David Youn - A15452585
 *          Jonathan Yun - A15431969
 *
 * Email(s): dayoun@ucsd.edu
 *           j3yun@ucsd.edu
 *
 * Source(s): Stepik textbook
 *
 * This file contains the method implementations for functions used by the
 * ActorGraph object. This file is used in conjunction with the file
 * ActorGraph.hpp in order to implement the methods declared.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

/**
 * Default constructor for the ActorGraph object
 */
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

/**
 * Method that finds the unweighted shortest path from one Actor to another
 * through movie connections and Breadth First Search.
 * Parameter(s): fromActor - the name of the first actor to find the connection
 *               toActor - the name of the second actor to find the connection
 *                         between
 *               shortestPath - the string that contains the required format
 *                              showing the shortest path between two actors
 * Return: none
 */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    // vector to hold all actors and movies added to the pq
    vector<Movie*> ms;
    vector<Actor*> as;

    // queue that holds all the actors to find
    queue<Actor*> toExplore;
    // attemps to find the actor fromActor in the Actor hashfunction
    try {
        Actor* toFind = Actors.at(fromActor);
        toExplore.push(toFind);

        // if the actor doesn't exist in the database, return
    } catch (exception& e) {
        return;
    }

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
                    // resets all variables for every actor visited
                    for (int a = 0; a < as.size(); a++) {
                        Actor* myActor = as.at(a);
                        myActor->visited = false;
                        myActor->prevMovie = nullptr;
                    }
                    // resets all variables for every movie visited
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
    // resets all variables for every actor visited
    for (int a = 0; a < as.size(); a++) {
        Actor* myActor = as.at(a);
        myActor->visited = false;
        myActor->prevMovie = nullptr;
    }
    // resets all variables for every movie visited
    for (int m = 0; m < ms.size(); m++) {
        Movie* myMovie = ms.at(m);
        myMovie->visited = false;
        myMovie->prevActor = nullptr;
    }
}

/**
 * Tester method that manually inserts actors and movies into the corresponding
 * hashfuncitons to test the method BFS().
 * Parameter(s): a, b, c, d, e - actor objects to insert into the Actors
 *                               hashfunction
 *               m1, m2, m3, m4, m5 - movie objects to insert into the Movies
 *                                    hashfunction
 * Return: none
 */
void ActorGraph::smallTest(Actor* a, Actor* b, Actor* c, Actor* d, Actor* e,
                           Movie* m1, Movie* m2, Movie* m3, Movie* m4,
                           Movie* m5) {
    Actors.insert({a->name, a});
    Actors.insert({b->name, b});
    Actors.insert({c->name, c});
    Actors.insert({d->name, d});
    Actors.insert({e->name, e});

    Movies.insert({m1->fullT, m1});
    Movies.insert({m2->fullT, m2});
    Movies.insert({m3->fullT, m3});
    Movies.insert({m4->fullT, m4});
    Movies.insert({m5->fullT, m5});
}

/**
 *  Extra credit method we did not implement
 */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/**
 * Default default constructor that frees all allocated memory
 */
ActorGraph::~ActorGraph() {
    for (auto m = Movies.begin(); m != Movies.end(); m++) {
        delete (Movies.at(m->first));
    }
    for (auto a = Actors.begin(); a != Actors.end(); a++) {
        delete (Actors.at(a->first));
    }
}