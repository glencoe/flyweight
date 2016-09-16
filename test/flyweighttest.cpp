#include "../flyweight.hpp"
#include <string>
#include <memory>
#include <gtest/gtest.h>

namespace {
  using namespace flyweight;

  TEST(FlyweightTest, CreateTwoEqual)
  {
    Flyweight<std::string> obj1("test");
    Flyweight<std::string> obj2("test");
    ASSERT_EQ(obj2.get(), obj1.get());
    ASSERT_EQ(obj2.use_count(), 2);
  }

  TEST(FlyweightTest, CompareOperators)
  {
    Flyweight<std::string> s1("aaaaa");
    Flyweight<std::string> s2("bbbbbbbbbb");
    ASSERT_LT(s1, s2);
  }

  TEST(FlyweightTest, LoosingPointerOnReassignment)
  {
    auto a = Flyweight<std::string>("test");
    auto b = Flyweight<std::string>("test");
    auto c = Flyweight<std::string>("bar");
    ASSERT_EQ(a.use_count(), 2);
    b = c;
    ASSERT_EQ(a.use_count(), 1);
  }

  TEST(FlyweightTest, ConstructTenThousand)
  {
    int count = 100000;
    std::vector<Flyweight<std::string>> a;
    for(int i=0; i < count; i++)
      {
        a.push_back(Flyweight<std::string>(std::to_string(i)));
      }
    ASSERT_EQ(a[1].use_count(), 1);
  }

  TEST(FlyweightTest, ConstructTenThousandStrings)
  {
    int count = 100000;
    std::vector<std::string> a;
    for(int i=0; i<count; i++)
      {
        a.push_back(std::string(std::to_string(i)));
      }
  }

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
 
