#pragma once

#include "rules.hpp"
#include "matrix.hpp"

namespace gol
{
    // Classic implementation of the game algorithms
    namespace classic
    {
        enum class Status: bool
        {
            Dead,
            Alive
        };

        class RuleStrategy : public IRuleStrategy<Status>
        {
            Status calculateStatus(const ICellAccessor<Status>&) const override;
        };

        Matrix<Status> randomMatrix(size_t width, size_t height, int seed);
    }
}
