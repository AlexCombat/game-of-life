#include "universe_builder.hpp"

int main()
{
    auto universe = gol::createClassicUniverse(20, 20, 0);
    universe->iterate(5);
}