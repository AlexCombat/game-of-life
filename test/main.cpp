#include <universe.hpp>
#include <classic.hpp>
#include <gtest/gtest.h>

#include "rules.hpp"

class TestUniverse : public ::testing::Test {
public:
    TestUniverse()
        : m_falseState{ m_size, m_size }, m_stableState{ m_size, m_size }
    {
        for (int i = 0; i < m_size; i++)
        {
            for (int j = 0; j < m_size; j++)
            {
                m_falseState.set(i, j, false);
            }
        }

        for (int i = 0; i < m_size; i++)
        {
            for (int j = 0; j < m_size; j++)
            {
                m_stableState.set(i, j, gol::classic::Status::Dead);
            }
        }
        m_stableState.set(0, 0, gol::classic::Status::Alive);
        m_stableState.set(2, 0, gol::classic::Status::Alive);
        m_stableState.set(0, 2, gol::classic::Status::Alive);
        m_stableState.set(2, 2, gol::classic::Status::Alive);
    }
    ~TestUniverse() { /* free protected members here */ }
    void SetUp() { /* called before every test */ }
    void TearDown() { /* called after every test */ }

protected:
    const int m_size = 3;
    gol::Matrix<bool> m_falseState;
    gol::Matrix<gol::classic::Status> m_stableState;
};

TEST_F(TestUniverse, UniverseIteratesOverAllElements) {
    auto universe = gol::Universe<bool>(std::move(m_falseState), std::make_shared<TurnTrueRuleStrategy>());
    universe.iterate(1);

    auto currentState = universe.get();
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            ASSERT_TRUE(currentState.get(i, j));
        }
    }
}

TEST_F(TestUniverse, UniverseWithStableStateStaysStable) {
    auto universe = gol::Universe<bool>(std::move(m_falseState), std::make_shared<TurnTrueRuleStrategy>());
    universe.iterate(0);

    auto currentState = universe.get();
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            ASSERT_FALSE(currentState.get(i, j));
        }
    }
}

TEST_F(TestUniverse, ClassicUniverseCalculatesStatesCorrectly) {
    auto universe = gol::Universe<gol::classic::Status>(m_stableState, std::make_shared<gol::classic::RuleStrategy>());
    universe.iterate(1);

    auto currentState = universe.get();
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            ASSERT_EQ(m_stableState.get(i, j), currentState.get(i,j));
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}