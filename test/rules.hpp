#include <rules.hpp>

class TurnTrueRuleStrategy : public gol::IRuleStrategy<bool>
{
public:
    bool calculateStatus(const gol::ICellAccessor<bool>&) const override
    {
        return true;
    }
};