/**
 * TODO: add file header
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP
#include "Movie.hpp"

#include <iostream>
#include <vector>

using namespace std;

/**
 * TODO: add class header
 */
class Actor {
  protected:
  public:
    string name;
    vector<Movie*> movies;

    /* TODO */
    // default constructor
    Actor();
    Actor(string name);

    /* TODO */
    ~Actor();

    /* TODO */
    string getName() { return name; }
};

#endif  // ACTOR_HPP
