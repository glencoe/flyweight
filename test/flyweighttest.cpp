#include "../flyweight.hpp"
#include <string>
#include <gtest/gtest.h>

namespace {
  using namespace flyweight;

  TEST(Flyweight, CreateTwoEqual)
  {
    Flyweight<std::string> obj1("test");
    Flyweight<std::string> obj2("test");
    ASSERT_EQ(obj2.get(), obj1.get());
  }


}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
 
