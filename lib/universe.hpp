#pragma once

#include "rules.hpp"
#include "matrix.hpp"

#include <memory>

namespace gol
{
    // Class, representing a game universe. Receives rule strategy and the initial state of the game.
    // On iteration, calculates new states of each cell by calling rule strategy and form the new state of the game
    template<class CellStatus>
    class Universe
    {
    public:
        using Ptr = std::unique_ptr<Universe<CellStatus>>;

        Universe(Matrix<CellStatus> initialState, typename IRuleStrategy<CellStatus>::Ptr ruleStrategy);

        const Matrix<CellStatus>& get() const;
        void iterate(std::size_t steps);

    private:
        // Wrapper interface over the Matrix that allow to access elements
        // with indices relative to the passed offsets.
        class CellAccessor : public ICellAccessor<CellStatus>
        {
        public:
            CellAccessor(size_t x, size_t y, const Universe& universe);

            CellStatus getStatus() const override;
            CellStatus getNeighborStatus(size_t horizontalOffset, size_t verticalOffset) const override;

        private:
            size_t m_x;
            size_t m_y;
            const Universe& m_universe;
        };

        Matrix<CellStatus> m_currentState;
        typename IRuleStrategy<CellStatus>::Ptr m_ruleStrategy;

        size_t m_width;
        size_t m_height;
    };

    template<class CellStatus>
    Universe<CellStatus>::Universe(Matrix<CellStatus> initialState, typename IRuleStrategy<CellStatus>::Ptr ruleStrategy)
        : m_currentState(std::move(initialState)),
        m_ruleStrategy(std::move(ruleStrategy)),
        m_width(m_currentState.getWidth()),
        m_height(m_currentState.getHeight())
    {
        if (!m_ruleStrategy)
        {
            throw std::invalid_argument("ruleStrategy does not exist");
        }
    }

    template<class CellStatus>
    const Matrix<CellStatus>& Universe<CellStatus>::get() const
    {
        return m_currentState;
    }

    template<class CellStatus>
    void Universe<CellStatus>::iterate(std::size_t steps)
    {
        for (int i = 0; i < steps; i++)
        {
            Matrix<CellStatus> nextIteration(m_width, m_height);

            for (size_t i = 0; i < m_width; ++i)
            {
                for (size_t j = 0; j < m_height; ++j)
                {
                    nextIteration.set(i, j, m_ruleStrategy->calculateStatus(CellAccessor(i, j, *this)));
                }
            }

            m_currentState = std::move(nextIteration);
        }
    }

    template<class CellStatus>
    Universe<CellStatus>::CellAccessor::CellAccessor(size_t x, size_t y, const Universe& universe)
        : m_x(x), m_y(y), m_universe(universe)
    {
    }

    template<class CellStatus>
    CellStatus Universe<CellStatus>::CellAccessor::getStatus() const
    {
        return getNeighborStatus(0, 0);
    }

    template<class CellStatus>
    CellStatus Universe<CellStatus>::CellAccessor::getNeighborStatus(size_t horizontalOffset, size_t verticalOffset) const
    {
        // Indices are calculated as division remainder
        // to treat the matrix as a closed space
        return m_universe.m_currentState.get(
            (m_x + horizontalOffset) % m_universe.m_width,
            (m_y + verticalOffset) % m_universe.m_height);
    }
}
