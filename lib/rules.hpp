#pragma once

#include "cell.hpp"

#include <memory>

namespace gol
{
    template<class CellStatus>
    class IRuleStrategy
    {
    public:
        using Ptr = std::shared_ptr<IRuleStrategy<CellStatus>>;

        virtual CellStatus calculateStatus(const ICellAccessor<CellStatus>&) const = 0;
    };
}
