/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
//#include "Actor.hpp"
//#include "Movie.hpp"

typedef struct Movie Movie;
typedef struct Actor Actor;

using namespace std;

struct Movie {
    string title;
    int year;
    string fullT;
    vector<Actor*> actors;

    Movie(string t, int y) {
        title = t;
        year = y;
        fullT = title + to_string(year);
    }

    bool operator==(const Movie& m) const {
        return title == m.title && year == m.year;
    }
};

struct Actor {
    string name;
    vector<Movie*> movies;
    Actor(string n) { name = n; }

    bool operator==(const Actor& a) const { return name == a.name; }
};

class MovieHF {
  public:
    // hash function to be used
    string operator()(const Movie& movie) const { return movie.fullT; }
};

class ActorHF {
  public:
    // hash function to be used
    string operator()(const Actor& actor) const { return actor.name; }
};

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // creating user-defined hash functions for Movies and Actors
    // unordered_map<Movie, Actor*, MovieHF> Movies;
    // unordered_map<Actor, Movie*, ActorHF> Actors;
    unordered_map<string, Actor*> Movies;
    unordered_map<string, Movie*> Actors;

  public:
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraphFromFile(const char* filename);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    int getMoviesSize() { return Movies.size(); }
    int getActorsSize() { return Actors.size(); }

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
