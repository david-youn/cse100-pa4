/**
 * Name(s): David Youn - A15452585
 *          Jonathan Yun - A15431969
 *
 * Email(s): dayoun@ucsd.edu
 *           j3yun@ucsd.edu
 *
 * Source(s): Stepik textbook
 *
 * This file contains all the method headers and structs used to create the
 * ActoGraph object. It is used in conjunction with the ActorGraph.cpp file
 * as it defines all method headers as well as defines the nodes of the graph
 * such as Movie and Actor.
 */
#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "limits.h"

typedef struct Movie Movie;
typedef struct Actor Actor;

using namespace std;

/**
 * Struct used to define a Movie used in ActorGraph as a connection
 * between actor nodes.
 */
struct Movie {
    // variables used by the Movie struct
    string title;
    int year;
    string fullT;
    vector<Actor*> actors;

    Actor* prevActor = nullptr;
    bool visited = false;

    /**
     * Constructor for Movie struct
     * Parameter(s): t - the title of the movie
     *               y - the year of the movie
     */
    Movie(string t, int y) {
        title = t;
        year = y;
        // creates the string that follows the required format when creating
        // the final string in the BFS method
        fullT = title + "#@" + to_string(year);
    }

    /**
     * Overrides comparator for Movie struct
     */
    bool operator==(const Movie& m) const {
        // in order for two Movie structs to be equal they must have same
        // title and year
        return title == m.title && year == m.year;
    }
};

/**
 * Struct used to define an Actor node used in ActorGraph.
 */
struct Actor {
    string name;
    Movie* prevMovie = nullptr;
    bool visited = false;

    // contains all the movies the actor appeared in
    vector<Movie*> movies;

    /**
     * Constructor that creates an actor struct
     * Parameter(s): n - the name of the actor
     */
    Actor(string n) { name = n; }

    /**
     * Overrides comparator for the actor struct
     */
    bool operator==(const Actor& a) const { return name == a.name; }
};

/**
 * This class is contains the hashfunction used for the Movie struct. It
 * contains no variables, and is used to support the ActorGraph object.
 */
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
 * This class contains all the method headers used for the ActorGraph objects.
 * It contains the variabls Actors and Movies which are hashfunctions used
 * to hold all the actors and movies within the ActorGraph.
 */
class ActorGraph {
  protected:
    // creating user-defined hash functions for Movies and Actors
    // unordered_map<Movie, Actor*, MovieHF> Movies;
    // unordered_map<Actor, Movie*, ActorHF> Actors;
    unordered_map<string, Actor*> Actors;
    unordered_map<string, Movie*> Movies;

  public:
    /**
     * Default constructor for the ActorGraph object
     */
    ActorGraph();

    /* Build the actor graph from dataset file.
     * Each line of the dataset file must be formatted as:
     * ActorName <tab> MovieName <tab> Year
     * Two actors are connected by an undirected edge if they have worked in a
     * movie before.
     */
    bool buildGraphFromFile(const char* filename);

    /**
     * Method that finds the unweighted shortest path from one Actor to another
     * through movie connections and Breadth First Search.
     * Parameter(s): fromActor - the name of the first actor to find the
     * connection toActor - the name of the second actor to find the connection
     *                         between
     *               shortestPath - the string that contains the required format
     *                              showing the shortest path between two actors
     * Return: none
     */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /**
     *  Extra credit method we did not implement
     */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /**
     * Get method that returns the size of Movies hashfunction
     * Return: int representing the size of the Movies hashfunction
     */
    int getMoviesSize() { return Movies.size(); }

    /**
     * Get method that returns the size of Actors hashfunction
     * Return: int representing the size of the Actors hashfunction
     */
    int getActorsSize() { return Actors.size(); }

    /**
     * Tester method that manually inserts actors and movies into the
     * corresponding hashfuncitons to test the method BFS(). Parameter(s): a, b,
     * c, d, e - actor objects to insert into the Actors hashfunction m1, m2,
     * m3, m4, m5 - movie objects to insert into the Movies hashfunction Return:
     * none
     */
    void smallTest(Actor* a, Actor* b, Actor* c, Actor* d, Actor* e, Movie* m1,
                   Movie* m2, Movie* m3, Movie* m4, Movie* m5);

    /**
     * Default default constructor that frees all allocated memory
     */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
