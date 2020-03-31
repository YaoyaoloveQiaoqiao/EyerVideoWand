#include "MBWand.hpp"

namespace MB
{
    MBFilterKey::MBFilterKey()
    {

    }

    MBFilterKey::MBFilterKey(const MBFilterKey & fk)
    {
        *this = fk;
    }

    MBFilterKey & MBFilterKey::operator = (const MBFilterKey & fk)
    {
        t = fk.t;
        level = fk.level;
        filterName = fk.filterName;
        return *this;
    }
}