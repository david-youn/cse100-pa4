/**
 * TODO: add file header
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP
#include "Actor.hpp"

#include <iostream>
#include <vector>

using namespace std;

/**
 * TODO: add class header
 */
class Movie {
  protected:
  public:
    string title;
    int year;
    vector<Actor*> actors;

    /* TODO */
    // defualt constructor
    Movie();
    Movie(string title, int year);

    /* TODO */
    ~Movie();

    string getTitle() { return title; }

    int getYear() { return year; }
};

#endif  // MOVIE
