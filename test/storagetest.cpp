#include "../storage.hpp"
#include <string>
#include <gtest/gtest.h>

namespace {

  TEST(StorageTest, EmptyContainer)
  {
    flyweight::Storage<std::string> st;
    ASSERT_TRUE(st.empty());
  }

  TEST(StorageTest, FindOneWithoutSharing)
  {
    flyweight::Storage<std::string> st;
    st.find("testing");
    ASSERT_TRUE(st.empty());
    ASSERT_EQ(st.size(), 0);
  }

  TEST(StorageTest, FindOne)
  {
    flyweight::Storage<std::string> st;
    auto ptr = st.find("testing");
    ASSERT_FALSE(st.empty());
    ASSERT_EQ(st.size(), 1);
  }

  TEST(StorageTest, FindTwoDiffering)
  {
    flyweight::Storage<std::string> st;
    auto ptr1 = st.find("Testing");
    auto ptr2 = st.find("tEstTTTTing");
    ASSERT_FALSE(st.empty());
    ASSERT_EQ(st.size(), 2);
  }

  TEST(StorageTest, FindTwoEqual)
  {
    flyweight::Storage<std::string> st;
    auto ptr1 = st.find("Testing");
    auto ptr2 = st.find("Testing");
    ASSERT_EQ(st.size(), 1);
    ASSERT_EQ(ptr1, ptr2);
  }



}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
 
