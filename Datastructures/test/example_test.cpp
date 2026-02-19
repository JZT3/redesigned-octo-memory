#include <iostream>
#include <gtest/gtest.h>


class example
{
  public:
    int foo()
    {
      return 1;
    }
};

class testFixture : public testing::Test
{
  public:
    testFixture()
    {
      std::cout<<"construct"<<'\n';
      ex = new example();
    }

    ~testFixture()
    {
      std::cout<<"destruct"<<std::endl;
      delete ex;
    }

    void SetUp()
    {
      std::cout<<"set up"<<'\n';
    }

    void TearDown()
    {
      std::cout<<"tear down"<<'\n';
    }

    example* ex;
};


TEST_F(testFixture, test1)
{
  ASSERT_EQ(1,ex->foo());
}

/*
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}

*/
