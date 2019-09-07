#pragma once

#include "universe.hpp"
#include "classic.hpp"

#include <ctime>

namespace gol
{
    Universe<classic::Status>::Ptr createClassicUniverse(size_t width, size_t height, int seed = std::time(nullptr))
    {
        return std::make_unique<Universe<classic::Status>>(
            classic::randomMatrix(width, height, seed), std::make_shared<classic::RuleStrategy>());
    }
}
