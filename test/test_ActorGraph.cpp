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
        ActorGraph ag;
        ag.buildGraphFromFile("map2pairs.txt");
    }
};

// TODO: add tests for actor graph

TEST_F(ActorGraphFixture, EMPTY_TEST) {
    ASSERT_EQ(ag.getMoviesSize(), 4);
}
*/

TEST(ActorGraphTests, EMPTY_TEST) {
    ActorGraph ag;
    ag.smallTest();
    ASSERT_EQ(ag.getMoviesSize(), 4);
}