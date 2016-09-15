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

  TEST(StorageTest, CreateAnAwfullLotDifferingItems)
  {
    flyweight::Storage<std::string> st;
    auto shared_ptr_container = new std::vector<std::shared_ptr<const std::string>>();
    std::string text = "";
    for(int i = 0; i<1000000; i++)
      {
        shared_ptr_container->push_back(st.find(std::to_string(i)));
      }
    ASSERT_EQ(st.size(), 1000000);
    delete shared_ptr_container;
    ASSERT_TRUE(st.empty());
  }

  TEST(StorageTest, CreateAnAwfullLotEqualItems)
  {
    int count = 1000000;
    flyweight::Storage<std::string> st;
    auto shared_ptr_container = new std::vector<std::shared_ptr<const std::string>>();
    for(int i=0; i<count; i++)
      {
        shared_ptr_container->push_back(st.find("item"));
      }
    ASSERT_EQ(st.size(), 1);
    delete shared_ptr_container;
    ASSERT_TRUE(st.empty());

  }



}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
 
