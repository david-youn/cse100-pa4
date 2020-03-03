#include <gtest/gtest.h>
#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

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