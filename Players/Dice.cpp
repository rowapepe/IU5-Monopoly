#include "Dice.hpp"

namespace Dice{
int RollDice() {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(1, maxRoll);
    return distribution(randomEngine);
}
}
