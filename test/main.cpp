#include <universe.hpp>
#include <gtest/gtest.h>

class TestUniverse : public ::testing::Test {
public:
    TestUniverse() { /* init protected members here */ }
    ~TestUniverse() { /* free protected members here */ }
    void SetUp() { /* called before every test */ }
    void TearDown() { /* called after every test */ }

protected:
    /* none yet */
};

TEST_F(TestUniverse, check) {
    ASSERT_EQ(1, 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}