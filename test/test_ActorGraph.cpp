#include <gtest/gtest.h>
#include "ActorGraph.hpp"

using namespace std;
using namespace testing;
/*
class ActorGraphFixture : public ::testing::Test {
  protected:
    ActorGraph ag;

  public:
    ActorGraphFixture() {
        // initialization code here
        ag.buildGraphFromFile("../data/small_actor_graph.tsv");
    }
};

// TODO: add tests for actor graph

TEST_F(ActorGraphFixture, SMALL_TEST) {
    ASSERT_EQ(ag.getMoviesSize(), 7);
    ASSERT_EQ(ag.getActorsSize(), 7);
}

TEST(ActorGraphTest, BIG_TEST) {
    ActorGraph bag;
    bag.buildGraphFromFile("../data/imdb_2019.tsv");
    ASSERT_EQ(bag.getMoviesSize(), 325354);
    ASSERT_EQ(bag.getActorsSize(), 412528);
}
*/

/*
TEST(ActorGraphTest, SMALL_TEST) {
    ActorGraph* small = new ActorGraph();
    Actor* a = new Actor("a");
    Actor* b = new Actor("b");
    Actor* c = new Actor("c");
    Actor* d = new Actor("d");
    Actor* e = new Actor("e");

    Movie* m1 = new Movie("m1", 2000);
    Movie* m2 = new Movie("m2", 2001);
    Movie* m3 = new Movie("m3", 2002);
    Movie* m4 = new Movie("m4", 2020);
    Movie* m5 = new Movie("m5", 2012);

    a->movies = {m1, m2};
    b->movies = {m2, m3, m5};
    c->movies = {m3, m1};
    d->movies = {m4, m5};
    e->movies = {m5, m4};

    m1->actors = {a, c};
    m2->actors = {a, b};
    m3->actors = {c, b, a};
    m4->actors = {d, e};
    m5->actors = {d, e, b};

    small->smallTest(a, b, c, d, e, m1, m2, m3, m4, m5);

    ASSERT_EQ(small->getMoviesSize(), 5);
    ASSERT_EQ(small->getActorsSize(), 5);

    string path = "";
    small->BFS("a", "e", path);

    ASSERT_EQ(path.compare("(a)--[m2#@2001]-->(b)--[m5#@2012]-->(e)"), 0);

    delete (a);
    delete (b);
    delete (c);
    delete (d);
    delete (e);
    delete (m1);
    delete (m2);
    delete (m3);
    delete (m4);
    delete (m5);
}
*/