#pragma once

namespace gol
{
    template<class Status>
    class ICellAccessor
    {
    public:
        virtual Status getStatus() const = 0;
        virtual Status getNeighborStatus(size_t horizontalOffset, size_t verticalOffset) const = 0;
    };
}
