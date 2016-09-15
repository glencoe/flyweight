#include "../storage.hpp"
#include <string>
#include <gtest/gtest.h>

namespace {

  TEST(StorageTest, EmptyContainer)
  {
    flyweight::Storage<std::string> st;
    ASSERT_TRUE(st.empty());
  }

  TEST(StorageTest, AddOneWithoutSharing)
  {
    flyweight::Storage<std::string> st;
    st.add("testing");
    ASSERT_TRUE(st.empty());
    ASSERT_EQ(st.size(), 0);
  }

  TEST(StorageTest, AddOne)
  {
    flyweight::Storage<std::string> st;
    auto ptr = st.add("testing");
    ASSERT_FALSE(st.empty());
    ASSERT_EQ(st.size(), 1);
  }

  TEST(StorageTest, AddTwoDiffering)
  {
    flyweight::Storage<std::string> st;
    auto ptr1 = st.add("Testing");
    auto ptr2 = st.add("tEstTTTTing");
    ASSERT_FALSE(st.empty());
    ASSERT_EQ(st.size(), 2);
  }

  TEST(StorageTest, AddTwoEqual)
  {
    flyweight::Storage<std::string> st;
    auto ptr1 = st.add("Testing");
    auto ptr2 = st.add("Testing");

  }



}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
 
