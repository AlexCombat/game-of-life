#pragma once

#include "cell.hpp"

#include <memory>

namespace gol
{
    // Rule strategy calculates the new state of the cell based on the cells surrounding it.
    // The actual rules are determined by implementations
    template<class CellStatus>
    class IRuleStrategy
    {
    public:
        using Ptr = std::shared_ptr<IRuleStrategy<CellStatus>>;

        virtual CellStatus calculateStatus(const ICellAccessor<CellStatus>&) const = 0;
    };
}
