#include "classic.hpp"

#include <cstdlib>

namespace gol
{
    namespace classic
    {
        Status gol::classic::RuleStrategy::calculateStatus(const ICellAccessor<Status>& cellAccessor) const
        {
            Status cellStatus = cellAccessor.getStatus();

            size_t liveNeighborsCount = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0) continue;
                    if (cellAccessor.getNeighborStatus(i, j) == Status::Alive) liveNeighborsCount++;
                }
            }

            if (cellStatus == Status::Dead)
            {
                if (liveNeighborsCount == 3) return Status::Alive;
            }
            else
            {
                if (liveNeighborsCount < 2 || liveNeighborsCount > 3) return Status::Dead;
                
                return Status::Alive;
            }

            return Status::Dead;
        }

        Matrix<Status> randomMatrix(size_t width, size_t height, int seed)
        {
            Matrix<Status> matrix(width, height);

            std::srand(seed);

            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    matrix.set(i, j, static_cast<Status>(std::rand() % 2));
                }
            }

            return matrix;
        }
    }
}