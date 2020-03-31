#include "MBWand.hpp"

namespace MB
{
    bool MBTransKey::operator < (const MBTransKey &key2)
    {
        return t < key2.t;
    }

    MBTransKey::MBTransKey()
    {

    }

    MBTransKey::MBTransKey(const MBTransKey & tk)
    {
        *this = tk;
    }

    MBTransKey & MBTransKey::operator = (const MBTransKey & tk)
    {
        t = tk.t;
        x = tk.x;
        y = tk.y;
        z = tk.z;
        return *this;
    }
}